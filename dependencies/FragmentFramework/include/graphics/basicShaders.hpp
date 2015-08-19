/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_BASIC_SHADERS
#define FFW_BASIC_SHADERS

#include "../config.h"
#include "shader.hpp"

namespace ffw{
    class renderContext;

    class FFW_API basicShaders {
    public:
        basicShaders();
        ~basicShaders();

        bool init(renderContext* Context);
		void deleteShaders();

        shader genericShader;
        shader arcShader;
		shader fontShader;
		shader bezierShader;
		shader bezierAdvShader;

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
