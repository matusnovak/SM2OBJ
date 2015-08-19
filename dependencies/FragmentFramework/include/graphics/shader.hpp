/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_SHADER
#define FFW_GRAPHICS_SHADER

#include "../config.h"
#include "../math/math.h"
#include "../gl/extensions.hpp"
#include <string>

/*!
    @ingroup Graphics
*/
namespace ffw {
    class renderContext;
    /*!
        @memberof ffw
        @ingroup Graphics
    */
	class FFW_API shader {
    public:
        shader();
        virtual ~shader();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool init(renderContext* Context);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool isCreated() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        const std::string& getCompileLog() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool loadFromFile(const std::string& geomPath, const std::string& vertPath, const std::string& fragPath);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool loadFromData(const std::string& geomData, const std::string& vertData, const std::string& fragData);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool destroy();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        unsigned int getProgram() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setAttributePointerf(int Location, int Size, int Stride, int Offset) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setAttributeDivisor(unsigned int Index, unsigned int Divisor) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawArrays(unsigned int Mode, int First, int Count) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawArraysInstanced(unsigned int Mode, int First, int Count, int InstanceCount) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElements(unsigned int Mode, int Count, unsigned int Type, const void* Indices) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElementsRange(unsigned int Mode, unsigned int Start, unsigned int End, int Count, unsigned int Type, const void* Indices) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElementsInstanced(unsigned int Mode, int Count, unsigned int Type, const void* Indices, int InstanceCount) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool begin() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool end() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        int getUniformLocation(const char* Name) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        int getAttributeLocation(const char* Name) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1f(int location, float value) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1fv(int location, const float* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1i(int location, int value) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1iv(int location, const int* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2f(int location, float x, float y) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2fv(int location, const float* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2i(int location, int x, int y) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2iv(int location, const int* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3f(int location, float x, float y, float z) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3fv(int location, const float* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3i(int location, int x, int y, int z) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3iv(int location, const int* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f(int location, float x, float y, float z, float w) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv(int location, const float* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
		void setUniform4i(int location, int x, int y, int z, int w) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4iv(int location, const int* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2f(int location, const ffw::vec2f& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2fv(int location, const ffw::vec2f* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2i(int location, const ffw::vec2i& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2iv(int location, const ffw::vec2i* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3f(int location, const ffw::vec3f& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3fv(int location, const ffw::vec3f* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3i(int location, const ffw::vec3i& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3iv(int location, const  ffw::vec3i* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f(int location, const  ffw::vec4f& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv(int location, const ffw::vec4f* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4i(int location, const  ffw::vec4i& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4iv(int location, const ffw::vec4i*  array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f(int location, const  ffw::color& vec) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv(int location, const ffw::color* array, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix2fv(int location, const float* mat, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix3fv(int location, const float* mat, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix4fv(int location, const float* mat, int length) const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix4fv(int location, const mat4 mat, int length) const;

    private:
        // Compile shader
        bool compileShader(unsigned int &thisShader, const char* data, unsigned int shaderType);
        // Check for shader compilation errors
        bool checkForShaderErrors(unsigned int thisShader, std::string* ErrorStr);
        // Check for program linking errors
        bool checkForProgramErrors(std::string* ErrorStr);
        // Is shader loaded?
        bool loaded;
        // Shader program
        unsigned int program;
        // Geometry shader
        unsigned int geomShader;
        // Vertex shader
        unsigned int vertShader;
        // Fragment shader
        unsigned int fragShader;
        // Is geometry shader loaded?
        bool usingGeom;
        // Is vertex shader loaded?
        bool usingVert;
        // Is fragment shader loaded?
        bool usingFrag;
		std::string* errorLogStr;

        bool initialized;

        const glExtensions* gl;
    };
};
#endif