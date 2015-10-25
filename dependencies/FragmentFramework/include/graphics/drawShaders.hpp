/*** This file is part of FragmentFramework project ***/

#ifndef FFW_DRAW_SHADERS
#define FFW_DRAW_SHADERS

#include "../common.h"
#include "shader.hpp"

namespace ffw{
    class renderContext;

    class FFW_API drawShaders {
    public:
        drawShaders();
        ~drawShaders();

        bool create(const renderContext* Context);
		void destroy();

        shader genericShader;
        shader arcShader;
		shader fontShader;
		shader bezierShader;
		shader bezierAdvShader;

		mutable bool genShaderColor;
		mutable bool arcShaderColor;
		mutable bool fontShaderColor;
		mutable bool bezierShaderColor;
		mutable bool bezierAdvShaderColor;

		mutable ffw::color drawColor;

        int arcShaderMvpLoc;
        int arcShaderPosLoc;
        int arcShaderSizeLoc;
        int arcShaderColorLoc;
        int arcShaderAngleLoc;
        int arcShaderStepsLoc;

        int genShaderMvpLoc;
        int genShaderPosLoc;
        int genShaderColorLoc;
        int genShaderSamplerLoc;
        int genShaderUvsLoc;
        int genShaderBranchLoc;

		int fontShaderMvpLoc;
        int fontShaderSamplerLoc;
        int fontShaderColorLoc;
        int fontShaderPosLoc;
        int fontShaderUvsLoc;
        int fontShaderOffsetLoc;
        int fontShaderScaleLoc;

		int bezierShaderMvpLoc;
        int bezierShaderPointsLoc;
        int bezierShaderColorLoc;
        int bezierShaderStepsLoc;

		int bezierAdvShaderMvpLoc;
        int bezierAdvShaderPointsLoc;
        int bezierAdvShaderColorLoc;
        int bezierAdvShaderStepsLoc;
		int bezierAdvShaderThickLoc;
    };
};

#endif
