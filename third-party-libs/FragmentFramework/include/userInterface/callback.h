/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UI_CALLBACK
#define FFW_UI_CALLBACK

#include "event.h"

namespace ffw {
    class callbackInterface {
    public:
        virtual ~callbackInterface(){}
        virtual void execute(const uiEvent& Event) = 0;
    };

    template <class T> class callback: public callbackInterface {
    public:
        callback(void (T::*Func)(const uiEvent&), T* Instance):funcMem(Func), instance(Instance), isMem(true){}
        callback(void (*Func)(const uiEvent&)):func(Func), instance(NULL), isMem(false){}

        void execute(const uiEvent& Event) override {
            if(isMem)
                (instance->*funcMem)(Event);
            else
                func(Event);
        }
    private:
        void (T::*funcMem)(const uiEvent&);
        void (*func)(const uiEvent&);
        T* instance;
        bool isMem;
    };
}

#endif

