/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_FONT
#define FFW_GRAPHICS_FONT

#include "../config.h"
#include "texture2D.hpp"
#include "bufferObject.hpp"
#include "shader.hpp"
#include "text.hpp"

/*!
    @ingroup Graphics
*/
namespace ffw {
    class renderContext;
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    class FFW_API font {
    public:
        font();
        virtual ~font();
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool init(const renderContext* Context);
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool isCreated() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool destroy();
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool loadFromData(const unsigned char* Buffer, size_t Length, int Points, int Dpi);
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool loadFromFile(const std::string& Path, int Points, int Dpi);
        /*!
            @memberof font
            @ingroup Graphics

        */
        void getCharVertices(unsigned short C, vec4f& v0, vec4f& v1, vec4f& v2, vec4f& v3);
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool createTextBuffer(text* Text, const std::string& Message);
        /*!
            @memberof font
            @ingroup Graphics

        */
        bool createTextBuffer(text* Text, const std::wstring& Message);
        /*!
            @memberof font
            @ingroup Graphics

        */
        int getCharAdvance(unsigned short C) const;
		/*!
            @memberof font
            @ingroup Graphics

        */
		int getCharVboId(unsigned short C) const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        void setLineHeight(int Height);
        /*!
            @memberof font
            @ingroup Graphics

        */
        int getLineHeight() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        const texture2D* getFontTexture() const;
		/*!
            @memberof font
            @ingroup Graphics

        */
		const bufferObject* getFontVbo() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        int getFontSize() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        int getFontDPI() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
		size_t getNumOfGlyphs() const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        vec2i getStringSize(const std::string& Str) const;
        /*!
            @memberof font
            @ingroup Graphics

        */
        vec2i getStringSize(const std::wstring& Str) const;

    private:
		bool loadFontFace(void* FontFacePtr, int Error, int Points, int Dpi);
		bool renderGlyph(void* FontFacePtr, int glyphIndex, int Unicode);
		bool constructVbo();
		
		std::wstring tempChar;

        struct charStruct{
            unsigned char* pixels;
            short texWidth;
            short texHeight;
            short width;
            short height;
            short x;
            short y;
            short left;
            short bearing;
            short advance;
            unsigned short unicode;
        };

        std::vector<charStruct> allCharacters;
        ffw::texture2D fontTexture;
        ffw::bufferObject fontVBO;
        int fontSizePixels;
        int fontSizePoints;
        int fontDpi;
        int fontLineHeight;

        bool loaded;
		static const int unicodeMax = 65536;
        unsigned short unicodePtr[unicodeMax];
    };
};
#endif

