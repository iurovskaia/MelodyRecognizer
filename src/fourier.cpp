#include "fourier.h"
#include <cmath>

const double PI = 3.14159265358979323846;
// функция для вычисления коэффицентов Фурье

std::vector<std::complex<double>> fourierCoefficients(
    const std::vector<double>& samples,
    const std::vector<double>& freqs,
    int sampleRate
) {
    std::vector<std::complex<double>> coeffs;
    coeffs.reserve(freqs.size());
    // считаем время, зная частоту дискретизации
    double dt = 1.0 / static_cast<double>(sampleRate);
    // имеем список частот, по которым будем раскладывать фуекцию (ноты), по формуле фурье находим комплексные коэффиценты
    for (double f : freqs) {
        std::complex<double> sum(0.0, 0.0);

        for (size_t n = 0; n < samples.size(); ++n) {
            double t = n * dt;
            double angle = 2.0 * PI * f * t;
            // формула эйлера exp(- ia) = cos (a) - i*sin (a)
            std::complex<double> expTerm(std::cos(angle), -std::sin(angle));

            sum += samples[n] * expTerm * dt;
        }

        coeffs.push_back(sum);
    }

    return coeffs;
}
// находим модуль комплексных коэффицентов (посчитанных в прошлой функции)
std::vector<double> magnitudes(
    const std::vector<std::complex<double>>& coeffs
) {
    std::vector<double> result;
    result.reserve(coeffs.size());

    for (const auto& c : coeffs) {
        result.push_back(std::abs(c));
    }

    return result;
}
// возвращается индекс максимального элемента (в списке с модулями коэффицентов фурье) то есть ищем самую сильную частоту на каждом отрезке времени
int argMax(const std::vector<double>& values) {
    if (values.empty()) return -1;

    int bestIndex = 0;

    for (int i = 1; i < values.size(); i++) {
        if (values[i] > values[bestIndex]) {
            bestIndex = i;
        }
    }

    return bestIndex;
}