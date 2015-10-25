/*** This file is part of FragmentFramework project ***/

#ifndef FFW_IMAGE_LOADER
#define FFW_IMAGE_LOADER

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Image loader base class
	 */
    class FFW_API imageLoader {
    public:
        imageLoader();
        virtual ~imageLoader();
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::string& Path) = 0;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Closes the file
         */
        virtual void close() = 0;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Reads a single row of pixels
         */
        virtual bool readRow(unsigned char* Pixels) = 0;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the number of rows read
         */
        int getRowOffset() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Checks if the file is open
         */
        bool isOpen() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the width of an image
         */
        int getWidth() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the height of an image
         */
        int getHeight() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the image type
         */
        imageType getImageType() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the bit depth of single channel per pixel
         */
        int getBithDepth() const;
        /*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the number of channels
         */
        int getNumOfChannels() const;
		/*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Checks if the file is open
         */
		operator bool() const;
		/*!
         * @memberof imageLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns true if the first row of pixels is the top row
         */
		virtual bool firstRowIsTop() const = 0;

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
};
#endif

