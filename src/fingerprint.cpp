#include "fingerprint.h"
#include "fourier.h"

#include <cmath>

std::vector<double> makeFrequencyGrid() { //создаем список частот нот
    std::vector<double> freqs;

    for (int midi = 48; midi <= 84; midi++) { //формула чтобы перевести номер ноты в частоту (от 48 до 84)
        double freq =
            440.0 * std::pow(2.0, (midi - 69) / 12.0);

        freqs.push_back(freq);
    }

    return freqs;
}

std::vector<int> buildFingerprint( 
    const std::vector<double>& samples, //сюда складываем результат
    int sampleRate
) {
    std::vector<int> fingerprint;

    std::vector<double> freqs =
        makeFrequencyGrid(); //использовали функцию чтобы сделать список частот

    int windowSize =
        sampleRate / 4; //размер окна, 1/4с

    for (int start = 0; //идет по сигналу кусками продолжительностью длины окна
         start + windowSize <= samples.size();
         start += windowSize)
    {
        std::vector<double> window; //создаем окно, временный кусок сигнала

        for (int i = start;
             i < start + windowSize;
             i++)
        {
            window.push_back(samples[i]); //копируем кусок сигнала
        }

        std::vector<std::complex<double>> coeffs =
            fourierCoefficients( //считаем спектр по фурье
                window,
                freqs,
                sampleRate
            );

        std::vector<double> mags =
            magnitudes(coeffs); //амплитуда спектра

        int bestIndex =
            argMax(mags); //находим самую сильную частоту

        fingerprint.push_back(bestIndex); //запоминаем самую сильную частоту окна
    }

    return fingerprint;
}