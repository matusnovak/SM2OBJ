/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_UTILS
#define FFW_AUDIO_UTILS

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	class audioLoader;
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Loads an audio file
	 * @details The correct audio format loader is automatically chosen
	 */
	bool FFW_API loadAudio(const std::string& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Loads an audio file
	 * @details The correct audio format loader is automatically chosen
	 */
	bool FFW_API loadAudio(const std::wstring& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Returns the correct audio format loader based on file extension
	 */
	FFW_API ffw::audioLoader* getAudioLoader(const std::string& Path);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Returns the correct audio format loader based on file extension
	 */
	FFW_API ffw::audioLoader* getAudioLoader(const std::wstring& Path);
};
#endif

