//
// Created by Daniel Bartolini on 5/29/24.
//
// Uses Core Audio to play the audio from the buffer.
// The AudioCallback function reads from the buffer and
// feeds data to the audio output
//

#ifndef HOMEAUDIOLIB_HAAUDIOIO_H
#define HOMEAUDIOLIB_HAAUDIOIO_H

#include <AudioToolbox/AudioToolbox.h>
#include "HAAudioBuffer.h"

class HAAudioIO
{
public:
    HAAudioIO(HAAudioBuffer& buffer);
    ~HAAudioIO();

    void start();
    void stop();

private:
    AudioQueueRef audioQueue;
    HAAudioBuffer& audioBuffer;

    static void AudioCallback(
        void* userData,
        AudioQueueRef queue,
        AudioQueueBufferRef buffer
    );
};

#endif //HOMEAUDIOLIB_HAAUDIOIO_H
