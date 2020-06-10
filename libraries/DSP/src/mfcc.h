/*
* Typical feature extraction pipeline:
* speech signal -> magnitude spectrum (FFT) -> mel freq warping -> critical band integration (overlapping triangle filters)
* -> logarithm -> cepstral decorrelation -> cepstral mean norm. -> energy norm. -> acoustic vector
* 
*/

// only tested with xmc700
#if defined(XMC4700_Relax_Kit)

#include "FFTAnalyzer.h"

#ifndef _MFCC_H_INCLUDED
#define _MFCC_H_INCLUDED

#define M_2PI 6.283185307179586476925286766559
#define FLOAT_MIN 0.000000001

#define MEL_LOW_FREQ 100
#define MEL_HIGH_FREQ 4000
#define NUM_FBANK_BINS 39 // number of the triangular mel filters, typically 26 (20-40)
class MFCC
{
  private:
    int samp_freq;
    int _spectrumLength;
    int num_mfcc_features; // number of the needed features, 10 should be enough
    int mfcc_dec_bits;

    FFTAnalyzer *fftAnalyzer;
    bool fft_update_method;
    float *hammingWindow;
    float *magnitudes;
    float *mel_energies; // how much energy is in each filter bank
    float *dctMatrix;
    // mark the first/last indices of each section of the magnitude that should go into the same filter
    int32_t *fbank_filter_first;
    int32_t *fbank_filter_last;
    // an array of filters with increasing lengths
    float **mel_fbank;
    float *create_dct_matrix(int32_t input_fftLength, int32_t coefficient_count);
    float **create_mel_fbank();
    static inline float InverseMelScale(float mel_freq)
    {
        return 700.0f * (expf(mel_freq / 1127.0f) - 1.0f);
    }

    static inline float MelScale(float freq)
    {
        return 1127.0f * logf(1.0f + freq / 700.0f);
    }

  public:
    MFCC(int length, int num_mfcc_features = 10, int mfcc_dec_bits = 2);
    virtual ~MFCC();
    void getMfccFeatues(int8_t *mfcc_features);

    /*typically gets I2S as input; I2S should be started in advance*/
    int input(SignalInput *signalInput, int samplingFreq = 16000);
};

#endif
#endif