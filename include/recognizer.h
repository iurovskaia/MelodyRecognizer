#pragma once
#include <string>
#include <vector>
#include "database.h"

int compareFingerprints(
    const std::vector<int>& first,
    const std::vector<int>& second
);

std::string recognizeMelody(
    const std::vector<int>& query,
    const std::vector<Melody>& database
);