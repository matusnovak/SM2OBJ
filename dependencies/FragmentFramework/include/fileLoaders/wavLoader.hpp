/*** This file is part of FragmentFramework project ***/

#ifndef FFW_WAV_LOADER
#define FFW_WAV_LOADER

#include "audioLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit audioLoader
	 * @brief WAV file loader
	 */
    class FFW_API wavLoader: public audioLoader {
    public:
        wavLoader();
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @brief Move constructor
		 */
		wavLoader(wavLoader&& Other);
        ~wavLoader();
        /*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::string& Path) override;
        /*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::wstring& Path) override;
        /*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        void close() override;
        /*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool readChunk(unsigned char* Bytes, size_t* BytesOut) override;
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool skipChunk(size_t* BytesOut) override;
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool reset() override;
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		bool eof() const override;
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		size_t getPos() const override;
		/*!
		 * @memberof wavLoader
		 * @ingroup File-Loaders
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
	bool FFW_API loadWAV(const std::string& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadWAV(const std::wstring& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
};

#endif
