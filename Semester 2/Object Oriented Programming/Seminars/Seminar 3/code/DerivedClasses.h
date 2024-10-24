#define _USE_MATH_DEFINES
#include "AcousticWave.h"
#include <cmath>
#pragma once

class SineWave : public AcousticWave {
public:
	SineWave() = default;
	SineWave(float _freq, unsigned int _amplitude, unsigned int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {};
	void computeSamples(float _duration, float _freq, unsigned int _sampleRate);
	const string getType() const override { return "sine_wave"; }
	string specificToSineWave() { return "This is a function specific to the SineWave (does not exist in AcousticWave)."; };
	~SineWave() { cout << "Sine Wave destructor called." << endl; };
};
class SquareWave : public AcousticWave {
public:
	SquareWave() = default;
	SquareWave(float _freq, unsigned int _amplitude, unsigned int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {};
	void computeSamples(float _duration, float _freq, unsigned int _sampleRate);
	const string getType() const override { return "square_wave"; }
	~SquareWave() { cout << "Square Wave destructor called." << endl; }
};

class TriangleWave : public AcousticWave {
public:
	TriangleWave() = default;
	TriangleWave(float _freq, unsigned int _amplitude, unsigned int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {};
	void computeSamples(float _duration, float _freq, unsigned int _sampleRate);
	const string getType() const override { return "triangle_wave"; }

	~TriangleWave() { cout << "Triangle wave destructor called." << endl; };
};

class SawtoothWave : public AcousticWave {
public:
	SawtoothWave() = default;
	SawtoothWave(float _freq, unsigned int _amplitude, unsigned int _sampleRate) : AcousticWave(_freq, _amplitude, _sampleRate) {};
	void computeSamples(float _duration, float _freq, unsigned int _sampleRate);
	const string getType() const override { return "sawtooth_wave"; }

	~SawtoothWave() { cout<<"Sawtooth Wave destructor called."<<endl; };
};
