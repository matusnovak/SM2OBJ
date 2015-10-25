/*** This file is part of FragmentFramework project ***/

#ifndef FFW_LOAD_SAVE_JSON
#define FFW_LOAD_SAVE_JSON

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API decodeJSON(const std::string& Str, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	void FFW_API encodeJSON(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadJSON(const std::string& Path, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadJSON(const std::wstring& Path, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveJSON(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveJSON(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
};

#endif
