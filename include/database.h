#pragma once
#include <string>
#include <vector>

struct Melody {
    //структура: название + отпечаток
    std::string name;
    std::vector<int> fingerprint;
};

void saveFingerprint(
    //сохранить отпечаток в файл
    const std::string& filename,
    const std::vector<int>& fingerprint
);

std::vector<int> loadFingerprint(
    //читает отпечаток из файла
    const std::string& filename
);

std::vector<Melody> loadDatabase(); 
//загрузить всю базу данных