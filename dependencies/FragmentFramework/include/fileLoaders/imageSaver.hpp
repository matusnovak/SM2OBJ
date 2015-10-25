/*** This file is part of FragmentFramework project ***/

#ifndef FFW_IMAGE_SAVER
#define FFW_IMAGE_SAVER

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
    class FFW_API imageSaver {
    public:
        imageSaver();
        virtual ~imageSaver();
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for writing
         */
        virtual bool open(const std::string& Path, int Width, int Height, imageType Type) = 0;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for writing
         */
        virtual bool open(const std::wstring& Path, int Width, int Height, imageType Type) = 0;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Closes the file
         */
        virtual void close() = 0;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Writes a single row of pixels
         */
        virtual bool writeRow(unsigned char* Pixels) = 0;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Writes a footer
         */
        virtual bool writeFooter() = 0;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the number of rows written
         */
        int getRowOffset() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Checks if the file is open
         */
        bool isOpen() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the width of an image
         */
        int getWidth() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the height of an image
         */
        int getHeight() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the image type
         */
        imageType getImageType() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the bit depth of single channel per pixel
         */
        int getBithDepth() const;
        /*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns the number of channels
         */
        int getNumOfChannels() const;
		/*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Checks if the file is open
         */
		operator bool() const;
		/*!
         * @memberof imageSaver
         * @ingroup File-Loaders
         * @pure
		 * @brief Returns true if the first row of pixels is the top row
         */
		virtual bool firstRowIsTop() const = 0;

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

