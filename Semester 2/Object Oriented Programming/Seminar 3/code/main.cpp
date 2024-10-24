#define _CRT_DBG_MALLOC
#include <iostream>
#include <vector>
#include <crtdbg.h>
#include "DerivedClasses.h"
#include "WaveOutput.h"
using std::vector;
using std::cout;
using std::endl;


void run() {
	
	vector<AcousticWave*> waveVector;

	AcousticWave* sineWave = new SineWave{ 4, 5, 100 };
	AcousticWave* squareWave = new SquareWave{ 4, 5, 100 };
	AcousticWave* sawtoothWave = new SawtoothWave{ 4, 5, 100 };
	AcousticWave* triangleWave = new TriangleWave{ 4, 5, 100 };

	waveVector.push_back(sineWave);
	waveVector.push_back(squareWave);
	waveVector.push_back(sawtoothWave);
	waveVector.push_back(triangleWave);

	for (const auto& wave : waveVector) {
		wave->computeSamples(5, 220, 100);
		//cout << wave->getType();
		string file_title = "wave_output_5_220_100" + wave->getType() + ".csv";
		cout << file_title << endl;
		WaveOutput::saveSamples(file_title.c_str(), *wave);
	}
	for (auto wave : waveVector)
		delete wave;
}
int main() {
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}