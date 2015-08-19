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
	class oggFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa audioFileLoader
        @inherit audioFileLoader
    */
    template<> class FFW_API audioLoader<oggFile>: public audioFileLoader {
    public:
        audioLoader();
		/*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
		audioLoader(audioLoader&& Other);
        ~audioLoader();
        /*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
        bool readChunk(unsigned char* Bytes, size_t* BytesOut) override;
		/*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
            @pure
        */
		bool skipChunk(size_t* BytesOut) override;
		/*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
            @pure
        */
		bool reset() override;
		/*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof audioLoader<oggFile>
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof audioLoader<oggFile>
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
    template<> class FFW_API audioSaver<oggFile>: public audioFileSaver {
    public:
        audioSaver();
		/*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
		audioSaver(audioSaver&& Other);
        ~audioSaver();
        /*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int BitsPerSample, size_t Size, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
            @pure
        */
		bool writeFooter() override;
		/*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
            @pure
        */
		bool eof() override;
		/*!
            @memberof audioSaver<oggFile>
            @ingroup Utilities
        */
		size_t getPos() override;
		/*!
            @memberof audioSaver<oggFile>
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


