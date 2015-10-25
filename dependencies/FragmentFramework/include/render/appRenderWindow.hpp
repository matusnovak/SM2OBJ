/*** This file is part of FragmentFramework project ***/

#ifndef FFW_APP_RENDER_WINDOW
#define FFW_APP_RENDER_WINDOW

#include "../common.h"
#include "renderContext.hpp"

/*!
 * @defgroup Render
 */



/*!
 * @ingroup Render
 */
namespace ffw {
	/*!
     * @memberof ffw
     * @ingroup Render
     */
	struct FFW_API appRenderWindowArgs{
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window position (Set to -1, -1 in order to
		 * let OS select the default position)
		 */
		ffw::vec2i pos = ffw::vec2i(-1, -1);
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window size
		 */
		ffw::vec2i size = ffw::vec2i(400, 400);
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Title of the window (UTF-8 compatible)
		 */
		std::string title;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window can be resizable
		 */
		bool resizable = true;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window has border
		 */
		bool border = true;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window maximize button
		 */
		bool maximize = true;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window is floating
		 */
		bool floating = false;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window is focused on spawn
		 */
		bool focused = true;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window is visible on spawn
		 */
		bool visible = true;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Window framebuffer samples
		 */
		int samples = 0;
		/*!
		 * @memberof appRenderWindowArgs
		 * @ingroup Render
		 * @brief Target monitor
		 */
		ffw::monitor* monitor = NULL;
	};	
	/*!
     * @memberof ffw
     * @ingroup Render
	 * @inherits renderContext
     */
	class FFW_API appRenderWindow: public renderContext {
    public:
        appRenderWindow();
        virtual ~appRenderWindow();
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		void setPos(int PosX, int PosY);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		void setSize(int Width, int Height);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		ffw::vec2i getPos() const;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		ffw::vec2i getSize() const;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		bool create(const appRenderWindowArgs& Args, appRenderWindow* Other);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		void destroy();
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		bool update();
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		bool isInitialized() const;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		bool runSetup();
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		void setViewport(int PosX, int PosY, int Width, int Height) override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        const ffw::mat4x4f& getViewMatrix() const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @override
		 * @const
		 * @brief Gets current viewport size
		 *
		 * @details Gets the current viewport size and position. 
		 * Parameters can be NULL.
		 *
		 * @params
		 * **PosX** Where to store position X
		 *
		 * **PosY** Where to store position Y
		 *
		 * **Width** Where to store width
		 *
		 * **Height** Where to store height
		 */
        void getViewport(int *PosX, int *PosY, int *Width, int *Height) const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        void* getGlextFunc(const std::string& FunctionName) const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        bool isGlextFuncPresent(const std::string& FunctionName) const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        void setSwapInterval(int Interval) override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        const glExtensions& getGlExtensions() const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
        const drawShaders& getdrawShaders() const override;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 */
		void shouldClose(bool Close);

		// Disable copy operator and copy constructor
        appRenderWindow& operator = (const appRenderWindow&) = delete;
        appRenderWindow(const appRenderWindow&) = delete;
		
		appRenderWindow(appRenderWindow&& Other);
		appRenderWindow& operator = (appRenderWindow&& Other);

		struct windowCallback;
		friend struct windowCallback;

	protected:
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
		virtual bool setup() = 0;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
		virtual void render() = 0;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
		virtual void close() = 0;
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
		virtual void textInputEvent(unsigned int C);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void keyPressedEvent(ffw::key Key, ffw::mode Mode);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void mouseMovedEvent(int MouseX, int MouseY);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void mouseScrollEvent(int Scroll);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void mouseButtonEvent(ffw::mouseButton Button, ffw::mode Mode);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void windowResizedEvent(int Width, int Height);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void windowMovedEvent(int PosX, int PosY);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void windowCloseEvent();
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void windowFocusEvent(bool Focus);
		/*!
		 * @memberof appRenderWindow
		 * @ingroup Render
		 * @protected
		 */
        virtual void filesDroppedEvent(std::vector<std::string> FileList);
    private:
		bool setupContext();
		void destroyWindowData();
		class impl;
		impl* pimpl;
    };
};
#endif
