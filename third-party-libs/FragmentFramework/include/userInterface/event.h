/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_EVENT
#define FFW_UI_EVENT

/*!
    @ingroup User-Interface
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup User-Interface
    */
    class uiEvent {
    public:
        virtual ~uiEvent(){}
        /*!
            @memberof uiEvent
            @ingroup User-Interface
        */
        enum type {
            none,
            pressed,
            selected,
            value
        };

        /*!
            @memberof uiEvent
            @ingroup User-Interface
        */
        uiEvent(type Type, uiWidget* Widget){
            eventType = Type;
            widget = Widget;
        }
        /*!
            @memberof uiEvent
            @ingroup User-Interface
        */
        type getType() const {
            return eventType;
        }
        /*!
            @memberof uiEvent
            @ingroup User-Interface
        */
        uiWidget* getWidget() const {
            return widget;
        }
    private:
        type eventType;
        uiWidget* widget;
    };
}

#endif
