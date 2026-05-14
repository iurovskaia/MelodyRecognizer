#pragma once
#include <string>
#include <vector>
#include <utility>

void saveFingerprint(const std::string& melodyName, const std::vector<int>& fp);

std::vector<std::pair<std::string, std::vector<int>>> loadDatabase(const std::string& folder);