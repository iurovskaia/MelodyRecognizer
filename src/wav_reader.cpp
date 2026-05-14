#include "wav_reader.h"

#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>

AudioData readWav(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); //открываем файл

    if (!file) {
        std::cout << "Cannot open file: " << filename << std::endl;
        return {0, {}};
    }

    char riff[4];
    file.read(riff, 4); //сюда копируем первые 4 символа

    if (std::strncmp(riff, "RIFF", 4) != 0) { //если их нет, то неверный формат файла
        std::cout << "This is not a RIFF file" << std::endl;
        return {0, {}};
    }

    file.ignore(4); //следующие 4 символа это размер файла, скип

    char wave[4];
    file.read(wave, 4); //следующие 4 символа в айле это WAVE

    if (std::strncmp(wave, "WAVE", 4) != 0) {
        std::cout << "This is not a WAVE file" << std::endl;
        return {0, {}};
    }

    int sampleRate = 0; //частота дискретизации
    short numChannels = 0; //количество каналов
    short bitsPerSample = 0; //битность
    short audioFormat = 0; //формат wav

    char chunkName[4]; //имя блока
    int chunkSize = 0; //размер блока

    while (file.read(chunkName, 4)) {
        file.read(reinterpret_cast<char*>(&chunkSize), 4);

        if (std::strncmp(chunkName, "fmt ", 4) == 0) {
            file.read(reinterpret_cast<char*>(&audioFormat), 2);
            file.read(reinterpret_cast<char*>(&numChannels), 2);
            file.read(reinterpret_cast<char*>(&sampleRate), 4);

            file.ignore(6);

            file.read(reinterpret_cast<char*>(&bitsPerSample), 2);

            if (chunkSize > 16) {
                file.ignore(chunkSize - 16);
            }
        }
            //блок data
        else if (std::strncmp(chunkName, "data", 4) == 0) {
            if (audioFormat != 1 || bitsPerSample != 16) {
                std::cout << "Only 16-bit PCM WAV is supported" << std::endl;
                return {0, {}};
            }

            std::vector<double> samples;
            //сколько байт один семпл
            int bytesPerSample = bitsPerSample / 8;
            //сколько всего
            int totalSamples = chunkSize / bytesPerSample / numChannels;

            for (int i = 0; i < totalSamples; i++) {
                double value = 0.0;

                for (int ch = 0; ch < numChannels; ch++) {
                    short sample = 0;

                    file.read(
                        reinterpret_cast<char*>(&sample),
                        sizeof(sample)
                    );

                    value += sample / 32768.0;
                }

                value = value / numChannels;
                samples.push_back(value);
            }

            return {sampleRate, samples};
        }

        else {
            file.ignore(chunkSize);
        }
    }

    std::cout << "Data block was not found" << std::endl;
    return {0, {}};
}