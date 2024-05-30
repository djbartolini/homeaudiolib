#include <iostream>
#include <cmath>
#include <thread>
#include "include/HAAudioBuffer.h"
#include "include/HAAudioIO.h"

int main()
{
    HAAudioBuffer audioBuffer(48000); // 1-second buffer at 44100 Hz
    HAAudioIO audioIO(audioBuffer);

    // Generate a sine wave with adjusted amplitude and frequency
    const float sampleRate = 48000.0f;
    const float duration = 5.0f; // seconds
    const float amplitude = 0.5f; // Adjust amplitude as needed
    const float frequency = 440.0f; // Adjust frequency as needed
    const size_t numSamples = static_cast<size_t>(duration * sampleRate);

    std::vector<float> audioData(numSamples);

    for (size_t i = 0; i < numSamples; i++)
    {
        audioData[i] = amplitude * sinf(2.0f * M_PI * frequency * i / sampleRate);
    }

    audioIO.start();
    std::cout << "Playing audio..." << std::endl;

    // Let it play for a while
    std::this_thread::sleep_for(std::chrono::seconds(5));

    audioIO.stop();
    std::cout << "Audio stopped." << std::endl;

    return 0;
}
