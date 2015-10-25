/*** This file is part of FragmentFramework project ***/

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

/*!
 * @defgroup User-Interface
 */



/*!
 * @ingroup User-Interface
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	struct FFW_API uiWindowArgs {
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		ffw::vec2i pos = ffw::vec2i(-1, -1);
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		ffw::vec2i size = ffw::vec2i(400, 400);
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		std::wstring title = L"Title";
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool resizable = true;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool border = true;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool maximize = true;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool minimize = true;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool closeable = true;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		bool customBcgColor = false;
		/*!
		 * @memberof uiWindowArgs
		 * @ingroup User-Interface
		 */
		ffw::color bcgColor;
	};

	class uiWindow;

	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	bool FFW_API showModal(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	bool FFW_API showModalError(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	bool FFW_API showModalWarning(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	bool FFW_API showModalInfo(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel = false);

	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 */
	class FFW_API uiWindow{
	public:
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		uiWindow();
		uiWindow(const uiWindow& Other) = delete;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		uiWindow(uiWindow&& Other);
		virtual ~uiWindow();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		bool create(const uiWindowArgs& Info);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		bool update();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void destroy();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void shouldClose(bool Close);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void hide();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void show();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void minimize();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void maximize();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void restore();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		bool isInitialized() const;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void setWindowSize(int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void setSize(int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		void setPos(int PosX, int PosY);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		ffw::vec2i getWindowSize() const;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		ffw::vec2i getSize() const;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		ffw::vec2i getPos() const;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		void invalidate();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @const
		 */
		void redraw();
		
		// Copy assigment is not allowed
		uiWindow& operator = (const uiWindow& Other) = delete;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 */
		uiWindow& operator = (uiWindow&& Other);

		friend bool FFW_API showModal(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalError(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalWarning(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);
		friend bool FFW_API showModalInfo(const uiWindow* Window, const std::wstring& Title, const std::wstring& Message, bool Cancel);

	protected:
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual void setup() = 0;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual void widgetEvent(const ffw::uiWidget* Widget) = 0;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual void windowCloseEvent() = 0;
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
		virtual void textInputEvent(unsigned int C);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void keyPressedEvent(ffw::key Key, ffw::mode Mode);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseMovedEvent(int MouseX, int MouseY);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseScrollEvent(int Scroll);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseButtonEvent(ffw::mouseButton Button, ffw::mode Mode);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
		virtual void windowMovedEvent(int PosX, int PosY);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
		virtual void windowResizeEvent(int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		void setDefaultFont(const ffw::uiFont* Font);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiButton* addButton(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiButtonToggle* addButtonToggle(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiCombo* addCombo(int PosX, int PosY, int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiGroup* addGroup(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiCheckbox* addCheckbox(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiIcon* addIcon(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiIconToggle* addIconToggle(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiLabel* addLabel(int PosX, int PosY, int Width, int Height, const std::wstring& Label, const ffw::color& Color = ffw::color(0.0f));
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiList* addList(int PosX, int PosY, int Width, int Height, int Scroll);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiProgressbar* addProgressbar(int PosX, int PosY, int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiRadio* addRadio(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiScrollbar* addScrollbar(int PosX, int PosY, int Width, int Height, int Style);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiSlider* addSlider(int PosX, int PosY, int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiStaticImage* addStaticImage(int PosX, int PosY, int Width, int Height, const ffw::uiBitmap* Bitmap);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiStepper* addStepper(int PosX, int PosY, int Width, int Height);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiTextArea* addTextArea(int PosX, int PosY, int Width, int Height, const std::wstring& Label, bool HScroll, bool VScroll, bool ReadOnly);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiTextInput* addTextInput(int PosX, int PosY, int Width, int Height, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		bool addRenderWindow(uiRenderWindow* Widget, int PosX, int PosY, int Width, int Height, uiRenderWindow* Other = NULL);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		bool deleteWidget(uiWidget* Widget);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiMenu* addMenu();
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiMenuItem* addMenuItem(const uiMenu* Menu, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiMenuFolder* addMenuFolder(const uiMenu* Menu, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiMenuItem* addMenuItem(const uiMenuFolder* Menu, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		uiMenuFolder* addMenuFolder(const uiMenuFolder* Menu, const std::wstring& Label);
		/*!
		 * @memberof uiWindow
		 * @ingroup User-Interface
		 * @protected
		 */
		void showMenu(const uiMenu* Menu);
	private:
		class impl;
		impl* pimpl;
	};
};
#endif
