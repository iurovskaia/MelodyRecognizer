#include <iostream>
#include <string>
#include <vector>

#include "wav_reader.h"
#include "fingerprint.h"
#include "database.h"
#include "recognizer.h"

int main() {
    // Путь к WAV-файлу, который хотим распознать
    std::string inputFile = "../data/wav/query/query.wav";

    // Путь к файлу базы данных
    std::string databaseFile = "../data/database.txt";

    // Считываем WAV-файл и получаем аудиосигнал
    AudioData audio = readWav(inputFile);

    // Проверяем, удалось ли считать файл
    if (audio.samples.empty()) {
        std::cout << "Error: could not read input WAV file" << std::endl;
        return 1;
    }

    // Строим отпечаток для входного сигнала
    std::vector<int> queryFingerprint =
        buildFingerprint(audio.samples, audio.sampleRate);

    // Проверяем, получилось ли построить отпечаток
    if (queryFingerprint.empty()) {
        std::cout << "Error: fingerprint is empty" << std::endl;
        return 1;
    }

    // Сохраняем отпечаток входного файла,
    // чтобы можно было посмотреть его вручную
    saveFingerprint(
        "../data/fingerprints/query.txt",
        queryFingerprint
    );

    // Загружаем базу данных мелодий
    std::vector<Melody> database =
        loadDatabase(databaseFile);

    // Проверяем, что база данных не пустая
    if (database.empty()) {
        std::cout << "Error: database is empty" << std::endl;
        return 1;
    }

    // Сравниваем входной отпечаток с базой
    // и получаем название самой похожей мелодии
    std::string result =
        recognizeMelody(queryFingerprint, database);

    // Выводим результат
    std::cout << "Recognized melody: "
              << result << std::endl;

    return 0;
}