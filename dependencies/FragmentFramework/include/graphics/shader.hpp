/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GRAPHICS_SHADER
#define FFW_GRAPHICS_SHADER

#include "../common.h"

/*!
 * @ingroup Graphics
 */
namespace ffw {
    class renderContext;
    /*!
	 * @memberof ffw
	 * @ingroup Graphics
	 */
	class FFW_API shader {
    public:
		/*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @static
		 */
        static bool checkCompability(const renderContext* Renderer);
		
		shader();
        virtual ~shader();
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @brief Checks if shader is created
		 */
        bool isCreated() const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the compile log
		 */
        const std::string& getCompileLog() const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @brief Creates the shader from files
		 */
        bool createFromFile(const renderContext* Renderer, const std::string& geomPath, const std::string& vertPath, const std::string& fragPath);
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @brief Creates the shader from data
		 */
        bool createFromData(const renderContext* Renderer, const std::string& geomData, const std::string& vertData, const std::string& fragData);
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @brief Destroys the shader
		 */
        void destroy();
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Returns the shader handle (OpenGL pointer)
		 */
        unsigned int getHandle() const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets float attribute pointer
		 */
        void setAttributePointerf(int Location, int Size, int Stride, int Offset) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets attribute divisor
		 */
        void setAttributeDivisor(unsigned int Index, unsigned int Divisor) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Draws array
		 */
        void drawArrays(unsigned int Mode, int First, int Count) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Draws instanced array
		 */
        void drawArraysInstanced(unsigned int Mode, int First, int Count, int InstanceCount) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Draws elements (indices)
		 */
        void drawElements(unsigned int Mode, int Count, unsigned int Type, const void* Indices) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Draws specific range of elements (indices)
		 */
        void drawElementsRange(unsigned int Mode, unsigned int Start, unsigned int End, int Count, unsigned int Type, const void* Indices) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Draws instanced elements (indices)
		 */
        void drawElementsInstanced(unsigned int Mode, int Count, unsigned int Type, const void* Indices, int InstanceCount) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Binds the shader
		 */
        void bind() const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Unbinds the shader
		 */
        void unbind() const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Returns uniform location
		 */
        int getUniformLocation(const char* Name) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Returns attribute location
		 */
        int getAttributeLocation(const char* Name) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets float uniform
		 */
        void setUniform1f(int location, float value) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of floats uniform
		 */
        void setUniform1fv(int location, const float* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets integer uniform
		 */
        void setUniform1i(int location, int value) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of integer uniform
		 */
        void setUniform1iv(int location, const int* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 2D float vector uniform
		 */
        void setUniform2f(int location, float x, float y) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 2D float vectors uniform
		 */
        void setUniform2fv(int location, const float* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 2D integer vector uniform
		 */
        void setUniform2i(int location, int x, int y) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 2D integer vectors uniform
		 */
        void setUniform2iv(int location, const int* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 3D float vector
		 */
        void setUniform3f(int location, float x, float y, float z) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 3D float vectors uniform
		 */
        void setUniform3fv(int location, const float* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 3D integer vector uniform
		 */
        void setUniform3i(int location, int x, int y, int z) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 3D integer vectors uniform
		 */
        void setUniform3iv(int location, const int* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 4D float vector uniform
		 */
        void setUniform4f(int location, float x, float y, float z, float w) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4D float vectors uniform
		 */
        void setUniform4fv(int location, const float* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 4D integer vector uniform
		 */
		void setUniform4i(int location, int x, int y, int z, int w) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4D integer vectors uniform
		 */
        void setUniform4iv(int location, const int* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 2D float vector uniform
		 */
        void setUniform2f(int location, const ffw::vec2f& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 2D float vectors uniform
		 */
        void setUniform2fv(int location, const ffw::vec2f* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 2D integer vector uniform
		 */
        void setUniform2i(int location, const ffw::vec2i& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 2D integer vectors uniform
		 */
        void setUniform2iv(int location, const ffw::vec2i* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 3D float vector uniform
		 */
        void setUniform3f(int location, const ffw::vec3f& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 3D float vectors uniform
		 */
        void setUniform3fv(int location, const ffw::vec3f* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 3D integer vector uniform
		 */
        void setUniform3i(int location, const ffw::vec3i& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 3D integer vectors uniform
		 */
        void setUniform3iv(int location, const  ffw::vec3i* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 4D float vector uniform
		 */
        void setUniform4f(int location, const  ffw::vec4f& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4D float vectors uniform
		 */
        void setUniform4fv(int location, const ffw::vec4f* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 4D integer vector uniform
		 */
        void setUniform4i(int location, const  ffw::vec4i& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4D integer vectors uniform
		 */
        void setUniform4iv(int location, const ffw::vec4i*  array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets 4D float vector uniform from color
		 */
        void setUniform4f(int location, const  ffw::color& vec) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4D float vectors uniform from array of colors
		 */
        void setUniform4fv(int location, const ffw::color* array, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 2x2 float matrices uniform
		 */
        void setUniformMatrix2fv(int location, const float* mat, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 3x3 float matrices uniform
		 */
        void setUniformMatrix3fv(int location, const float* mat, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4x4 float matrices uniform
		 */
        void setUniformMatrix4fv(int location, const float* mat, int length) const;
        /*!
		 * @memberof shader
		 * @ingroup Graphics
		 * @const
		 * @brief Sets array of 4x4 float matrices uniform
		 */
        void setUniformMatrix4fv(int location, const mat4x4f* mat, int length) const;

    private:
        bool compileShader(unsigned int &thisShader, const char* data, unsigned int shaderType);
        bool checkForShaderErrors(unsigned int thisShader, std::string* ErrorStr);
        bool checkForProgramErrors(std::string* ErrorStr);
        bool loaded;
        unsigned int program;
        unsigned int geomShader;
        unsigned int vertShader;
        unsigned int fragShader;
        bool usingGeom;
        bool usingVert;
        bool usingFrag;
		std::string* errorLogStr;
        const glExtensions* gl;
    };
};
#endif
