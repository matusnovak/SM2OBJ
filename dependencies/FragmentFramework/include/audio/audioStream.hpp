/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_AUDIO_STREAM
#define FFW_AUDIO_STREAM

#include "../common.h"
#include "audioDevice.hpp"
#include "audioBuffer.hpp"

namespace ffw {
	class FFW_API audioOutputStream{
	public:
		audioOutputStream();
		virtual ~audioOutputStream();

		bool create(const audioOutputDevice* Device, int BitsPerSample, int SampleRate, int NumOfChannels, int QueueSize);
		bool queueBuffer(audioBuffer* Buffer);
		bool unqueueBuffer(audioBuffer** Buffer);
		void destroy();
		bool isCreated() const;
		bool play();
		bool stop();
		bool isPlaying() const;
		float getTime() const;
		unsigned long long getTimeBytes() const;
		void setGain(float Gain);
		float getGain() const;
		int getBitsPerSample() const;
		int getSampleRate() const;
		int getNumOfChannels() const;
		int getQueueSize() const;
	private:
		class impl;
		impl* pimpl;
	};
};

#endif