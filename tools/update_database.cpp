#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "wav_reader.h"
#include "fingerprint.h"
#include "database.h"

int main() {
    // Папка, где лежат WAV-файлы мелодий базы
    std::string wavFolder = "../data/wav/database/";

    // Папка, куда будем сохранять отпечатки мелодий
    std::string fingerprintFolder = "../data/fingerprints/";

    // Файл, где будет храниться список мелодий базы
    std::string databaseFile = "../data/database.txt";

    // Открываем database.txt для записи
    // Если файла не было, он создастся
    // Если файл уже был, он перезапишется
    std::ofstream database(databaseFile);

    // Проверяем, получилось ли открыть файл базы
    if (!database) {
        std::cout << "Cannot create database file" << std::endl;
        return 1;
    }

    // Проходим по всем файлам в папке с WAV-файлами
    for (const auto& entry : std::filesystem::directory_iterator(wavFolder)) {

        // Берём только файлы с расширением .wav
        if (entry.path().extension() == ".wav") {

            // Полный путь к текущему WAV-файлу
            std::string wavPath = entry.path().string();

            // Имя мелодии берём из имени файла без расширения
            // Например: song1.wav -> song1
            std::string melodyName = entry.path().stem().string();

            // Путь, куда сохраним отпечаток этой мелодии
            std::string fingerprintPath =
                fingerprintFolder + melodyName + ".txt";

            std::cout << "Processing: " << wavPath << std::endl;

            // Считываем WAV-файл
            AudioData audio = readWav(wavPath);

            // Если файл не удалось прочитать, пропускаем его
            if (audio.samples.empty()) {
                std::cout << "Cannot read this file, skipped" << std::endl;
                continue;
            }

            // Строим отпечаток по аудиосигналу
            std::vector<int> fingerprint =
                buildFingerprint(audio.samples, audio.sampleRate);

            // Сохраняем отпечаток в отдельный .txt файл
            saveFingerprint(fingerprintPath, fingerprint);

            // Добавляем запись в database.txt
            // Формат строки:
            // название_мелодии путь_к_отпечатку
            database << melodyName
                     << " data/fingerprints/"
                     << melodyName
                     << ".txt"
                     << std::endl;
        }
    }

    std::cout << "Database created" << std::endl;

    return 0;
}