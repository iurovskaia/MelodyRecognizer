#include <iostream>

#include "wav_reader.h"
#include "fingerprint.h"
#include "database.h"
#include "recognizer.h"

int main() {
    AudioData audio = readWav("../data/wav/test.wav");

    if (audio.samples.empty()) {
        std::cout << "Failed to read audio" << std::endl;
        return 1;
    }

    std::cout << "Building fingerprint..." << std::endl;

    std::vector<int> queryFingerprint =
        buildFingerprint(audio.samples, audio.sampleRate);

    std::cout << "Fingerprint:" << std::endl;

    for (int x : queryFingerprint) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    std::vector<std::string> names = {
        "Test song",
        "Boring song"
    };

    std::vector<std::string> files = {
        "../data/fingerprints/test_song.txt",
        "../data/fingerprints/boring_song.txt"
    };

    auto database = loadDatabase(names, files);

    std::string result =
        recognizeMelody(queryFingerprint, database);

    std::cout << std::endl;
    std::cout << "Recognized melody: "
              << result << std::endl;

    return 0;
}