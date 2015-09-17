/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_PNG
#define FFW_LOAD_SAVE_PNG

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
    class FFW_API pngLoader: public imageLoader {
    public:
        pngLoader();
		/*!
            @memberof pngLoader
            @ingroup Utilities
        */
		pngLoader(pngLoader&& Other);
        ~pngLoader();
        /*!
            @memberof pngLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof pngLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof pngLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof pngLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof pngLoader
            @ingroup Utilities
        */
		pngLoader& operator = (pngLoader&& Other);
		// Copy constructor is not allowed
		pngLoader(const pngLoader& Other) = delete;
		// Copy assigment is not allowed
		pngLoader& operator = (const pngLoader& Other) = delete;

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
	class FFW_API pngSaver: public imageSaver {
    public:
        pngSaver();
		/*!
            @memberof pngSaver
            @ingroup Utilities
        */
		pngSaver(pngSaver&& Other);
        ~pngSaver();
        /*!
            @memberof pngSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof pngSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof pngSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof pngSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof pngSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof pngSaver
            @ingroup Utilities
        */
		pngSaver& operator = (pngSaver&& Other);
		// Copy constructor is not allowed
		pngSaver(const pngSaver& Other) = delete;
		// Copy assigment is not allowed
		pngSaver& operator = (const pngSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadPNG(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API savePNG(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadPNG(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API savePNG(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif


