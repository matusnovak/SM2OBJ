/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_WIDGET
#define FFW_UI_WIDGET

#include "../dll.h"
#include "constructor.h"
#include "sharedData.h"
#include "../math/stringMath.h"
#include "../systemUtils/win32SysUtils.h"

namespace ffw {
    class uiWidget;
};

#include "event.h"

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
	class FFW_API uiWidget {
    public:
        uiWidget(const std::string& ID);
        virtual ~uiWidget() {};
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void update() = 0;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        void setSize(float Width, float Height);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        void setPos(float PosX, float PosY);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        const ffw::vec2f& getSize() const;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        const ffw::vec2f& getPos() const;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        const std::string& getID() const;
        uint32_t getBufferSize() const;
        const float* getBuffer() const;
        uiEvent::type getEvent();
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        bool isStatic() const;
        bool shouldUpdateBuffer();
        bool shouldUpdate();
        void setDataPtr(uiSharedData* SharedData);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void hover(bool Hover);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void mousePressed(int Button, int PosX, int PosY);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void mouseReleased(int Button);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void focus(bool Focus);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void keyPressed(int Key, int Mode);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void textInput(int C);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        virtual void mousePos(int PosX, int PosY);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        bool hasHover();
        /*!
            @memberof uiWidget
            @ingroup User-Interface
        */
        bool hasFocus();

    protected:
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        void pushEvent(uiEvent::type EventType);
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        uiSharedData* sharedData;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        bool updateBufferFlag;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        bool updateFlag;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        bool isStaticFlag;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        uint32_t bufferSize;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        float* bufferVertices;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        bool hoverFlag;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        bool focusFlag;
        uiEvent::type currentEvent;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        std::string id;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        ffw::vec2f size;
        /*!
            @memberof uiWidget
            @ingroup User-Interface
            @protected
        */
        ffw::vec2f pos;

    };
};

#endif


