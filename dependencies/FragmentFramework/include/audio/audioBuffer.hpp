/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_AUDIO_BUFFER
#define FFW_AUDIO_BUFFER

#include "../common.h"

namespace ffw {
	class FFW_API audioBuffer{
	public:
		audioBuffer();
		virtual ~audioBuffer();

		bool create(void* Data, int BitsPerSample, size_t Size, int SampleRate, int NumChannels);
		void* getData();
		const void* getData() const;
		size_t getSize() const;
		int getSampleRate() const;
		int getBitsPerSample() const;
		int getNumOfChannels() const;
		void destroy();
	private:
		void* data;
		size_t size;
		int sampleRate;
		int bitsPerSample;
		int numChannels;
	};
};

#endif