/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_AUDIO_DEVICE
#define FFW_AUDIO_DEVICE

#include "../common.h"

namespace ffw {
	class FFW_API audioOutputDevice{
	public:
		audioOutputDevice(const std::string& Name, int Index, int DefaultSamples, double Low, double High, int MaxChannels);
		~audioOutputDevice();

		double getLatencyLow() const;
		double getLatencyHigh() const;
		int getMaxChannels() const;
		int getIndex() const;
		const std::string& getName() const;
		int getDefaultSampleRate() const;
		bool isFormatCompatible(int Samples, int BitsPerSample, int NumOfChannels) const;
	private:
		std::string name;
		int index;
		int defaultSamples;
		double low;
		double high;
		int maxChannels;
	};

	class FFW_API audioInputDevice{
	public:
		audioInputDevice(const std::string& Name, int Index, int DefaultSamples, double Low, double High, int MaxChannels);
		~audioInputDevice();

		double getLatencyLow() const;
		double getLatencyHigh() const;
		int getMaxChannels() const;
		int getIndex() const;
		const std::string& getName() const;
		int getDefaultSampleRate() const;
		bool isFormatCompatible(int Samples, int BitsPerSample, int NumOfChannels) const;
	private:
		std::string name;
		int index;
		int defaultSamples;
		double low;
		double high;
		int maxChannels;
	};
};

#endif