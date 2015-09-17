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
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageLoader
        @inherit imageLoader
    */
    class FFW_API tiffLoader: public imageLoader {
    public:
        tiffLoader();
		/*!
            @memberof tiffLoader
            @ingroup Utilities
        */
		tiffLoader(tiffLoader&& Other);
        ~tiffLoader();
        /*!
            @memberof tiffLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof tiffLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof tiffLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof tiffLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof tiffLoader
            @ingroup Utilities
        */
		tiffLoader& operator = (tiffLoader&& Other);
		// Copy constructor is not allowed
		tiffLoader(const tiffLoader& Other) = delete;
		// Copy assigment is not allowed
		tiffLoader& operator = (const tiffLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };

    /*!
        @memberof ffw
        @ingroup Utilities
        @sa imageSaver
        @inherit imageSaver
    */
    class FFW_API tiffSaver: public imageSaver {
    public:
        tiffSaver();
		/*!
            @memberof tiffSaver
            @ingroup Utilities
        */
		tiffSaver(tiffSaver&& Other);
        ~tiffSaver();
        /*!
            @memberof tiffSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof tiffSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof tiffSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof tiffSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof tiffSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof tiffSaver
            @ingroup Utilities
        */
		tiffSaver& operator = (tiffSaver&& Other);
		// Copy constructor is not allowed
		tiffSaver(const tiffSaver& Other) = delete;
		// Copy assigment is not allowed
		tiffSaver& operator = (const tiffSaver& Other) = delete;

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


