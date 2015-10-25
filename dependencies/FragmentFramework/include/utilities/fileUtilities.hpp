/*** This file is part of FragmentFramework project ***/

#ifndef FFW_FILE_UTILITIES
#define FFW_FILE_UTILITIES

#include "../common.h"

/*!
 * @ingroup Utilities
 */
namespace ffw{
    /*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Checks if file exists
	 * @param Path UTF-8 compatible path
     */
	bool FFW_API checkIfFileExists(const std::string& Path);
    /*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Checks if file exists
	 * @param Path Multi-byte compatible path
     */
	bool FFW_API checkIfFileExists(const std::wstring& Path);
    /*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Retrieves directory, name, and extension from a path
	 * @details 2nd, 3rd, and 4th parameters can be NULL.
	 * If a path does not contains file name then an empty string
	 * will be assigned to the FileName parameter. This also applies
	 * to the Directory and FileExtension parameter.
	 * @param Path UTF-8 compatible path to read from
	 * @param Directory Where to store the directory name
	 * @param FileName Where to store the file name
	 * @param FileExtension where to store the file extension
     */
	void FFW_API getFilePathProperties(const std::string& Path, std::string *Directory, std::string *FileName, std::string *FileExtension);
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Retrieves directory, name, and extension from a path
	 * @details 2nd, 3rd, and 4th parameters can be NULL.
	 * If a path does not contains file name then an empty string
	 * will be assigned to the FileName parameter. This also applies
	 * to the Directory and FileExtension parameter.
	 * @param Path Multi-byte path to read from
	 * @param Directory Where to store the directory name
	 * @param FileName Where to store the file name
	 * @param FileExtension where to store the file extension
     */
	void FFW_API getFilePathProperties(const std::wstring& Path, std::wstring *Directory, std::wstring *FileName, std::wstring *FileExtension);
};

#endif
