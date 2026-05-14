#pragma once
#include <vector>

std::vector<double> makeFrequencyGrid();

std::vector<int> buildFingerprint(
    const std::vector<double>& samples,
    int sampleRate
);