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
	/*!
        @memberof ffw
        @ingroup Utilities
        @sa imageLoader
        @inherit imageLoader
    */
    class FFW_API pbmLoader: public imageLoader {
    public:
        pbmLoader();
		/*!
            @memberof pbmLoader
            @ingroup Utilities
        */
		pbmLoader(pbmLoader&& Other);
        ~pbmLoader();
        /*!
            @memberof pbmLoader
            @ingroup Utilities
        */
        bool open(const std::string& Path) override;
        /*!
            @memberof pbmLoader
            @ingroup Utilities
        */
        bool open(const std::wstring& Path) override;
        /*!
            @memberof pbmLoader
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof pbmLoader
            @ingroup Utilities
        */
        bool readRow(unsigned char* Pixels) override;
		/*!
            @memberof pbmLoader
            @ingroup Utilities
        */
		pbmLoader& operator = (pbmLoader&& Other);
		// Copy constructor is not allowed
		pbmLoader(const pbmLoader& Other) = delete;
		// Copy assigment is not allowed
		pbmLoader& operator = (const pbmLoader& Other) = delete;

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
    class FFW_API pbmSaver: public imageSaver {
    public:
        pbmSaver();
		/*!
            @memberof pbmSaver
            @ingroup Utilities
        */
		pbmSaver(pbmSaver&& Other);
        ~pbmSaver();
        /*!
            @memberof pbmSaver
            @ingroup Utilities
        */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof pbmSaver
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
            @memberof pbmSaver
            @ingroup Utilities
        */
        void close() override;
        /*!
            @memberof pbmSaver
            @ingroup Utilities
        */
        bool writeRow(unsigned char* Pixels) override;
        /*!
            @memberof pbmSaver
            @ingroup Utilities
        */
        bool writeFooter() override;
		/*!
            @memberof pbmSaver
            @ingroup Utilities
        */
		pbmSaver& operator = (pbmSaver&& Other);
		// Copy constructor is not allowed
		pbmSaver(const pbmSaver& Other) = delete;
		// Copy assigment is not allowed
		pbmSaver& operator = (const pbmSaver& Other) = delete;

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
