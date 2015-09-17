/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_TEXT
#define FFW_GRAPHICS_TEXT

#include "../common.h"
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
        static bool checkCompability(const renderContext* Renderer);
		
		text();
        ~text();
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool create(const renderContext* Renderer, float* Vertices, size_t Size);
        /*!
            @memberof text
            @ingroup Graphics

        */
        void destroy();
        /*!
            @memberof text
            @ingroup Graphics

        */
        size_t getSize() const;
        /*!
            @memberof text
            @ingroup Graphics

        */
        bool isLoaded() const;
        /*!
            @memberof text
            @ingroup Graphics
        */
        void bind() const;
        /*!
            @memberof text
            @ingroup Graphics
        */
        void unbind() const;

    private:
        bool loaded;
        ffw::vbo vbo;
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
