/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_TEXT
#define FFW_GRAPHICS_TEXT

#include "../dll.h"
#include <GL/glfw3.h>
#include "bufferObject.h"
#include <iostream>

/*!
    @ingroup Graphics
*/
namespace ffw {
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API text {
    public:
        text();
        ~text();
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool init();
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool createText(float* Vertices, size_t Size);
        /*!
            @memberof text
            @ingroup Graphics

        */
        void deleteText();
        /*!
            @memberof text
            @ingroup Graphics

        */
        size_t getTextLength() const;
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool isLoaded() const;
        /*!
            @memberof text
            @ingroup Graphics
        */
        void bind();
        /*!
            @memberof text
            @ingroup Graphics
        */
        void unbind();

    private:
        bool loaded;
        ffw::bufferObject vbo;
        unsigned int size;

        int shaderViewLoc;
        int shaderTexSampleLoc;
        int shaderColorLoc;
        int shaderPositionLoc;
        int shaderTexCoordsLoc;
        int shaderOffsetLoc;
        bool shaderUniform;
    };
};
#endif
