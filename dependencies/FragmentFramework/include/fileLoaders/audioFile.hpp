/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_AUDIO
#define FFW_LOAD_SAVE_AUDIO

#include "../config.h"
#include "../utilities/fileUtilities.hpp"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API audioFileLoader {
    public:
        audioFileLoader();
        virtual ~audioFileLoader();
        /*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool readChunk(unsigned char* Bytes, size_t* BytesOut) = 0;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool skipChunk(size_t* BytesOut) = 0;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool reset() = 0;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool eof() = 0;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
            @pure
        */
		virtual size_t getPos() = 0;
        /*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		size_t getSize() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		int getSampleRate() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		int getNumOfChannels() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		int getBitsPerSample() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		size_t getChunkSize() const;
		/*!
            @memberof audioFileLoader
            @ingroup Utilities
        */
		operator bool () const;

    protected:
		audioFileLoader(const audioFileLoader& Other) = default;
		audioFileLoader& operator = (const audioFileLoader& Other) = default;
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
    class FFW_API audioFileSaver {
    public:
        audioFileSaver();
        virtual ~audioFileSaver();
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool writeChunk(unsigned char* Data, size_t* BytesWritten) = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool writeFooter() = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual void close() = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool eof() = 0;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
            @pure
        */
		virtual size_t getPos() = 0;
        /*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		size_t getSize() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		int getSampleRate() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		int getNumOfChannels() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		int getBitsPerSample() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		size_t getChunkSize() const;
		/*!
            @memberof audioFileSaver
            @ingroup Utilities
        */
		operator bool () const;
	protected:
		audioFileSaver(const audioFileSaver& Other) = default;
		audioFileSaver& operator = (const audioFileSaver& Other) = default;
		bool loaded;
        size_t size;
        int sampleRate;
        int channelCount;
        int bitsPerSample;
		size_t chunkSize;
	};

	template<class T> class audioLoader: public audioFileLoader {
	};

	template<class T> class audioSaver: public audioFileSaver {
	};
};
#endif

