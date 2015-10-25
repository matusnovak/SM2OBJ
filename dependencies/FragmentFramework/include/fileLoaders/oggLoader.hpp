/*** This file is part of FragmentFramework project ***/

#ifndef FFW_OGG_LOADER
#define FFW_OGG_LOADER

#include "audioLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit audioLoader
	 * @brief OGG file loader
	 */
    class FFW_API oggLoader: public audioLoader {
    public:
        oggLoader();
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @brief Move constructor
		 */
		oggLoader(oggLoader&& Other);
        ~oggLoader();
        /*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::string& Path) override;
        /*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool open(const std::wstring& Path) override;
        /*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        void close() override;
        /*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
        bool readChunk(unsigned char* Bytes, size_t* BytesOut) override;
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool skipChunk(size_t* BytesOut) override;
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool reset() override;
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		bool eof() const override;
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		size_t getPos() const override;
		/*!
		 * @memberof oggLoader
		 * @ingroup File-Loaders
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
    */
	bool FFW_API loadOGG(const std::string& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOGG(const std::wstring& Path, unsigned char** Data, size_t* Size, int* BitsPerSample, int* SampleRate, int* NumChannels);
};
#endif


