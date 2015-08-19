/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_PBM
#define FFW_LOAD_SAVE_PBM

#include "imageFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	class pbmFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageFileLoader
        @inherit imageFileLoader
    */
    template<> class FFW_API imageLoader<pbmFile>: public imageFileLoader {
    public:
        imageLoader();
		/*!
            @memberof imageLoader<pbmFile>
            @ingroup Utilities
        */
		imageLoader(imageLoader&& Other);
        ~imageLoader();
        /*!
            @memberof imageLoader<pbmFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof imageLoader<pbmFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof imageLoader<pbmFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageLoader<pbmFile>
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof imageLoader<pbmFile>
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
    template<> class FFW_API imageSaver<pbmFile>: public imageFileSaver {
    public:
        imageSaver();
		/*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
		imageSaver(imageSaver&& Other);
        ~imageSaver();
        /*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof imageSaver<pbmFile>
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof imageSaver<pbmFile>
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
	bool FFW_API loadPBM(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API savePBM(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadPBM(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API savePBM(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
