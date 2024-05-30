//
// Created by Daniel Bartolini on 5/29/24.
//


#include "../include/HAAudioIO.h"

HAAudioIO::HAAudioIO(HAAudioBuffer& buffer)
        : audioBuffer(buffer)
{
    AudioStreamBasicDescription format;
    format.mSampleRate = 44100;
    format.mFormatID = kAudioFormatLinearPCM;
    format.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked;
    format.mBytesPerPacket = 4;
    format.mFramesPerPacket = 1;
    format.mBytesPerFrame = 4;
    format.mChannelsPerFrame = 1;
    format.mBitsPerChannel = 32;

    AudioQueueNewOutput(
        &format,
        AudioCallback,
        this,
        nullptr,
        nullptr,
        0,
        &audioQueue
    );
}

HAAudioIO::~HAAudioIO()
{
    stop();
    AudioQueueDispose(audioQueue, true);
}

void HAAudioIO::start()
{
    AudioQueueStart(audioQueue, nullptr);
}

void HAAudioIO::stop()
{
    AudioQueueStop(audioQueue, true);
}

void HAAudioIO::AudioCallback(
    void* userData,
    AudioQueueRef queue,
    AudioQueueBufferRef buffer
)
{
    HAAudioIO* audioIO = static_cast<HAAudioIO*>(userData);
    size_t numSamples = buffer->mAudioDataBytesCapacity / sizeof(float);

    size_t samplesRead = audioIO->audioBuffer.read(static_cast<float*>(buffer->mAudioData), numSamples);

    buffer->mAudioDataByteSize = samplesRead * sizeof(float);
    AudioQueueEnqueueBuffer(queue, buffer, 0, nullptr);
}
