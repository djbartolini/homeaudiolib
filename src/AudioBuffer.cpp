//
// Created by Daniel Bartolini on 5/29/24.
//

#include "../include/HAAudioBuffer.h"
#include <algorithm>

HAAudioBuffer::HAAudioBuffer(size_t size)
    : buffer(size), head(0), tail(0), bufferSize(size)
{}

size_t HAAudioBuffer::availableToWrite() const
{
    if (head >= tail)
    {
        return bufferSize - (head - tail) - 1;
    }
    else
    {
        return (tail - head) - 1;
    }
}

size_t HAAudioBuffer::availableToRead() const
{
    if (head >= tail)
    {
        return head - tail;
    }
    else
    {
        return bufferSize - (tail - head);
    }
}

void HAAudioBuffer::write(const float *data, size_t numSamples)
{
    std::lock_guard<std::mutex> lock(bufferMutex);

    if (numSamples > availableToWrite())
    {
        throw std::runtime_error(
            "Error: Not enough space in buffer to write data"
        );
    }

    for (size_t i = 0; i < numSamples; i++)
    {
        buffer[head] = data[i];
        head = (head + 1) % bufferSize;
    }
}

size_t HAAudioBuffer::read(float* data, size_t numSamples)
{
    std::lock_guard<std::mutex> lock(bufferMutex);

    size_t samplesRead = std::min(numSamples, availableToRead());

    for (size_t i = 0; i < samplesRead; i++)
    {
        data[i] = buffer[tail];
        tail = (tail + 1) % bufferSize;
    }

    return samplesRead;
}
