/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TRUE_TYPE
#define FFW_TRUE_TYPE

#include <GL/glfw3.h>
#include "../dll.h"
#include "graphicsTexture2D.h"
#include "bufferObject.h"
#include "graphicsShader.h"
#include "graphicsText.h"
#include "../utilities/logger.h"

#define UNICODE_MAX 65536

/*!
    @ingroup Graphics
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Graphics
    */
    class FFW_API trueType {
    public:
        trueType();
        virtual ~trueType();
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool init();
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool isLoaded() const;
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool deleteFont();
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool loadFromData(const unsigned char* Buffer, size_t Length, int Points, int Dpi);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool loadFromFile(std::string Path, int Points, int Dpi);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void getCharVertices(unsigned short C, vec4f& v0, vec4f& v1, vec4f& v2, vec4f& v3);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool createTextBuffer(text* Text, const std::string& Message);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        bool createTextBuffer(text* Text, const std::wstring& Message);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void drawChar(int PosX, int PosY, shader *FontShader, float* ViewMatrix, unsigned short Unicode, const color& Color, float Scale);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void drawString(int PosX, int PosY, shader *FontShader, float* ViewMatrix, const std::string& Message, const color& Color, float Scale);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void drawString(int PosX, int PosY, shader* FontShader, float* ViewMatrix, const std::wstring& Message, const color& Color, float Scale);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void drawText(int PosX, int PosY, shader* FontShader, float* ViewMatrix, text* Message, const color& Color, float Scale);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        int getCharAdvance(unsigned short C) const;
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        void setLineHeight(int Height);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        int getLineHeight() const;
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        texture2D *getFontTexture();
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        int getFontSize() const;
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        int getFontDPI() const;
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        vec2i getStringSize(const std::string& Str);
        /*!
            @memberof trueType
            @ingroup Graphics

        */
        vec2i getStringSize(const std::wstring& Str);

    private:
        bool initLibrary();
        bool loadFontFace(void* FontFacePtr, int Error, int Points, int Dpi);
        bool renderGlyph(void* FontFacePtr, int GlyphIndex, int Unicode);
        bool constructVbo();
        bool initDrawing();
        template<class T> void drawTemplate(int PosX, int PosY, shader *FontShader, float* ViewMatrix, const T& Message, const color& Color, float Scale);
        template<class T> bool createTextTemplate(text* Text, const T& Message);
        template<class T> vec2i getStringSizeTemplate(const T& Str);
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

        bool loaded = false;
        unsigned short unicodePtr[UNICODE_MAX];

        int shaderViewLoc;
        int shaderTexSampleLoc;
        int shaderColorLoc;
        int shaderPositionLoc;
        int shaderTexCoordsLoc;
        int shaderOffsetLoc;
        int shaderScaleLoc;
        bool shaderUniform;
    };
};
#endif

