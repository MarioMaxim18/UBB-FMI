#include "WaveOutput.h"

bool WaveOutput::saveSamples(const char* csv_path, const AcousticWave& ac) {
    std::ofstream fout(csv_path);
    const float* samples = ac.getSamples();
    for (int i = 0; i < ac.getNrOfSamples(); i++)
        fout << samples[i] << "\n";
    fout.close();
    return true;
}
