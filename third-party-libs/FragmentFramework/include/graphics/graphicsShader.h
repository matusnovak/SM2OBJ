/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_GRAPHICS_SHADER
#define FFW_GRAPHICS_SHADER

#include "../dll.h"
#include "../math/math.h"
#include "../utilities/loadSaveTxt.h"

#include <GL/glfw3.h>
#include <GL/glext.h>

/*!
    @ingroup Graphics
*/
namespace ffw {
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
        bool init();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool isLoaded() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        const std::string& getCompileLog() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool loadFromFile(std::string geomPath, std::string vertPath, std::string fragPath);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool loadFromData(const GLchar* geomData, const GLchar* vertData, const GLchar* fragData);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool deleteShader();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        GLuint getProgram() const;
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setAttributePointerf(GLint location, GLint size, GLsizei stride, GLsizei offset);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawArrays(GLenum type, GLint first, GLsizei count);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElements(GLenum type, GLsizei count, const GLvoid * indices);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElementsRange(GLenum type, GLuint start, GLuint end, GLsizei count, const GLvoid * indices);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void drawElementsBaseVertex(GLenum type, GLsizei count, const GLvoid * indices, GLint offset);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool begin();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        bool end();
        /*!
            @memberof shader
            @ingroup Graphics

        */
        int getUniformLocation(const GLchar* Name);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        int getAttributeLocation(const GLchar* Name);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1f   (GLint location, GLfloat value);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1fv  (GLint location, GLfloat* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1i   (GLint location, GLint value);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform1iv  (GLint location, GLint* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2f   (GLint location, GLfloat x, GLfloat y);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2fv  (GLint location, GLfloat* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2i   (GLint location, GLint x, GLint y);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2iv  (GLint location, GLint* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3f   (GLint location, GLfloat x, GLfloat y, GLfloat z);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3fv  (GLint location, GLfloat* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3i   (GLint location, GLint x, GLint y, GLint z);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3iv  (GLint location, GLint* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f   (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv  (GLint location, GLfloat* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
		void setUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4iv  (GLint location, GLint* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2f   (GLint location, ffw::vec2f vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2fv  (GLint location, ffw::vec2f* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2i   (GLint location, ffw::vec2i vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform2iv  (GLint location, ffw::vec2i* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3f   (GLint location, ffw::vec3f vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3fv  (GLint location, ffw::vec3f* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3i   (GLint location, ffw::vec3i vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform3iv  (GLint location, ffw::vec3i* array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f   (GLint location, ffw::vec4f vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv  (GLint location, ffw::vec4f*  array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4i   (GLint location, ffw::vec4i vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4iv  (GLint location, ffw::vec4i*  array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4f   (GLint location, ffw::color vec);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniform4fv  (GLint location, ffw::color*  array, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix2fv    (GLint location, GLfloat* mat, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix3fv    (GLint location, GLfloat* mat, GLsizei length);
        /*!
            @memberof shader
            @ingroup Graphics

        */
        void setUniformMatrix4fv    (GLint location, GLfloat* mat, GLsizei length);

    private:
        // Compile shader
        bool compileShader(GLuint &thisShader, const GLchar* data, GLenum shaderType);
        // Check for shader compilation errors
        bool checkForShaderErrors(GLuint thisShader, std::string* ErrorStr);
        // Check for program linking errors
        bool checkForProgramErrors(std::string* ErrorStr);
        // Is shader loaded?
        bool loaded;
        // Shader program
        GLuint program;
        // Geometry shader
        GLuint geomShader;
        // Vertex shader
        GLuint vertShader;
        // Fragment shader
        GLuint fragShader;
        // Is geometry shader loaded?
        bool usingGeom;
        // Is vertex shader loaded?
        bool usingVert;
        // Is fragment shader loaded?
        bool usingFrag;
		std::string* errorLogStr;

        bool initialized;

        PFNGLUSEPROGRAMPROC glUseProgram;
        PFNGLCOMPILESHADERPROC glCompileShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLDELETEPROGRAMPROC glDeleteProgram;
        PFNGLDELETESHADERPROC glDeleteShader;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLSHADERSOURCEPROC glShaderSource;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
        PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
        PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
        PFNGLUNIFORM1FPROC glUniform1f;
        PFNGLUNIFORM1FVPROC glUniform1fv;
        PFNGLUNIFORM1IPROC glUniform1i;
        PFNGLUNIFORM1IVPROC glUniform1iv;
        PFNGLUNIFORM2FPROC glUniform2f;
        PFNGLUNIFORM2FVPROC glUniform2fv;
        PFNGLUNIFORM2IPROC glUniform2i;
        PFNGLUNIFORM2IVPROC glUniform2iv;
        PFNGLUNIFORM3FPROC glUniform3f;
        PFNGLUNIFORM3FVPROC glUniform3fv;
        PFNGLUNIFORM3IPROC glUniform3i;
        PFNGLUNIFORM3IVPROC glUniform3iv;
        PFNGLUNIFORM4FPROC glUniform4f;
        PFNGLUNIFORM4FVPROC glUniform4fv;
        PFNGLUNIFORM4IPROC glUniform4i;
        PFNGLUNIFORM4IVPROC glUniform4iv;
        PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
        PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
    };
};
#endif
