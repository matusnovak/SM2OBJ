/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_MANAGER
#define FFW_AUDIO_MANAGER

#include "../common.h"
#include "audioDevice.hpp"

/*!
 *  @defgroup Audio
 */



/*!
 * @ingroup Audio
 */
namespace ffw {
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 * @brief Initializes the audio
	 */
	bool FFW_API initAudio();
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 * @brief Terminates the audio
	 */
	void FFW_API terminateAudio();
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 * @brief Checks if a audio context is initialized
	 */
	bool FFW_API isAudioInitialized();
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 * @brief Returns the default output device
	 */
	const FFW_API audioOutputDevice* getDefaultAudioOutputDevice();
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 * @brief Returns the default input device
	 */
	const FFW_API audioInputDevice* getDefaultAudioInputDevice();
};

#endif