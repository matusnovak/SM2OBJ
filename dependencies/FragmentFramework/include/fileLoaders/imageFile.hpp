/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_IMAGE
#define FFW_LOAD_SAVE_IMAGE

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API imageLoader {
    public:
        imageLoader();
        virtual ~imageLoader();
        /*!
            @memberof imageLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof imageLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof imageLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof imageLoader
            @ingroup Utilities
            @pure
        */
        virtual bool readRow(unsigned char* Pixels) = 0;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        int getRowOffset() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        bool isOpend() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        int getWidth() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        int getHeight() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        imageType getImageType() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        int getBithDepth() const;
        /*!
            @memberof imageLoader
            @ingroup Utilities
        */
        int getNumOfChannels() const;
		/*!
            @memberof imageLoader
            @ingroup Utilities
        */
		operator bool() const;

    protected:
		imageLoader(const imageLoader& Other) = default;
		imageLoader& operator = (const imageLoader& Other) = default;
        bool loaded;
        int rows;
        int width;
        int height;
        int channels;
        int bitDepth;
        imageType type;
    };

    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API imageSaver {
    public:
        imageSaver();
        virtual ~imageSaver();
        /*!
            @memberof imageSaver
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path, int Width, int Height, imageType Type) = 0;
        /*!
            @memberof imageSaver
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path, int Width, int Height, imageType Type) = 0;
        /*!
            @memberof imageSaver
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof imageSaver
            @pureer
            @ingroup Utilities
        */
        virtual bool writeRow(unsigned char* Pixels) = 0;
        /*!
            @memberof imageSaver
            @ingroup Utilities
            @pure
        */
        virtual bool writeFooter() = 0;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        int getRowOffset() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        bool isOpend() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        int getWidth() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        int getHeight() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        imageType getImageType() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        int getBithDepth() const;
        /*!
            @memberof imageSaver
            @ingroup Utilities
        */
        int getNumOfChannels() const;
		/*!
            @memberof imageSaver
            @ingroup Utilities
        */
		operator bool() const;

    protected:
		imageSaver(const imageSaver& Other) = default;
		imageSaver& operator = (const imageSaver& Other) = default;
        bool loaded;
        int width;
        int height;
        int rows;
        int channels;
        int bitDepth;
        imageType type;
    };
};
#endif

