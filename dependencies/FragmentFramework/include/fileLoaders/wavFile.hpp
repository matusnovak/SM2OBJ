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
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa audioLoader
        @inherit audioLoader
    */
    class FFW_API wavLoader: public audioLoader {
    public:
        wavLoader();
		/*!
            @memberof wavLoader
            @ingroup Utilities
        */
		wavLoader(wavLoader&& Other);
        ~wavLoader();
        /*!
            @memberof wavLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof wavLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof wavLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof wavLoader
            @ingroup Utilities
        */
        bool readChunk(unsigned char* Data, size_t* BytesOut) override;
		/*!
            @memberof wavLoader
            @ingroup Utilities
        */
		bool skipChunk(size_t* BytesOut) override;
		/*!
            @memberof wavLoader
            @ingroup Utilities
            @pure
        */
		bool reset() override;
		/*!
            @memberof wavLoader
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof wavLoader
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof wavLoader
            @ingroup Utilities
        */
		wavLoader& operator = (wavLoader&& Other);
		// Copy constructor is not allowed
		wavLoader(const wavLoader& Other) = delete;
		// Copy assigment is not allowed
		wavLoader& operator = (const wavLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa audioLoader
        @inherit audioLoader
    */
    class FFW_API wavSaver: public audioSaver {
    public:
        wavSaver();
		/*!
            @memberof wavSaver
            @ingroup Utilities
        */
		wavSaver(wavSaver&& Other);
        ~wavSaver();
        /*!
            @memberof wavSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500000) override;
        /*!
            @memberof wavSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500000) override;
        /*!
            @memberof wavSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof wavSaver
            @ingroup Utilities
        */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
            @memberof wavSaver
            @ingroup Utilities
            @pure
        */
		bool writeFooter() override;
		/*!
            @memberof wavSaver
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof wavSaver
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof wavSaver
            @ingroup Utilities
        */
		wavSaver& operator = (wavSaver&& Other);
		// Copy constructor is not allowed
		wavSaver(const wavSaver& Other) = delete;
		// Copy assigment is not allowed
		wavSaver& operator = (const wavSaver& Other) = delete;

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
