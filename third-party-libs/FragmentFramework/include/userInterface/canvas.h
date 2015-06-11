/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_CANVAS
#define FFW_UI_CANVAS

#include "../dll.h"
#include "widget.h"
#include "event.h"
#include "callback.h"

#include "../math/stringMath.h"
#include "../math/math.h"
#include "../graphics/bufferObject.h"

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
	class FFW_API uiCanvas {
    public:
        uiCanvas();
        bool init();
        void destroy();
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void deleteAllWidgets();
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        uiWidget* addWidget(uiWidget* Widget);
        void bind();
        void unbind();
        void updateBuffers();
        void updateUserInput();
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void injectMousePos(int MouseX, int MouseY);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void injectMouseButtonPressed(int Button);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void injectMouseButtonReleased(int Button);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void injectKeyPressed(int Key, int Mode);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void injectTextInput(int C);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void resetUserInput();
        uint32_t getBufferSize() const;
        bool isBufferLoaded() const;
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void setPos(int PosX, int PosY);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void setSize(int Width, int Height);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void setOffset(int OffsetX, int OffsetY);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        void setVisible(bool Visibility);
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        const ffw::vec2i& getPos() const;
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        const ffw::vec2i& getSize() const;
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        const ffw::vec2i& getOffset() const;
        /*!
            @memberof uiCanvas
            @ingroup User-Interface
        */
        bool isVisible() const;
        void setDataPtr(uiSharedData* SharedData);
        void poolEvents(std::vector<callbackInterface*>& Listeners);

    private:
        void recreateVbo();

        ffw::bufferObject vbo;
        struct widgetWrapper {
            uiWidget* ptr;
            uint32_t bufferOffset;
        };
        std::vector<widgetWrapper> widgetsStaticVec;
        std::vector<widgetWrapper> widgetsDynamicVec;
        int mouseX;
        int mouseY;

        ffw::vec2i size;
        ffw::vec2i pos;
        ffw::vec2i offset;
        uiSharedData* sharedData;
        int eventsQueueSize;
        bool visible;
    };
};

#endif

