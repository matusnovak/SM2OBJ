/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_IMAGE
#define FFW_LOAD_SAVE_IMAGE

#include "../config.h"
#include "../utilities/fileUtilities.hpp"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API imageFileLoader {
    public:
        imageFileLoader();
        virtual ~imageFileLoader();
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool readRow(unsigned char* Pixels) = 0;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        int getRowOffset() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        bool isOpend() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        int getWidth() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        int getHeight() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        imageType getImageType() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        int getBithDepth() const;
        /*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
        int getNumOfChannels() const;
		/*!
            @memberof imageFileLoader
            @ingroup Utilities
        */
		operator bool() const;

    protected:
		imageFileLoader(const imageFileLoader& Other) = default;
		imageFileLoader& operator = (const imageFileLoader& Other) = default;
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
    class FFW_API imageFileSaver {
    public:
        imageFileSaver();
        virtual ~imageFileSaver();
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path, int Width, int Height, imageType Type) = 0;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path, int Width, int Height, imageType Type) = 0;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
        /*!
            @memberof imageFileSaver
            @pureer
            @ingroup Utilities
        */
        virtual bool writeRow(unsigned char* Pixels) = 0;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
            @pure
        */
        virtual bool writeFooter() = 0;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        int getRowOffset() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        bool isOpend() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        int getWidth() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        int getHeight() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        imageType getImageType() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        int getBithDepth() const;
        /*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
        int getNumOfChannels() const;
		/*!
            @memberof imageFileSaver
            @ingroup Utilities
        */
		operator bool() const;

    protected:
		imageFileSaver(const imageFileSaver& Other) = default;
		imageFileSaver& operator = (const imageFileSaver& Other) = default;
        bool loaded;
        int width;
        int height;
        int rows;
        int channels;
        int bitDepth;
        imageType type;
    };

	template<class T> class imageLoader: public imageFileLoader {
	};

	template<class T> class imageSaver: public imageFileSaver {
	};
};
#endif

