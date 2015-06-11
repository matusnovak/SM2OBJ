/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_WAV
#define FFW_LOAD_SAVE_WAV

#include "../dll.h"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities

        @brief Loads WAV file

        @details Loads audio data from WAV file. RIFF formal only.

        @param [in]  Path          Path to file
        @param [out] Data          Where to store buffer
        @param [out] BitsPerSample Where to store bits per sample
        @param [out] Size          Where to store total buffer size
        @param [out] ByteRate      Where to store byte rate
        @param [out] SampleRate    Where to store sample rate (frequency)
        @param [out] NumChannels   Where to store number of channels

        @return True on success

        @see saveWAV()

        @code
        // Example for loading WAV file
        unsigned char* audioData;
        int bitsPerSample;
        size_t audioBufferSize;
        int audioByteRate;
        int audioSampleRate;
        int audioChannels;
        bool result = ffw::loadWAV("data/myaudiofile.wav", &audioData, &bitsPerSample,
                      &audioBufferSize, &audioByteRate &audioSampleRate, &audioChannels);
        if(result){
            // Success
            // Use audio data here, upload it into sound buffer or do anything you want
            // After you are done delete the data
            delete[] audioData;
        } else {
            // Loading audio file failed
        }
        @endcode
    */
	bool FFW_API loadWAV(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveWAV(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadWAV(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* ByteRate, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveWAV(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int ByteRate, int SampleRate, int NumChannels);
};

#endif
