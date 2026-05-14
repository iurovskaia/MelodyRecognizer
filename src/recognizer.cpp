#include "recognizer.h"

int compareFingerprints(
    const std::vector<int>& first,
    const std::vector<int>& second
) {
    int score = 0; //считаем количество совпадений

    int size = first.size();

    if (second.size() < first.size()) {
        size = second.size();
    }

    for (int i = 0; i < size; i++) {
        if (first[i] == second[i]) {
            score++;
        }
    }

    return score;
}

std::string recognizeMelody(
    const std::vector<int>& query,
    const std::vector<Melody>& database
) {
    std::string bestName = "Unknown";
    int bestScore = -1; //изначально нет совпадений

    for (int i = 0; i < database.size(); i++) { //идем по всем мелодиям в базе
        int score = compareFingerprints(
            query,
            database[i].fingerprint
        );

        if (score > bestScore) { //сравниваем текущий тпечаток с лучшим вариантом
            bestScore = score;
            bestName = database[i].name;
        }
    }

    return bestName; //наилучшее совпадение
}