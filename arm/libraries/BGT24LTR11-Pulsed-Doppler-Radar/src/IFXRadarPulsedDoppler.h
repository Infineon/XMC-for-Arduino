#ifndef IFXRadarPulsedDoppler_h
#define IFXRadarPulsedDoppler_h
#include "arduino_adapt.h"

class IFXRadarPulsedDoppler
{
private: 
	bool result_handler_registered;
	bool error_handler_registered;
	Print *outDev;
	
public:
	IFXRadarPulsedDoppler();

	// config functions
	uint8_t setMinSpeed(float speedMs);
	float getMinSpeed(void);
    uint8_t setMaxSpeed(float speedMs);
	float getMaxSpeed(void);
	uint8_t setMotionSensitivity(float threshold); // threshold that will determine motion or not
	float getMotionSensitivity(void);
	uint8_t setDopplerSensitivity(float threshold); // threshold that will determine motion with direction (departing/approaching) or not
	float getDopplerSensitivity(void);
	uint8_t setFramePeriod(uint8_t periodUs); // frame period in usec
    uint8_t getFramePeriod(void);
	uint8_t setSampleFreq(uint32_t frequencyHz); // ADC sampling frequency in Hz
    uint32_t getSampleFreq(void);
    uint8_t setSkipSamples(uint32_t numSamples); // number of samples to skip
    uint32_t getSkipSamples(void);
    uint8_t setNumSamples(uint32_t numSamples); // number of samples
    uint32_t getNumSamples(void);
    uint8_t setPulseWidth(uint32_t widthUs); // pulse width in usec
    uint32_t getPulseWidth(void);
    uint32_t getMinFramePeriod(void); // get the minimum frame period in usec
    float getCurrentConsumption(void); // get the current consumed by the board in mA
 
	// control functions
	void initHW(void);
    void registerResultCallback(void(*callBackPtr)); // register function to be called when also process is done
    void registerErrorCallback(void(*callBackPtr)); // register function to be called in case of error
	void begin(void);
	void end(void); 
	void run(void); // run radar process

	// result functions
	bool targetAvailable(void); // true: motion (with no direction), false: no motion
	float getDopplerLevel(void);
	float getDopplerFreqHz(void);
	float getVelocity(void); // get speed value with sign
	uint8_t getDirection(void); // returns 0:no direction, 1:departing, 2:approaching
	float getSpeed(void); // get speed value without sign
	uint32_t getFrameCount(void); // get frame count of result
	
	// debug functions
	void parameterDump(Print *outDev);
	void parameterDump();
	void setPrintDev(Print *outDev);
};

#endif