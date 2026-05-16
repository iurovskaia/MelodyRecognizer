#include "database.h"

#include <fstream>
#include <iostream>

void saveFingerprint(
    const std::string& filename,
    const std::vector<int>& fingerprint
) {
    // Открываем файл для записи
    std::ofstream file(filename);

    // Проверяем, открылся ли файл
    if (!file) {
        std::cout << "Error: cannot save fingerprint to file "
                  << filename << std::endl;

        return;
    }

    // Проходим по всем числам fingerprint
    for (int i = 0; i < fingerprint.size(); i++) {

        // Записываем числа в файл через пробел
        file << fingerprint[i] << " ";
    }
}

std::vector<int> loadFingerprint(
    const std::string& filename
) {
    // Вектор для fingerprint
    std::vector<int> fingerprint;

    // Открываем файл для чтения
    std::ifstream file(filename);

    // Проверяем, открылся ли файл
    if (!file) {
        std::cout << "Error: cannot open fingerprint file "
                  << filename << std::endl;

        return fingerprint;
    }

    // Временная переменная для чтения чисел
    int value;

    // Пока файл не закончился —
    // читаем числа
    while (file >> value) {

        // Добавляем число в fingerprint
        fingerprint.push_back(value);
    }

    return fingerprint;
}

std::vector<Melody> loadDatabase(
    const std::string& databaseFile
) {
    // Вектор со всей базой мелодий
    std::vector<Melody> database;

    // Открываем файл базы данных
    std::ifstream file(databaseFile);

    // Проверяем, открылся ли файл
    if (!file) {
        std::cout << "Error: cannot open database file "
                  << databaseFile << std::endl;

        return database;
    }

    // Название мелодии
    std::string name;

    // Путь к fingerprint-файлу
    std::string fingerprintFile;

    // Читаем строки из database.txt
    while (file >> name >> fingerprintFile) {

        // Создаем новую мелодию
        Melody melody;

        // Сохраняем название
        melody.name = name;

        // Загружаем fingerprint из файла
        melody.fingerprint =
            loadFingerprint("../" + fingerprintFile);

        // Если fingerprint загрузился —
        // добавляем мелодию в базу
        if (!melody.fingerprint.empty()) {
            database.push_back(melody);
        }
    }

    return database;
}