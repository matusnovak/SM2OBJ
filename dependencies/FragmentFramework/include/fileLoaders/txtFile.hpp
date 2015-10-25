/*** This file is part of FragmentFramework project ***/

#ifndef FFW_LOAD_SAVE_TXT
#define FFW_LOAD_SAVE_TXT

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadTXT(const std::string& path, std::string* data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveTXT(const std::string& path, const std::string& data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadTXT(const std::string& path, std::vector<std::string>* data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveTXT(const std::string& path, const std::vector<std::string>& data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadTXT(const std::wstring& path, std::string* data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveTXT(const std::wstring& path, const std::string& data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadTXT(const std::wstring& path, std::vector<std::string>* data);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveTXT(const std::wstring& path, const std::vector<std::string>& data);
};
#endif
