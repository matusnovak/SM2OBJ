/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_RENDERER
#define FFW_RENDERER

#include <windows.h>
#include <GL/glfw3.h>
#include <GL/wglext.h>

#include "../dll.h"
#include "../graphics/shaderArcData.h"
#include "../graphics/shaderFontData.h"
#include "../graphics/shaderLineData.h"
#include "../graphics/shaderRectData.h"
#include "../graphics/shaderTextureData.h"
#include "../math/math.h"
#include "../graphics/graphicsShader.h"
#include "../graphics/graphicsTexture2D.h"
#include "../graphics/graphicsTrueType.h"

/*!
    @ingroup Core
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Core
        @name GLExtProc
    */
    typedef void (*GLExtProc)(void);
    /*!
        @memberof ffw
        @ingroup Core
    */
	class FFW_API renderUtilities {
    public:
		renderUtilities();
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        bool initShaders();
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void destroyShaders();
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void setBlendFuncSeparate(GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void setViewport(int PosX, int PosY, int Width, int Height);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void getViewMatrix(float *view);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void pushViewport();
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void popViewport();
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void getViewport(int *PosX, int *PosY, int *Width, int *Height);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        const GLExtProc getOpenGLExtension(std::string FunctionName);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void activeTexture(int Index);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void setDrawBuffers(GLint Num, GLuint* DrawBuffers);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void setArcResolution(int Steps);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawArc(float PosX, float PosY, float InnerRadius, float OuterRadius, float StartAngle, float EndAngle, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangle(float PosX, float PosY, float Width, float Height, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangleOut(float PosX, float PosY, float Width, float Height, const ffw::color& Color, float Outline);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangleRounded(float PosX, float PosY, float Width, float Height, const ffw::color& Color, float Corner, bool TopLeft, bool TopRight, bool BottomLeft, bool BottomRight);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangleRoundedOut(float PosX, float PosY, float Width, float Height, const ffw::color& Color, float Corner, bool TopLeft, bool TopRight, bool BottomLeft, bool BottomRight, float Outline);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangleRounded(float PosX, float PosY, float Width, float Height, const ffw::color& Color, float Corner);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawRectangleRoundedOut(float PosX, float PosY, float Width, float Height, const ffw::color& Color, float Corner, float Outline);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawCircle(float PosX, float PosY, float Radius, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawCircleOut(float PosX, float PosY, float Radius, const ffw::color& Color, float Outline);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawTexture(float PosX, float PosY, float Width, float Height, ffw::texture2D *Texture, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawTextureMirrored(float PosX, float PosY, float Width, float Height,  bool MirrorX, bool MirrorY, ffw::texture2D *Texture, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawTextureSubsection(float PosX, float PosY, float Width, float Height, float StartX, float StartY, float SizeX, float SizeY, ffw::texture2D *Texture, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawString(float PosX, float PosY, trueType* Font, const std::string& Message, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawString(float PosX, float PosY, trueType* Font, const std::wstring& Message, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawText(float PosX, float PosY, trueType* Font, text* Message, const ffw::color& Color);
        /*!
            @memberof renderUtilities
            @ingroup Core
        */
        void drawLine(float StartX, float StartY, float EndX, float EndY, const ffw::color& Color);

    private:
        ffw::shader arcShader;
        ffw::shader rectShader;
        ffw::shader textureShader;
        ffw::shader fontShader;
        ffw::shader lineShader;

        int arcShaderViewLoc;
        int arcShaderPosLoc;
        int arcShaderSizeLoc;
        int arcShaderColorLoc;
        int arcShaderAngleLoc;
        int arcShaderStepsLoc;
        bool arcShaderUniform = false;

        int rectShaderViewLoc;
        int rectShaderPosLoc;
        int rectShaderSizeLoc;
        int rectShaderColorLoc;
        bool rectShaderUniform = false;

        int textureShaderViewLoc;
        int textureShaderPosLoc;
        int textureShaderSizeLoc;
        int textureShaderTexSamplerLoc;
        int textureShaderMirrorLoc;
        int textureShaderRstvLoc;
        int textureShaderColorLoc;
        bool textureShaderUniform = false;

        int lineShaderViewLoc;
        int lineShaderStartLoc;
        int lineShaderEndLoc;
        int lineShaderColorLoc;
        bool lineShaderUniform = true;

        int arcShaderSteps = 24;

        bool graphicsShadersLoaded = false;
        int mirror[2];

        int viewport[4];
        int viewportPush[4];


        PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
        PFNGLACTIVETEXTUREPROC glActiveTexture;
        PFNGLDRAWBUFFERSPROC glDrawBuffers;
    };
};
#endif

