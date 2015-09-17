/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_WINDOW
#define FFW_SYS_UI_WINDOW

#include "../common.h"

#include "uiButton.hpp"
#include "uiButtonToggle.hpp"
#include "uiCombo.hpp"
#include "uiGroup.hpp"
#include "uiCheckbox.hpp"
#include "uiIcon.hpp"
#include "uiIconToggle.hpp"
#include "uiLabel.hpp"
#include "uiList.hpp"
#include "uiProgressbar.hpp"
#include "uiRadio.hpp"
#include "uiScrollbar.hpp"
#include "uiSlider.hpp"
#include "uiStaticImage.hpp"
#include "uiStepper.hpp"
#include "uiTextArea.hpp"
#include "uiTextInput.hpp"
#include "uiMenu.hpp"
#include "uiMenuFolder.hpp"
#include "uiMenuItem.hpp"
#include "uiRenderWindow.hpp"

namespace ffw{
	struct FFW_API uiWindowArgs {
		ffw::vec2i pos = ffw::vec2i(-1, -1);
		ffw::vec2i size = ffw::vec2i(400, 400);
		std::wstring title = L"Title";
		bool resizable = true;
		bool border = true;
		bool maximize = true;
		bool minimize = true;
		bool closeable = true;
		bool customBcgColor = false;
		ffw::color bcgColor;
	};

	class uiWindow;

	bool FFW_API showModal(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	bool FFW_API showModalError(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	bool FFW_API showModalWarning(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	bool FFW_API showModalInfo(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	
	class FFW_API uiWindow{
	public:
		uiWindow();
		uiWindow(uiWindow&& Other);
		virtual ~uiWindow();

		bool create(const uiWindowArgs& Info);
		bool update();
		void destroy();
		void shouldClose(bool Close);
		void hide();
		void show();
		void minimize();
		void maximize();
		void restore();

		bool isInitialized() const;

		void setWindowSize(int Width, int Height);
		void setSize(int Width, int Height);
		void setPos(int PosX, int PosY);
		ffw::vec2i getWindowSize() const;
		ffw::vec2i getSize() const;
		ffw::vec2i getPos() const;

		friend bool FFW_API showModal(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalError(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalWarning(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalInfo(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);

	protected:
		virtual void setup() = 0;
		virtual void textInputEvent(unsigned int C);
        virtual void keyPressedEvent(ffw::key Key, ffw::mode Mode);
        virtual void mouseMovedEvent(int MouseX, int MouseY);
        virtual void mouseScrollEvent(int Scroll);
        virtual void mouseButtonEvent(ffw::mouseButton Button, ffw::mode Mode);
		virtual void windowCloseEvent();
		virtual void widgetEvent(const ffw::uiWidget* Widget);
		virtual void windowPosEvent(short PosX, short PosY);
		virtual void windowSizeEvent(short Width, short Height);

		void setDefaultFont(const ffw::uiFont* Font);
		uiButton* addButton(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		uiButtonToggle* addButtonToggle(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		uiCombo* addCombo(int PosX, int PosY, int Width, int Height);
		uiGroup* addGroup(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		uiCheckbox* addCheckbox(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		uiIcon* addIcon(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		uiIconToggle* addIconToggle(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		uiLabel* addLabel(int PosX, int PosY, int Width, int Height, const std::wstring& Label, const ffw::color& Color = ffw::color(0.0f));
		uiList* addList(int PosX, int PosY, int Width, int Height, int Scroll);
		uiProgressbar* addProgressbar(int PosX, int PosY, int Width, int Height);
		uiRadio* addRadio(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		uiScrollbar* addScrollbar(int PosX, int PosY, int Width, int Height, int Style);
		uiSlider* addSlider(int PosX, int PosY, int Width, int Height);
		uiStaticImage* addStaticImage(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		uiStepper* addStepper(int PosX, int PosY, int Width, int Height);
		uiTextArea* addTextArea(int PosX, int PosY, int Width, int Height, const std::wstring& Label, bool HScroll, bool VScroll, bool ReadOnly);
		uiTextInput* addTextInput(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		bool addRenderWindow(uiRenderWindow* Widget, int PosX, int PosY, int Width, int Height, uiRenderWindow* Other = NULL);
		bool deleteWidget(uiWidget* Widget);

		uiMenu* addMenu();
		uiMenuItem* addMenuItem(const uiMenu* Menu, const std::wstring& Label);
		uiMenuFolder* addMenuFolder(const uiMenu* Menu, const std::wstring& Label);
		uiMenuItem* addMenuItem(const uiMenuFolder* Menu, const std::wstring& Label);
		uiMenuFolder* addMenuFolder(const uiMenuFolder* Menu, const std::wstring& Label);
		void showMenu(const uiMenu* Menu);

		uiWindow& operator = (uiWindow&& Other);
		// Copy constructor is not allowed
		uiWindow(const uiWindow& Other) = delete;
		// Copy assigment is not allowed
		uiWindow& operator = (const uiWindow& Other) = delete;
	private:
		class impl;
		impl* pimpl;
	};
};
#endif