#include "recognizer.h"

// Сравниваем два fingerprint с помощью алгоритма
// наибольшей общей подпоследовательности.
//
// Идея:
// если query является фрагментом песни или немного отличается,
// мы всё равно сможем найти похожую последовательность внутри candidate.
int compareFingerprints(
    const std::vector<int>& query,
    const std::vector<int>& candidate
) {
    // Размер входного fingerprint
    int n = query.size();

    // Размер fingerprint мелодии из базы
    int m = candidate.size();

    // Если один из fingerprint пустой,
    // сравнивать нечего
    if (n == 0 || m == 0) {
        return 0;
    }

    // dp[i][j] — длина наибольшей общей подпоследовательности
    // для первых i элементов query
    // и первых j элементов candidate
    std::vector<std::vector<int>> dp(
        n + 1,
        std::vector<int>(m + 1, 0)
    );

    // Заполняем таблицу dp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // Если текущие элементы совпали,
            // увеличиваем длину общей подпоследовательности
            if (query[i - 1] == candidate[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }

            // Если элементы не совпали,
            // берём лучший результат из двух вариантов:
            // 1) пропустить элемент из query
            // 2) пропустить элемент из candidate
            else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }

    // В правом нижнем углу таблицы лежит ответ:
    // длина наибольшей общей подпоследовательности
    return dp[n][m];
}

// Функция ищет мелодию из базы,
// fingerprint которой лучше всего совпадает с query.
std::string recognizeMelody(
    const std::vector<int>& query,
    const std::vector<Melody>& database
) {
    // Пока считаем, что ничего не распознали
    std::string bestName = "Unknown";

    // Лучший score пока минимальный
    int bestScore = -1;

    // Проходим по всем мелодиям в базе
    for (int i = 0; i < database.size(); i++) {

        // Сравниваем входной fingerprint
        // с fingerprint текущей мелодии из базы
        int score = compareFingerprints(
            query,
            database[i].fingerprint
        );

        // Если текущая мелодия похожа больше всех предыдущих,
        // запоминаем её
        if (score > bestScore) {
            bestScore = score;
            bestName = database[i].name;
        }
    }

    // Возвращаем название самой похожей мелодии
    return bestName;
}