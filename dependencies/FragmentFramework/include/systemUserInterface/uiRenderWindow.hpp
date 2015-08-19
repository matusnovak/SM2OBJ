/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SYS_UI_RENDER_WINDOW
#define FFW_SYS_UI_RENDER_WINDOW

#include "uiWidget.hpp"
#include "../render/renderContext.hpp"

namespace ffw{
	class FFW_API uiRenderWindow: public uiWidget, public renderContext{
	public:
		uiRenderWindow();
		virtual ~uiRenderWindow();

		void setPos(int PosX, int PosY) override;
		void setSize(int Width, int Height) override;
		bool create(void* Handle, void* HandleInst, uiRenderWindow* Other, int ID, int PosX, int PosY, int Width, int Height);
		void destroy();
		void update();
		bool isInitialized() const;
		bool isClosed() const;
		void shouldClose();
		bool runSetup();

		void setViewport(int PosX, int PosY, int Width, int Height) override;
        const ffw::mat4& getViewMatrix() const override;
        void getViewport(int *PosX, int *PosY, int *Width, int *Height) const override;
        void* getGlextFunc(const std::string& FunctionName) const override;
        bool isGlextFuncPresent(const std::string& FunctionName) const override;
        void setSwapInterval(int Interval) override;
        const glExtensions& getGlExtensions() const override;
        const basicShaders& getBasicShaders() const override;
	
		static const size_t hash;

		class wndProcClass;
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
	private:
		bool setupContext();
		void destroyWindowData();
		class impl;
		impl* pimpl;

		/*bool setupContext();
		void destroyWindowData();
		ffw::renderContextData ownContext;
		ffw::renderContextData* parentContext;
		void* wglContext;
		void* hDC;
		void* parentHInstance;
		void* swapIntervalFunc;
		bool setupDone;
		bool initialized;
		std::wstring className;
		ffw::uiRenderWindow* otherWindow;
		bool closed;*/
	};
};
#endif