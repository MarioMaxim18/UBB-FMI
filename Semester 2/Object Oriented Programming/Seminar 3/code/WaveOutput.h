#pragma once
#include "AcousticWave.h"
#include <fstream>
class WaveOutput {
public:
	static bool saveSamples(const char* csv_path, const AcousticWave& ac);
};

