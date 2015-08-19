/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_TIFF
#define FFW_LOAD_SAVE_TIFF

#include "imageFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	class tiffFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageFileLoader
        @inherit imageFileLoader
    */
    template <> class FFW_API imageLoader<tiffFile>: public imageFileLoader {
    public:
        imageLoader();
		/*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
		imageLoader(imageLoader&& Other);
        ~imageLoader();
        /*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof imageLoader<tiffFile>
            @ingroup Utilities
        */
		imageLoader& operator = (imageLoader&& Other);
		// Copy constructor is not allowed
		imageLoader(const imageLoader& Other) = delete;
		// Copy assigment is not allowed
		imageLoader& operator = (const imageLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };

    /*!
        @memberof ffw
        @ingroup Utilities
        @sa imageFileSaver
        @inherit imageFileSaver
    */
    template <> class FFW_API imageSaver<tiffFile>: public imageFileSaver {
    public:
        imageSaver();
		/*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
		imageSaver(imageSaver&& Other);
        ~imageSaver();
        /*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof imageSaver<tiffFile>
            @ingroup Utilities
        */
		imageSaver& operator = (imageSaver&& Other);
		// Copy constructor is not allowed
		imageSaver(const imageSaver& Other) = delete;
		// Copy assigment is not allowed
		imageSaver& operator = (const imageSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTIFF(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTIFF(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTIFF(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTIFF(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif


