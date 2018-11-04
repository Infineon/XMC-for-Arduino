/** @file SignalInput.cpp
 *  @brief This is an abstract class for interfacing between input signals (such as audio signals via I2S) and signal processing libraries
 */
#include <SignalInput.h>

#if defined(XMC4700_Relax_Kit)
#include "FFTAnalyzer.h"

int SignalInput::setAnalyzer(FFTAnalyzer *analyzer)
{
    _analyzer = analyzer;
    return _analyzer->configure();
}
#endif

void SignalInput::enablePreEmphasizing(int factor)
{
    _alpha = factor;
}