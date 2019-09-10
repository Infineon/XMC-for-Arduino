#if defined(XMC4700_Relax_Kit)
#include <mfcc.h>

MFCC::MFCC(int frame_len, int num_mfcc_features, int mfcc_dec_bits) : num_mfcc_features(num_mfcc_features), mfcc_dec_bits(mfcc_dec_bits)
{
    fftAnalyzer = new FFTAnalyzer(frame_len);
    _spectrumLength = fftAnalyzer->getSpectrumLength();
    hammingWindow = new float[frame_len];
    magnitudes = new float[_spectrumLength]; // only half of the spectrum needed
    mel_energies = new float[NUM_FBANK_BINS];

    // init hamming window
    for (int i = 0; i < frame_len; i++)
        hammingWindow[i] = 0.5 - 0.5 * cos(M_2PI * ((float)i) / (frame_len - 1));

    // init mel frequency bank
    fbank_filter_first = new int32_t[NUM_FBANK_BINS];
    fbank_filter_last = new int32_t[NUM_FBANK_BINS];

    // init dct coefficients
    dctMatrix = create_dct_matrix(NUM_FBANK_BINS, num_mfcc_features);
}

MFCC::~MFCC()
{
    delete[] fftAnalyzer;
    delete[] hammingWindow;
    delete[] magnitudes;
    delete[] mel_energies;
    delete[] fbank_filter_first;
    delete[] fbank_filter_last;
    delete[] dctMatrix;
    for (int i = 0; i < NUM_FBANK_BINS; i++)
        delete mel_fbank[i];
    delete mel_fbank;
}

float *MFCC::create_dct_matrix(int32_t num_fbank_bins, int32_t num_mfcc_features)
{
    int32_t k, n;
    float *M = new float[num_fbank_bins * num_mfcc_features];

    // normlazation necessary?
    float normalizer;
    arm_sqrt_f32(2.0 / (float)num_fbank_bins, &normalizer);

    for (k = 0; k < num_mfcc_features; k++)
    {
        for (n = 0; n < num_fbank_bins; n++)
        {
            M[k * num_fbank_bins + n] = normalizer * cos(((float)M_PI) / num_fbank_bins * (n + 0.5) * k);
        }
    }
    return M;
}

// creates overlapping triangular filters with logarithmically increasing width
float **MFCC::create_mel_fbank()
{
    int32_t bin, i;

    int32_t num_fft_bins = _spectrumLength;
    float fft_bin_width = ((float)samp_freq) / (_spectrumLength * 2);
    float mel_low_freq = MelScale(MEL_LOW_FREQ);
    float mel_high_freq = MelScale(MEL_HIGH_FREQ);
    float mel_freq_delta = (mel_high_freq - mel_low_freq) / (NUM_FBANK_BINS + 1);

    float *this_bin = new float[num_fft_bins];

    float **mel_fbank = new float *[NUM_FBANK_BINS];

    for (bin = 0; bin < NUM_FBANK_BINS; bin++)
    {
        float left_mel = mel_low_freq + bin * mel_freq_delta;
        float center_mel = mel_low_freq + (bin + 1) * mel_freq_delta;
        float right_mel = mel_low_freq + (bin + 2) * mel_freq_delta;

        int32_t first_index = -1, last_index = -1;

        // only use half of the fft output
        for (i = 0; i < num_fft_bins; i++)
        {
            float freq = (fft_bin_width * i); // center freq of this fft bin.
            float mel = MelScale(freq);
            this_bin[i] = 0.0;

            // find the current triangle
            if (mel > left_mel && mel < right_mel)
            {
                float weight;
                if (mel <= center_mel)
                {
                    weight = (mel - left_mel) / (center_mel - left_mel);
                }
                else
                {
                    weight = (right_mel - mel) / (right_mel - center_mel);
                }
                this_bin[i] = weight;
                if (first_index == -1)
                    first_index = i;
                last_index = i;
            }
        }

        fbank_filter_first[bin] = first_index;
        fbank_filter_last[bin] = last_index;
        mel_fbank[bin] = new float[last_index - first_index + 1];

        int32_t j = 0;
        //copy the part we care about
        for (i = first_index; i <= last_index; i++)
        {
            mel_fbank[bin][j++] = this_bin[i];
        }
    }
    delete[] this_bin;
    return mel_fbank;
}

int MFCC::input(SignalInput *signalInput, int samplingFreq)
{
    if (!fftAnalyzer)
        return;
    // in kws this must be 16000
    samp_freq = samplingFreq;
    fft_update_method = signalInput->_fftUpdateMethod;
    // mel freq bank depends on sampling freq
    mel_fbank = create_mel_fbank();

    // enables interrupt
    fftAnalyzer->input(signalInput, true);
}

void MFCC::getMfccFeatues(int8_t *mfcc_features)
{
    // must be initialized before use
    if (!fftAnalyzer || !magnitudes)
        return;

    if(fft_update_method == SYNC)
        fftAnalyzer->update2(hammingWindow);
    else    
        fftAnalyzer->update(hammingWindow);

    int availableBins = fftAnalyzer->readMagnitude(magnitudes, _spectrumLength);
    if (!availableBins)
        return;

    // apply mel filters
    int bin, j;
    float mel_energy = 0;
    for (bin = 0; bin < NUM_FBANK_BINS; bin++)
    {
        j = 0;
        mel_energy = 0;
        int first_index = fbank_filter_first[bin];
        int last_index = fbank_filter_last[bin];
        for (int i = first_index; i <= last_index; i++)
        {
            mel_energy += mel_fbank[bin][j++] * magnitudes[i];
        }

        // avoid log 0
        if (mel_energy < FLOAT_MIN)
        {
            mel_energy = FLOAT_MIN;
        }
        mel_energies[bin] = logf(mel_energy);
    }

    // discrete cosine transform of log mel energies
    float mfcc_feature;
    for (int k = 0; k < num_mfcc_features; k++)
    {
        mfcc_feature = 0;
        for (bin = 0; bin < NUM_FBANK_BINS; bin++)
        {
            mfcc_feature += mel_energies[bin] * dctMatrix[k * NUM_FBANK_BINS + bin];
        }

        // Input is Qx.mfcc_dec_bits (from quantization step)
        mfcc_feature *= (0x1 << mfcc_dec_bits);
        mfcc_feature = round(mfcc_feature);
        if (mfcc_feature >= 127)
            mfcc_features[k] = 127;
        else if (mfcc_feature <= -128)
            mfcc_features[k] = -128;
        else
            mfcc_features[k] = mfcc_feature;
    }
}
#endif