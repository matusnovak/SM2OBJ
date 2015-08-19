/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_APP_RENDER_WINDOW
#define FFW_APP_RENDER_WINDOW

#include "../config.h"
#include "renderContext.hpp"
#include "../math/math.h"

/*!
    @ingroup Core
*/
namespace ffw {
	struct FFW_API appRenderWindowArgs{
		ffw::vec2i pos = ffw::vec2i(-1, -1);
		ffw::vec2i size = ffw::vec2i(400, 400);
		std::string title;
		bool resizable = true;
		bool border = true;
		bool maximize = true;
		bool floating = false;
		bool focused = true;
		bool visible = true;
		int samples = 0;
		ffw::monitor* monitor = NULL;
	};	
	/*!
        @memberof ffw
        @ingroup Core
    */
	class FFW_API appRenderWindow: public renderContext {
    public:
        appRenderWindow();
        virtual ~appRenderWindow();

		void setPos(int PosX, int PosY);
		void setSize(int Width, int Height);
		ffw::vec2i getPos() const;
		ffw::vec2i getSize() const;
		bool create(const appRenderWindowArgs& Args, appRenderWindow* Other);
		void destroy();
		void update();
		bool isInitialized() const;
		bool runSetup();
		bool isClosed() const;
		void shouldClose();

		void setViewport(int PosX, int PosY, int Width, int Height) override;
        const ffw::mat4& getViewMatrix() const override;
        void getViewport(int *PosX, int *PosY, int *Width, int *Height) const override;
        void* getGlextFunc(const std::string& FunctionName) const override;
        bool isGlextFuncPresent(const std::string& FunctionName) const override;
        void setSwapInterval(int Interval) override;
        const glExtensions& getGlExtensions() const override;
        const basicShaders& getBasicShaders() const override;

		// Disable copy operator and copy constructor
        appRenderWindow& operator = (const appRenderWindow&) = delete;
        appRenderWindow(const appRenderWindow&) = delete;

		struct windowCallback;
		friend struct windowCallback;

	protected:
		virtual bool setup() = 0;
		virtual void render() = 0;
		virtual void close() = 0;
		virtual void textInputEvent(unsigned int C);
        virtual void keyPressedEvent(int Key, int Mode);
        virtual void mouseMovedEvent(int MouseX, int MouseY);
        virtual void mouseScrollEvent(int scroll);
        virtual void mouseButtonEvent(int button, int mode);
        virtual void windowResizedEvent(int width, int height);
        virtual void windowMovedEvent(int windowX, int windowY);
        virtual void windowCloseEvent();
        virtual void windowFocusEvent(int focus);
        virtual void filesDroppedEvent(std::vector<std::string> FileList);
    private:
		bool setupContext();
		void destroyWindowData();
		class impl;
		impl* pimpl;
    };
};
#endif
