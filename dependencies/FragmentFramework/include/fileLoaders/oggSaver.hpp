/*** This file is part of FragmentFramework project ***/

#ifndef FFW_OGG_SAVER
#define FFW_OGG_SAVER

#include "audioSaver.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit audioSaver
	 * @brief WAV file saver
	 */
    class FFW_API oggSaver: public audioSaver {
    public:
        oggSaver();
		/*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @brief Move constructor
		 */
		oggSaver(oggSaver&& Other);
        ~oggSaver();
        /*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::string& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::wstring& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 500) override;
        /*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        void close() override;
        /*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 */
		bool writeFooter() override;
		/*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		bool eof() const override;
		/*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		size_t getPos() const override;
		/*!
		 * @memberof oggSaver
		 * @ingroup File-Loaders
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
	bool FFW_API saveOGG(const std::string& Path, unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 500);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveOGG(const std::wstring& Path, unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 500);
};
#endif


