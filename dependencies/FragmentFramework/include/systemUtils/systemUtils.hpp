/*** This file is part of FragmentFramework project ***/

#ifndef FFW_SYS_UTILS
#define FFW_SYS_UTILS

#include "../common.h"

/*!
 * @defgroup System-Utilities
 */



/*!
 * @ingroup System-Utilities
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	std::wstring FFW_API openFileDialog(const std::wstring& title, const std::wstring& Path);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	std::wstring FFW_API openFolderDialog(const std::wstring& title, const std::wstring& Path);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	void FFW_API openExplorer(const std::string& path);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	void FFW_API createDirectory(const std::string& path);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	std::string FFW_API getClipboard();
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	std::wstring FFW_API getClipboardWstr();
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	void FFW_API setClipboard(const std::string& Str);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	void FFW_API setClipboard(const std::wstring& Str);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	bool FFW_API captureScreen(unsigned char** pixels, int* width, int* height);
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	std::string FFW_API getExecutablePath();
};
#endif
