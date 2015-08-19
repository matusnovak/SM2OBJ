/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_TEXT
#define FFW_GRAPHICS_TEXT

#include "../config.h"
#include "bufferObject.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
	class renderContext;
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
        bool init(const renderContext* Context);
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool createText(float* Vertices, size_t Size);
        /*!
            @memberof text
            @ingroup Graphics

        */
        void destroy();
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
