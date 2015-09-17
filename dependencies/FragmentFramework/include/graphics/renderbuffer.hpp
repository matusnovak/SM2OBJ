/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDERBUFFER
#define FFW_RENDERBUFFER

#include "../common.h"

/*!
    @ingroup Graphics
*/
namespace ffw {
	class renderContext;
	/*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API renderbuffer {
    public:
        renderbuffer();
        virtual ~renderbuffer();
        /*!
            @memberof renderbuffer
            @ingroup Graphics
            @const
        */
        bool isCreated() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
        */
        void destroy();
        /*!
            @memberof renderbuffer
            @ingroup Graphics
        */
        void bind() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
        */
        void unbind() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
            @const
        */
        unsigned int getHandle() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
            @const
        */
        int getWidth() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
            @const
        */
        int getHeight() const;
        /*!
            @memberof renderbuffer
            @ingroup Graphics
            @const
        */
        unsigned int getInternalFormat() const;

    protected:
        bool loaded;
        unsigned int internalFormat;
        unsigned int buffer;

        int width;
        int height;

        const glExtensions* gl;
    };
};
#endif
