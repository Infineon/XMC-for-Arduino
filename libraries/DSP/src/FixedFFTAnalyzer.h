
/*
  Addapted from https://github.com/arduino-libraries/ArduinoSound/blob/master/src/FFTAnalyzer.h

  FFT is computed with float numbers, since arm_rfft_fast_f32() is a more efficient implementation than arm_rfft_q31(), the later computes the whole (mirrored) spectrum
  whereas FFT can be uniquely represented only by half of the spectrum due to symmetry.
  With identical algorithm the implementation with floats even uses less space. 
*/

// TODO: switch between 16/32 bits
#ifndef _FIXED_FFT_ANALYZER_H_INCLUDED
#define _FIXED_FFT_ANALYZER_H_INCLUDED

#include <Arduino.h>
#define N_WAVE 1024    /* full length of Sinewave[] */
#define LOG2_N_WAVE 10 /* log2(N_WAVE) */

typedef struct {
	uint32_t mag;
	uint32_t freq;
} MAX_MAG_FRQ_t;

/*
  FIX_MPY() - fixed-point multiplication & scaling.
  Substitute inline assembly for hardware-specific
  optimization suited to a particluar DSP processor.
  Scaling ensures that result remains 16-bit.
*/
inline short FIX_MPY(short a, short b)
{
  /* shift right one less bit (i.e. 15-1) */
  int c = ((int)a * (int)b) >> 14;
  /* last bit shifted out = rounding-bit */
  b = c & 0x01;
  /* last shift + rounding bit */
  a = (c >> 1) + b;
  return a;
}

inline uint32_t SquareRoot(uint32_t a_nInput)
{
    uint32_t op  = a_nInput;
    uint32_t res = 0;
    uint32_t one = 1uL << 30; // The second-to-top bit is set: use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type

    // "one" starts at the highest power of four <= than the argument.
    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op = op - (res + one);
            res = res +  2 * one;
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}

class FFTAnalyzer
{
public:
  FFTAnalyzer();

  static short Sinewave[N_WAVE - N_WAVE / 4];

  int fix_fft(short *, short *, short, short);

  MAX_MAG_FRQ_t compute_magnitude(short *, short *, short *, short);
};

#endif

