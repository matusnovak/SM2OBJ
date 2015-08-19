/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_BITMAP
#define FFW_SYS_UI_BITMAP

#include "../utilities/fileUtilities.hpp"

namespace ffw{
	class uiBitmap;

	uiBitmap FFW_API createUiBitmap(unsigned char* Pixels, int Width, int Height);
	uiBitmap FFW_API createUiBitmap(const std::wstring& Path, int Width, int Height);

	class FFW_API uiBitmap{
	public:
		uiBitmap();
		~uiBitmap();

		operator bool() const;
		bool isValid() const;

		uiBitmap(uiBitmap&& Other);
		uiBitmap& operator = (uiBitmap&& Other);

		uiBitmap& operator = (const uiBitmap& Other) = delete;
		uiBitmap(const uiBitmap& Other) = delete;

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