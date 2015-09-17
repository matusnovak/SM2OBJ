/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_BMP
#define FFW_LOAD_SAVE_BMP

#include "imageFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageLoader
        @inherit imageLoader
    */
    class FFW_API bmpLoader: public imageLoader {
    public:
        bmpLoader();
		/*!
            @memberof bmpLoader
            @ingroup Utilities
        */
		bmpLoader(bmpLoader&& Other);
        ~bmpLoader();
        /*!
            @memberof bmpLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof bmpLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof bmpLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof bmpLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof bmpLoader
            @ingroup Utilities
        */
		bmpLoader& operator = (bmpLoader&& Other);
		// Copy constructor is not allowed
		bmpLoader(const bmpLoader& Other) = delete;
		// Copy assigment is not allowed
		bmpLoader& operator = (const bmpLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };

    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API bmpSaver: public imageSaver {
    public:
        bmpSaver();
		/*!
            @memberof bmpSaver
            @ingroup Utilities
        */
		bmpSaver(bmpSaver&& Other);
        ~bmpSaver();
        /*!
            @memberof bmpSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof bmpSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof bmpSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof bmpSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof bmpSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof bmpSaver
            @ingroup Utilities
        */
		bmpSaver& operator = (bmpSaver&& Other);
		// Copy constructor is not allowed
		bmpSaver(const bmpSaver& Other) = delete;
		// Copy assigment is not allowed
		bmpSaver& operator = (const bmpSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadBMP(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveBMP(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadBMP(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveBMP(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
