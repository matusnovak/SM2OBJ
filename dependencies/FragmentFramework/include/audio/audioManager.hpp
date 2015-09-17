/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_AUDIO_MANAGER
#define FFW_AUDIO_MANAGER

#include "../common.h"
#include "audioDevice.hpp"

namespace ffw {
	bool FFW_API initAudio();
	void FFW_API terminateAudio();
	bool FFW_API isAudioInitialized();
	const FFW_API audioOutputDevice* getDefaultAudioOutputDevice();
	const FFW_API audioInputDevice* getDefaultAudioInputDevice();
};

#endif