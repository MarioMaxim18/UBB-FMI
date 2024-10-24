#include "AcousticWave.h"



AcousticWave::AcousticWave(const AcousticWave& other) {
	freq = other.freq;
	amplitude = other.amplitude;
	sampleRate = other.sampleRate;
	nrOfSamples = other.nrOfSamples;
	if (nrOfSamples == 0)
		samples = nullptr;
	else
		samples = new float[nrOfSamples];
	for (int i = 0; i < nrOfSamples; i++) {
		samples[i] = other.samples[i];
	}
}

void AcousticWave::operator=(const AcousticWave& other) {
	delete[] samples;
	freq = other.freq;
	amplitude = other.amplitude;
	sampleRate = other.sampleRate;
	nrOfSamples = other.nrOfSamples;
	if (nrOfSamples == 0)
		samples = nullptr;
	else
		samples = new float[nrOfSamples];
	for (int i = 0; i < nrOfSamples; i++) {
		samples[i] = other.samples[i];
	}
}

void AcousticWave::computeSamples(float _duration, float _freq, unsigned int _sampleRate) {
	unsigned int _nrOfSamples = (unsigned int) (_duration * _freq * _sampleRate);
	this->freq = _freq;
	this->sampleRate = _sampleRate;
	samples = new float[_nrOfSamples];
	nrOfSamples = _nrOfSamples;
	for (int i = 0; i < _nrOfSamples; i++)
		samples[i] = 0;
}

std::ostream& operator<<(std::ostream& stream, const AcousticWave& wave) {
	stream << "Acoustic Wave (Frequency: " << wave.freq << "; Amplitude: " << wave.amplitude << "; Sample rate:" << wave.sampleRate << endl;
	stream << "Samples (number of samples = " << wave.nrOfSamples << "):";
	for (int i = 0; i < wave.nrOfSamples; i++) {
		stream << wave.getSamples()[i] << " ";
	};
	stream << endl;
	return stream;
}
