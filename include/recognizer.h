#pragma once
#include <string>
#include <vector>
#include <utility>

std::string recognizeMelody(
    const std::vector<int>& query,
    const std::vector<std::pair<std::string, std::vector<int>>>& database
);