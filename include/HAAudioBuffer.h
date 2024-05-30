//
// Created by Daniel Bartolini on 5/29/24.
//
// Manages audio data in a circular buffer,
// providing thread-safe write and read operations
//

#ifndef HOMEAUDIOLIB_HAAUDIOBUFFER_H
#define HOMEAUDIOLIB_HAAUDIOBUFFER_H

#include <vector>
#include <mutex>
#include <stdexcept>

class HAAudioBuffer
{
public:
    HAAudioBuffer(size_t size);

    void write(const float* data, size_t numSamples);
    size_t read(float* data, size_t numSamples);

private:
    std::vector<float> buffer;
    size_t head;
    size_t tail;
    size_t bufferSize;
    std::mutex bufferMutex;

    size_t availableToWrite() const;
    size_t availableToRead() const;
};

#endif //HOMEAUDIOLIB_HAAUDIOBUFFER_H
