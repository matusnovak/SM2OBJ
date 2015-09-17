/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_TGA
#define FFW_LOAD_SAVE_TGA

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
	class FFW_API tgaLoader: public imageLoader {
    public:
        tgaLoader();
		/*!
            @memberof tgaLoader
            @ingroup Utilities
        */
		tgaLoader(tgaLoader&& Other);
        ~tgaLoader();
        /*!
            @memberof tgaLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof tgaLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof tgaLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof tgaLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof tgaLoader
            @ingroup Utilities
        */
		tgaLoader& operator = (tgaLoader&& Other);
		// Copy constructor is not allowed
		tgaLoader(const tgaLoader& Other) = delete;
		// Copy assigment is not allowed
		tgaLoader& operator = (const tgaLoader& Other) = delete;

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
    class FFW_API tgaSaver: public imageSaver {
    public:
        tgaSaver();
		/*!
            @memberof tgaSaver
            @ingroup Utilities
        */
		tgaSaver(tgaSaver&& Other);
        ~tgaSaver();
        /*!
            @memberof tgaSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof tgaSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof tgaSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof tgaSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof tgaSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof tgaSaver
            @ingroup Utilities
        */
		tgaSaver& operator = (tgaSaver&& Other);
		// Copy constructor is not allowed
		tgaSaver(const tgaSaver& Other) = delete;
		// Copy assigment is not allowed
		tgaSaver& operator = (const tgaSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTGA(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTGA(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadTGA(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveTGA(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif

