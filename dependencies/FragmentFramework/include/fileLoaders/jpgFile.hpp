/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_JPG
#define FFW_LOAD_SAVE_JPG

#include "imageFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	class jpgFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageFileLoader
        @inherit imageFileLoader
    */
    template <> class FFW_API imageLoader<jpgFile>: public imageFileLoader {
    public:
        imageLoader();
		/*!
            @memberof imageLoader<jpgFile>
            @ingroup Utilities
        */
		imageLoader(imageLoader&& Other);
        ~imageLoader();
        /*!
            @memberof imageLoader<jpgFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof imageLoader<jpgFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof imageLoader<jpgFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageLoader<jpgFile>
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof imageLoader<jpgFile>
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
    */
    template <> class FFW_API imageSaver<jpgFile>: public imageFileSaver {
    public:
        imageSaver();
		/*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
		imageSaver(imageSaver&& Other);
        ~imageSaver();
        /*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof imageSaver<jpgFile>
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof imageSaver<jpgFile>
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
	bool FFW_API loadJPG(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveJPG(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadJPG(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveJPG(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
