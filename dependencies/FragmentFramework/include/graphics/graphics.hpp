/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GRAPHICS
#define FFW_GRAPHICS

#include "../common.h"
#include "../render/renderContext.hpp"
#include "texture2D.hpp"
#include "font.hpp"

/*!
 * @defgroup Graphics
 */



/*!
 * @ingroup Graphics
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Sets the color for next draw commands
	 * @param Context Pointer to the active render context
	 * @param Color Color to set
	 */
	void FFW_API setDrawColor(const ffw::renderContext* Context, const ffw::color& Color);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a simple filled rectangle
	 * @param Context Pointer to the active render context
	 * @param PosX Upper left corner of the rectangle
	 * @param PosY Upper left corner of the rectangle
	 * @param Width Width of the rectangle
	 * @param Height Height of the rectangle
	 */
    void FFW_API drawRectangle(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a triangle
	 * @param Context Pointer to the active render context
	 * @param P0x First vertex position
	 * @param P0y First vertex position
	 * @param P1x Second vertex position
	 * @param P1x Second vertex position
	 * @param P2x Third vertex position
	 * @param P2y Third vertex position
	 */
    void FFW_API drawTriangle(const ffw::renderContext* Context, int P0x, int P0y, int P1x, int P1y, int P2x, int P2y);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a 2D texture
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner
	 * @param PosY Left upper corner
	 * @param Width Width of rendered rectangle area
	 * @param Height Height of rendered rectangle area
	 * @param Texture Pointer to the 2D texture
	 */
    void FFW_API drawTexture2D(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a 2D texture
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner
	 * @param PosY Left upper corner
	 * @param Width Width of rendered rectangle area
	 * @param Height Height of rendered rectangle area
	 * @param Texture Pointer to the 2D texture
	 * @param MirrorX Pass true in order to mirror texture horizontally
	 * @param MirrorY Pass true in order to mirror texture vertically
	 */
    void FFW_API drawTexture2DMirror(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, bool MirrorX, bool MirrorY);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a 2D texture
	 * @details The specified subsection must be in texture coordinates
	 * (values between 0.0 and 1.0) For example
	 * `drawTexture2DSub(..., 0.5, 0.5, 0.5, 0.5)`
	 * will draw lower right section (1/4) starting from center of the texture.
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner
	 * @param PosY Left upper corner
	 * @param Width Width of rendered rectangle area
	 * @param Height Height of rendered rectangle area
	 * @param Texture Pointer to the 2D texture
	 * @param SubX Left upper corner of subsection rectangle
	 * @param SubY Left upper corner of subsection rectangle
	 * @param SubW Width of the subsection
	 * @param SubH Height of the subsection
	 */
    void FFW_API drawTexture2DSub(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, float SubX, float SubY, float SubW, float SubH);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a 2D texture
	 * @details The specified subsection must be in texture coordinates
	 * (values between 0.0 and 1.0) For example
	 * `drawTexture2DSub(..., 0.5, 0.5, 0.5, 0.5)`
	 * will draw lower right section (1/4) starting from center of the texture.
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner
	 * @param PosY Left upper corner
	 * @param Width Width of rendered rectangle area
	 * @param Height Height of rendered rectangle area
	 * @param Texture Pointer to the 2D texture
	 * @param SubX Left upper corner of subsection rectangle
	 * @param SubY Left upper corner of subsection rectangle
	 * @param SubW Width of the subsection
	 * @param SubH Height of the subsection
	 * @param MirrorX Pass true in order to mirror subsection horizontally
	 * @param MirrorY Pass true in order to mirror subsection vertically
	 */
    void FFW_API drawTexture2DSubMirror(const ffw::renderContext* Context, int PosX, int PosY, int Width, int Height, const ffw::texture2D* Texture, float SubX, float SubY, float SubW, float SubH, bool MirrorX, bool MirrorY);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws an arc shape
	 * @details
	 * ```
	 *   ___________
	 *  /           \
	 * /             \
	 * |      X------|  
	 * \             /
	 *  \           /
	 *   \_________/
	 *
	 *   X   - PosX and PosY
	 * ----- - Starting point of an inner and outer angle
	 * ```
	 * @note All angles go in opposite direction! (clock-wise)
	 * @param Context Pointer to the active render context
	 * @param PosX Center of the arc
	 * @param PosY Center of the arc
	 * @param InnerRadius Inner radius of the arc
	 * @param OuterRadius Outer Radius of the arc
	 * @param StartAngle Start angle of the arc starting from right
	 * @param EndAngl End angle of the arc starting from right
	 * @param Steps How many steps it takes to render the arc (more = fancy)
	 */
    void FFW_API drawArc(const ffw::renderContext* Context, int PosX, int PosY, int InnerRadius, int OuterRadius, int StartAngle, int EndAngle, int Steps);
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a circle
	 * @param Context Pointer to the active render context
	 * @param PosX Center of the circle
	 * @param PosY Center of the circle
	 * @param Radius Radius of the circle
	 * @param Steps How many steps it takes to render the triangle (more = fancy)
	 */
    void FFW_API drawCircle(const ffw::renderContext* Context, int PosX, int PosY, int Radius, int Steps);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a simple line
	 * @param Context Pointer to the active render context
	 * @param StartX Start position
	 * @param StartY Start position
	 * @param EndX End position
	 * @param EndY End position
	 */
    void FFW_API drawLine(const ffw::renderContext* Context, int StartX, int StartY, int EndX, int EndY);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a thick line
	 * @param Context Pointer to the active render context
	 * @param StartX Start position
	 * @param StartY Start position
	 * @param EndX End position
	 * @param EndY End position
	 * @param Thickness Thicnkess of the line in pixels
	 */
    void FFW_API drawLineThick(const ffw::renderContext* Context, int StartX, int StartY, int EndX, int EndY, int Thickness);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a string
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner of the first line
	 * @param PosY Left upper corner of the first line
	 * @param Font Pointer to the font instance
	 * @param Str String to draw (Not UTF-8 compatible!)
	 */
	void FFW_API drawString(const ffw::renderContext* Context, int PosX, int PosY, const font* Font, const std::string& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a string
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner of the first line
	 * @param PosY Left upper corner of the first line
	 * @param Font Pointer to the font instance
	 * @param Str Multi-byte string to draw
	 */
	void FFW_API drawString(const ffw::renderContext* Context, int PosX, int PosY, const font* Font, const std::wstring& Str);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a text buffer
	 * @details The same font must be used to create and to draw the
	 * text buffer!
	 * @param Context Pointer to the active render context
	 * @param PosX Left upper corner of the first line
	 * @param PosY Left upper corner of the first line
	 * @param Font Pointer to the font instance
	 * @param Text Pointer to the text buffer
	 */
	void FFW_API drawText(const ffw::renderContext* Context, int PosX, int PosY, const font* Font, const ffw::text* Text);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a bezier curve
	 * @param Context Pointer to the active render context
	 * @param StartX Starting point
	 * @param StartY Starting point
	 * @param CP0X Control point of the start point
	 * @param CP0Y Control point of the start point
	 * @param CP1X Control point of the end point
	 * @param CP1Y Control point of the end point
	 * @param EndX Ending point
	 * @param EndY Ending point
	 * @param Steps How many steps it takes to render the curve (more = fancy)
	 */
	void FFW_API drawBezier(const ffw::renderContext* Context, int StartX, int StartY, int CP0X, int CP0Y, int CP1X, int CP1Y, int EndX, int EndY, int Steps);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Draws a bezier curve
	 * @param Context Pointer to the active render context
	 * @param StartX Starting point
	 * @param StartY Starting point
	 * @param CP0X Control point of the start point
	 * @param CP0Y Control point of the start point
	 * @param CP1X Control point of the end point
	 * @param CP1Y Control point of the end point
	 * @param EndX Ending point
	 * @param EndY Ending point
	 * @param Thickness Thickness of the bezier curve 
	 * @param Steps How many steps it takes to render the curve (more = fancy)
	 */
	void FFW_API drawBezierThick(const ffw::renderContext* Context, int StartX, int StartY, int CP0X, int CP0Y, int CP1X, int CP1Y, int EndX, int EndY, int Thickness, int Steps);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Enables blending function
	 */
	void FFW_API enableBlendFunc(const ffw::renderContext* Context, unsigned int source, unsigned int destination);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Enables separate blending function for albedo and color
	 */
	void FFW_API enableBlendFuncSeparate(const ffw::renderContext* Context, unsigned int srcRgb, unsigned int destRgb, unsigned int srcAlpha, unsigned int destAlpha);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Disables blending function
	 */
	void FFW_API disableBlendFunc(const ffw::renderContext* Context);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Activates texture
	 * @param Context Pointer to the active render context
	 * @param Texture Index of the texture (0 - 31)
	 */
	void FFW_API activeTexture(const ffw::renderContext* Context, unsigned int Texture);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Sets a draw buffers
	 * @param Context Pointer to the active render context
	 * @param Num Length of buffer array
	 * @param Buffs Pointer to the buffer array
	 */
	void FFW_API setDrawBuffers(const ffw::renderContext* Context, int Num, const unsigned int* Buffs);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Finds a largets size and position of an image that can fit into the area
	 * @see coverImage
	 */
	ffw::vec4i FFW_API containImage(int ImgWidth, int ImgHeight, int MaxWidth, int MaxHeight);
	/*!
	 * @memberof ffw
	 * @ingroup Graphics
	 * @brief Finds a largets size and position of an image that will fill entire area with no space left
	 * @see containImage 
	 */
	ffw::vec4i FFW_API coverImage(int ImgWidth, int ImgHeight, int MaxWidth, int MaxHeight);
};
#endif
