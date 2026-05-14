#pragma once
#include <string>
#include <vector>

struct AudioData {
    int sampleRate;
    std::vector<double> samples;
};

AudioData readWav(const std::string& filename);