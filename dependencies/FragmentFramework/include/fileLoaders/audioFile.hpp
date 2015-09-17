/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_AUDIO
#define FFW_LOAD_SAVE_AUDIO

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API audioLoader {
    public:
        audioLoader();
        virtual ~audioLoader();
        /*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
        virtual bool readChunk(unsigned char* Bytes, size_t* BytesOut) = 0;
		/*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
		virtual bool skipChunk(size_t* BytesOut) = 0;
		/*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
		virtual bool reset() = 0;
		/*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
		virtual bool eof() = 0;
		/*!
            @memberof audioLoader
            @ingroup Utilities
            @pure
        */
		virtual size_t getPos() = 0;
        /*!
            @memberof audioLoader
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		size_t getSize() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		int getSampleRate() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		int getNumOfChannels() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		int getBitsPerSample() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		size_t getChunkSize() const;
		/*!
            @memberof audioLoader
            @ingroup Utilities
        */
		operator bool () const;

    protected:
		audioLoader(const audioLoader& Other) = default;
		audioLoader& operator = (const audioLoader& Other) = default;
        bool loaded;
        size_t size;
        int sampleRate;
        int channelCount;
        int bitsPerSample;
		size_t chunkSize;
    };

	/*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API audioSaver {
    public:
        audioSaver();
        virtual ~audioSaver();
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual bool writeChunk(unsigned char* Data, size_t* BytesWritten) = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual bool writeFooter() = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual void close() = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual bool eof() = 0;
		/*!
            @memberof audioSaver
            @ingroup Utilities
            @pure
        */
		virtual size_t getPos() = 0;
        /*!
            @memberof audioSaver
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		size_t getSize() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		int getSampleRate() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		int getNumOfChannels() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		int getBitsPerSample() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		size_t getChunkSize() const;
		/*!
            @memberof audioSaver
            @ingroup Utilities
        */
		operator bool () const;
	protected:
		audioSaver(const audioSaver& Other) = default;
		audioSaver& operator = (const audioSaver& Other) = default;
		bool loaded;
        size_t size;
        int sampleRate;
        int channelCount;
        int bitsPerSample;
		size_t chunkSize;
	};
};
#endif

