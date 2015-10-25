/*** This file is part of FragmentFramework project ***/

#ifndef FFW_IMAGE_UTILS
#define FFW_IMAGE_UTILS

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	class imageLoader;
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Loads an image file
	 * @details The correct image format loader is automatically chosen
	 */
	bool FFW_API loadImage(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Loads an image file
	 * @details The correct image format loader is automatically chosen
	 */
	bool FFW_API loadImage(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Returns the correct image format loader based on file extension
	 */
	FFW_API ffw::imageLoader* getImageLoader(const std::string& Path);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Returns the correct image format loader based on file extension
	 */
	FFW_API ffw::imageLoader* getImageLoader(const std::wstring& Path);
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Returns the correct image format loader based on file extension
	 */
    bool FFW_API getOpenGLFormat(imageType Type, GLenum* InternalFormat, GLenum* Format, GLenum* PixelFormat);
};
#endif

