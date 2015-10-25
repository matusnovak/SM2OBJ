/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GRAPHICS_FONT
#define FFW_GRAPHICS_FONT

#include "../common.h"
#include "texture2D.hpp"
#include "bufferObject.hpp"
#include "text.hpp"

/*!
 * @ingroup Graphics
 */
namespace ffw {
    class renderContext;
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 */
    class FFW_API font {
    public:
		/*!
		 * @memberof font
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		font();
        virtual ~font();
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Checks if the font is created
		 */
        bool isCreated() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @brief Destroys the font
		 */
        bool destroy();
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @brief Creates the font from array of bytes
		 */
        bool createFromData(const renderContext* Renderer, const unsigned char* Buffer, size_t Length, int Points, int Dpi);
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @brief Creates the font from a file
		 */
        bool createFromFile(const renderContext* Renderer, const std::string& Path, int Points, int Dpi);
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Creates a polygon (quad) from given unicode character
		 */
        void getCharVertices(unsigned short C, vec4f& v0, vec4f& v1, vec4f& v2, vec4f& v3) const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Creates a text buffer from given string
		 */
        bool createTextBuffer(text* Text, const std::string& Message) const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Creates a text buffer from given string
		 */
        bool createTextBuffer(text* Text, const std::wstring& Message) const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns character advance
		 */
        int getCharAdvance(unsigned short C) const;
		/*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns character index in VBO
		 */
		int getCharVboId(unsigned short C) const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @brief Sets line height in pixels
		 */
        void setLineHeight(int Height);
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns line height in pixels
		 */
        int getLineHeight() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns a pointer to the font texture
		 */
        const texture2D* getFontTexture() const;
		/*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns a pointer to the font VBO
		 */
		const bufferObject* getFontVbo() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the font size
		 */
        int getFontSize() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the font DPI
		 */
        int getFontDPI() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns number of characters inside the font
		 */
		size_t getNumOfGlyphs() const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Returns size of the string in pixels
		 */
        vec2i getStringSize(const std::string& Str) const;
        /*!
		 * @memberof font
		 * @ingroup Graphics
		 * @const
		 * @brief Return size of the string in pixels
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

		const ffw::renderContext* rendererPtr;
        std::vector<charStruct> allCharacters;
        ffw::texture2D fontTexture;
        ffw::vbo fontVBO;
        int fontSizePixels;
        int fontSizePoints;
        int fontDpi;
        int fontLineHeight;

        bool loaded;
		static const size_t unicodeMax = 65536;
        unsigned short unicodePtr[unicodeMax];
    };

	extern FFW_API const unsigned char* defaultFont;
	extern FFW_API const size_t defaultFontSize;
};
#endif

