/*** This file is part of FragmentFramework project ***/

#ifndef FFW_WAV_SAVER
#define FFW_WAV_SAVER

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
    class FFW_API wavSaver: public audioSaver {
    public:
        wavSaver();
		/*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @brief Move constructor
		 */
		wavSaver(wavSaver&& Other);
        ~wavSaver();
        /*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::string& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 0) override;
        /*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::wstring& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps = 0) override;
        /*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        void close() override;
        /*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 */
        bool writeChunk(unsigned char* Data, size_t* BytesWritten) override;
		/*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 */
		bool writeFooter() override;
		/*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		bool eof() const override;
		/*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		size_t getPos() const override;
		/*!
		 * @memberof wavSaver
		 * @ingroup File-Loaders
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
    */
	bool FFW_API saveWAV(const std::string& Path, unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveWAV(const std::wstring& Path, unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumChannels);
};

#endif
