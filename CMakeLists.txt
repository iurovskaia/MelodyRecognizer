cmake_minimum_required(VERSION 3.10)
project(MelodyRecognizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(COMMON_SOURCES
    src/wav_reader.cpp
    src/fourier.cpp
    src/fingerprint.cpp
    src/database.cpp
    src/recognizer.cpp
)

add_executable(melody_recognizer
    main.cpp
    ${COMMON_SOURCES}
)

add_executable(update_database
    tools/update_database.cpp
    ${COMMON_SOURCES}
)