/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_WAV
#define FFW_LOAD_SAVE_WAV

#include "audioFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	class wavFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa audioFileLoader
        @inherit audioFileLoader
    */
    template<> class FFW_API audioLoader<wavFile>: public audioFileLoader {
    public:
        audioLoader();
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
		audioLoader(audioLoader&& Other);
        ~audioLoader();
        /*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
        bool readChunk(unsigned char* Data, size_t* BytesOut) override;
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
		bool skipChunk(size_t* BytesOut) override;
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
            @pure
        */
		bool reset() override;
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof audioLoader<wavFile>
            @ingroup Utilities
        */
		audioLoader& operator = (audioLoader&& Other);
		// Copy constructor is not allowed
		audioLoader(const audioLoader& Other) = delete;
		// Copy assigment is not allowed
		audioLoader& operator = (const audioLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa audioFileLoader
        @inherit audioFileLoader
    */
    template<> class FFW_API audioSaver<wavFile>: public audioFileSaver {
    public:
        audioSaver();
		/*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
		audioSaver(audioSaver&& Other);
        ~audioSaver();
        /*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500000) override;
        /*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500000) override;
        /*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
            @pure
        */
		bool writeFooter() override;
		/*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof audioSaver<wavFile>
            @ingroup Utilities
        */
		audioSaver& operator = (audioSaver&& Other);
		// Copy constructor is not allowed
		audioSaver(const audioSaver& Other) = delete;
		// Copy assigment is not allowed
		audioSaver& operator = (const audioSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
	/*!
        @memberof ffw
        @ingroup Utilities

        @brief Loads WAV file

        @details Loads audio data from WAV file. RIFF formal only.

        @param [in]  Path          Path to file
        @param [out] Data          Where to store buffer
        @param [out] BitsPerSample Where to store bits per sample
        @param [out] Size          Where to store total buffer size
        @param [out] SampleRate    Where to store sample rate (frequency)
        @param [out] NumChannels   Where to store number of channels

        @return True on success

        @see saveWAV()
    */
	bool FFW_API loadWAV(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveWAV(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int SampleRate, int NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadWAV(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveWAV(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int SampleRate, int NumChannels);
};

#endif
