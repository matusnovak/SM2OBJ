/*** This file is part of FragmentFramework project ***/

#ifndef FFW_LOAD_SAVE_XML
#define FFW_LOAD_SAVE_XML

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API decodeXML(const std::string& Str, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	void FFW_API encodeXML(std::string* Output, ffw::var* Var, bool Formated, bool EscapeUnicode);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadXML(const std::string& Path, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API loadXML(const std::wstring& Path, ffw::var* Output);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveXML(const std::string& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 */
	bool FFW_API saveXML(const std::wstring& Path, ffw::var* Input, bool Formated, bool EscapeUnicode);
};

#endif
