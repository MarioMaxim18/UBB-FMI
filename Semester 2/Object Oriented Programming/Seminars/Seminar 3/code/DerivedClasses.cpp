#include "DerivedClasses.h"

void SineWave::computeSamples(float _duration, float _freq, unsigned int _sampleRate) {
	//call the base class method to initialize our sample array
	AcousticWave::computeSamples(_duration, _freq, _sampleRate);

	//duration of interval between sample points 
	float sampleT = _duration / nrOfSamples;
	//first sample point: 0
	//second sample point: 1*sampleT
	//third sample point: 2*sampleT
	//...
	//generally: timestep i will be at i*sampleT

	for (unsigned int i = 0; i < nrOfSamples; i++)
		samples[i] = amplitude * sin(2 * M_PI * freq * i * sampleT);
}

void SquareWave::computeSamples(float _duration, float _freq, unsigned int _sampleRate)
{
	AcousticWave::computeSamples(_duration, _freq, _sampleRate);
	float sampleT = _duration / nrOfSamples;
	for (unsigned int i = 0; i < nrOfSamples; i++) {
		float y_si = amplitude * sin(2 * M_PI * freq * i * sampleT);
		if (y_si > 0)
			samples[i] = 1;
		else if (y_si < 0)
			samples[i] = -1;
		else
			samples[i] = 0;

	}
}

void TriangleWave::computeSamples(float _duration, float _freq, unsigned int _sampleRate)
{
	AcousticWave::computeSamples(_duration, _freq, _sampleRate);
	float sampleT = _duration / nrOfSamples;
	for (unsigned int i = 0; i < nrOfSamples; i++) {
		double x = 2 * i * sampleT * M_PI * freq;
		double y_st = ((this->amplitude * 2) / M_PI) * asin(sin(x));
		this->samples[i] = y_st;

	}
}

void SawtoothWave::computeSamples(float _duration, float _freq, unsigned int _sampleRate)
{
	AcousticWave::computeSamples(_duration, _freq, _sampleRate);
	float sampleT = _duration / nrOfSamples;
	for (unsigned int i = 0; i < nrOfSamples; i++) {
		double x = i*sampleT * M_PI * freq;
		double cot = cos(x) / sin(x);
		double y_st = (-1) * (((this->amplitude * 2) / M_PI) * atan(cot));
		this->samples[i] = y_st;

	}
}
