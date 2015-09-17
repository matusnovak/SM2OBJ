/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_OGG
#define FFW_LOAD_SAVE_OGG

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
    class FFW_API oggLoader: public audioLoader {
    public:
        oggLoader();
		/*!
            @memberof oggLoader
            @ingroup Utilities
        */
		oggLoader(oggLoader&& Other);
        ~oggLoader();
        /*!
            @memberof oggLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof oggLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof oggLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof oggLoader
            @ingroup Utilities
        */
        bool readChunk(unsigned char* Bytes, size_t* BytesOut) override;
		/*!
            @memberof oggLoader
            @ingroup Utilities
            @pure
        */
		bool skipChunk(size_t* BytesOut) override;
		/*!
            @memberof oggLoader
            @ingroup Utilities
            @pure
        */
		bool reset() override;
		/*!
            @memberof oggLoader
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof oggLoader
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof oggLoader
            @ingroup Utilities
        */
		oggLoader& operator = (oggLoader&& Other);
		// Copy constructor is not allowed
		oggLoader(const oggLoader& Other) = delete;
		// Copy assigment is not allowed
		oggLoader& operator = (const oggLoader& Other) = delete;

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
    class FFW_API oggSaver: public audioSaver {
    public:
        oggSaver();
		/*!
            @memberof oggSaver
            @ingroup Utilities
        */
		oggSaver(oggSaver&& Other);
        ~oggSaver();
        /*!
            @memberof oggSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
            @memberof oggSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
            @memberof oggSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof oggSaver
            @ingroup Utilities
        */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
            @memberof oggSaver
            @ingroup Utilities
            @pure
        */
		bool writeFooter() override;
		/*!
            @memberof oggSaver
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof oggSaver
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof oggSaver
            @ingroup Utilities
        */
		oggSaver& operator = (oggSaver&& Other);
		// Copy constructor is not allowed
		oggSaver(const oggSaver& Other) = delete;
		// Copy assigment is not allowed
		oggSaver& operator = (const oggSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
	/*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOGG(const std::string& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveOGG(const std::string& Path, unsigned char* Data, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOGG(const std::wstring& Path, unsigned char** Data, int* BitsPerSample, size_t* Size, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveOGG(const std::wstring& Path, unsigned char* Data, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500);
};
#endif


