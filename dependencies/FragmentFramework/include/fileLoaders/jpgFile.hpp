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
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageLoader
        @inherit imageLoader
    */
	class FFW_API jpgLoader: public imageLoader {
    public:
        jpgLoader();
		/*!
            @memberof jpgLoader
            @ingroup Utilities
        */
		jpgLoader(jpgLoader&& Other);
        ~jpgLoader();
        /*!
            @memberof jpgLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof jpgLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof jpgLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof jpgLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof jpgLoader
            @ingroup Utilities
        */
		jpgLoader& operator = (jpgLoader&& Other);
		// Copy constructor is not allowed
		jpgLoader(const jpgLoader& Other) = delete;
		// Copy assigment is not allowed
		jpgLoader& operator = (const jpgLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };

    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API jpgSaver: public imageSaver {
    public:
        jpgSaver();
		/*!
            @memberof jpgSaver
            @ingroup Utilities
        */
		jpgSaver(jpgSaver&& Other);
        ~jpgSaver();
        /*!
            @memberof jpgSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof jpgSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof jpgSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof jpgSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof jpgSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof jpgSaver
            @ingroup Utilities
        */
		jpgSaver& operator = (jpgSaver&& Other);
		// Copy constructor is not allowed
		jpgSaver(const jpgSaver& Other) = delete;
		// Copy assigment is not allowed
		jpgSaver& operator = (const jpgSaver& Other) = delete;

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
