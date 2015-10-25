/*** This file is part of FragmentFramework project ***/

#ifndef FFW_SYS_UI_RENDER_WINDOW
#define FFW_SYS_UI_RENDER_WINDOW

#include "uiWidget.hpp"
#include "../render/renderContext.hpp"

/*!
 * @ingroup User-Interface
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup User-Interface
	 * @inherit uiWidget, renderContext
	 */
	class FFW_API uiRenderWindow: public uiWidget, public renderContext{
	public:
		uiRenderWindow();
		virtual ~uiRenderWindow();
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 */
		void setPos(int PosX, int PosY) override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 */
		void setSize(int Width, int Height) override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		bool create(void* Handle, void* HandleInst, uiRenderWindow* Other, int ID, int PosX, int PosY, int Width, int Height);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		void destroy();
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		bool update();
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		bool isInitialized() const;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		void shouldClose(bool Close);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 */
		bool runSetup();
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 */
		void setViewport(int PosX, int PosY, int Width, int Height) override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        const ffw::mat4x4f& getViewMatrix() const override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        void getViewport(int *PosX, int *PosY, int *Width, int *Height) const override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        void* getGlextFunc(const std::string& FunctionName) const override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        bool isGlextFuncPresent(const std::string& FunctionName) const override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 */
        void setSwapInterval(int Interval) override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        const glExtensions& getGlExtensions() const override;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @override
		 * @const
		 */
        const drawShaders& getdrawShaders() const override;

		static const size_t hash;

		class wndProcClass;
	protected:
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual bool setup() = 0;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual void render() = 0;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @pure
		 * @protected
		 */
		virtual void close() = 0;
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
		virtual void textInputEvent(unsigned int C);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void keyPressedEvent(ffw::key Key, ffw::mode Mode);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseMovedEvent(int MouseX, int MouseY);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseScrollEvent(int Scroll);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void mouseButtonEvent(ffw::mouseButton Button, ffw::mode Mode);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
		virtual void windowResizedEvent(int Width, int Height);
		/*!
		 * @memberof uiRenderWindow
		 * @ingroup User-Interface
		 * @virtual
		 * @protected
		 */
        virtual void windowMovedEvent(int WindowX, int WindowY);
	private:
		bool setupContext();
		void destroyWindowData();
		class impl;
		impl* pimpl;
	};
};
#endif
