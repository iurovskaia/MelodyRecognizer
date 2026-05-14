#include "database.h"
#include <fstream>

void saveFingerprint(
    const std::string& filename,
    const std::vector<int>& fingerprint
) {
    std::ofstream file(filename); //открываем файл для записи

    for (int i = 0; i < fingerprint.size(); i++) { //проходим по всем числам отпечатка
        file << fingerprint[i] << " "; //записываем каждое число в файл с пробелами
    }
}

std::vector<int> loadFingerprint( 
    const std::string& filename
) {
    std::vector<int> fingerprint;

    std::ifstream file(filename); //открываем файл для чтения
    int value; //временная переменная для чтения

    while (file >> value) { //пока файл не закончился
        fingerprint.push_back(value); //добавляем число в вектор
    }

    return fingerprint;
}

std::vector<Melody> loadDatabase() { //вручную создаем базу данных из двух мелодий
    std::vector<Melody> database;

    Melody testSong;
    testSong.name = "Test song";
    testSong.fingerprint = loadFingerprint("../data/fingerprints/test_song.txt");
    database.push_back(testSong);

    Melody boringSong;
    boringSong.name = "Boring song";
    boringSong.fingerprint = loadFingerprint("../data/fingerprints/boring_song.txt");
    database.push_back(boringSong);

    return database;
}