#pragma once
#include <vector>
#include <complex>

// Считает коэффициенты Фурье для одного окна сигнала
// samples - отсчёты сигнала
// freqs - сетка частот, на которых считаем коэффициенты
// sampleRate - частота дискретизации
std::vector<std::complex<double>> fourierCoefficients(
    const std::vector<double>& samples,
    const std::vector<double>& freqs,
    int sampleRate
);

// Возвращает модули комплексных коэффициентов
std::vector<double> magnitudes(
    const std::vector<std::complex<double>>& coeffs
);

// Возвращает индекс максимального элемента
int argMax(const std::vector<double>& values);