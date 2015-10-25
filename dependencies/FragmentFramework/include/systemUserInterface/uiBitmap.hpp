/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_BITMAP
#define FFW_SYS_UI_BITMAP

#include "../common.h"

/*!
 * @ingroup User-Interface
 */
namespace ffw{
	class uiBitmap;
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	uiBitmap FFW_API createUiBitmap(unsigned char* Pixels, int Width, int Height);
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	uiBitmap FFW_API createUiBitmap(const std::wstring& Path, int Width, int Height);
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	class FFW_API uiBitmap{
	public:
		uiBitmap();
		uiBitmap(uiBitmap&& Other);
		uiBitmap(const uiBitmap& Other) = delete;
		~uiBitmap();
		/*!
		 * @memberof uiBitmap
		 * @ingroup User-Interface
		 * @const
		 */
		operator bool() const;
		/*!
		 * @memberof uiBitmap
		 * @ingroup User-Interface
		 * @const
		 */
		bool isValid() const;
		/*!
		 * @memberof uiBitmap
		 * @ingroup User-Interface
		 */
		uiBitmap& operator = (uiBitmap&& Other);
		/*!
		 * @memberof uiBitmap
		 * @ingroup User-Interface
		 */
		uiBitmap& operator = (const uiBitmap& Other) = delete;

		friend class uiWidget;
		friend class uiWindow;
		friend class uiIcon;
		friend class uiIconToggle;
		friend class uiStaticImage;
		friend uiBitmap FFW_API createUiBitmap(unsigned char* Pixels, int Width, int Height);
		friend uiBitmap FFW_API createUiBitmap(const std::wstring& Path, int Width, int Height);
	private:
		void* data;
	};
};
#endif