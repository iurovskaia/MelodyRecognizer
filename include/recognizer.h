#pragma once

#include <string>
#include <vector>

#include "database.h"

int compareFingerprints(
    const std::vector<int>& query,
    const std::vector<int>& candidate
);

std::string recognizeMelody(
    const std::vector<int>& query,
    const std::vector<Melody>& database
);