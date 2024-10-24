#pragma once
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
class AcousticWave {
protected:
	float freq;
	unsigned int amplitude;
	unsigned int sampleRate;
	unsigned int nrOfSamples;
	float* samples;
public:
	AcousticWave() : freq{ 0 }, amplitude{ 0 }, sampleRate{ 0 }, samples{ nullptr }, nrOfSamples{0} {};
	AcousticWave(float _freq, unsigned int _amplitude, unsigned int _sampleRate) : freq{ _freq }, amplitude{ _amplitude }, sampleRate{ _sampleRate }, samples{ nullptr }, nrOfSamples {0} {};
	virtual ~AcousticWave() { delete[] samples; cout << "AcousticWave destructor called." << endl;};
	AcousticWave(const AcousticWave& other);
	void operator=(const AcousticWave& other);
	inline void setFreq(float _freq) { freq = _freq; };
	inline void setAmplitude(unsigned int _amplitude) { amplitude = _amplitude; };
	inline void setSampleRate(unsigned int _sampleRate) { sampleRate = _sampleRate; };
	inline float getFreq() const { return freq; };
	inline const float* getSamples() const { return samples; };
	inline unsigned int getAmplitude() const { return amplitude; };
	inline unsigned int getSampleRate() const { return sampleRate; };
	inline unsigned int getNrOfSamples() const { return nrOfSamples; };
	virtual void computeSamples(float _duration, float _freq, unsigned int _sampleRate);
	virtual const string getType() const { return "base"; };
	friend std::ostream& operator<<(std::ostream& stream, const AcousticWave& wave);

};


