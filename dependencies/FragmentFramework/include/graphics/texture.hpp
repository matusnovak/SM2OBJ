/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TEXTURE_BASE
#define FFW_TEXTURE_BASE

#include "../common.h"

/*!
 * @ingroup Graphics
 */
namespace ffw {
	class renderContext;
	/*!
     * @memberof ffw
     * @ingroup Graphics
	 *
     * @brief Base class for texture formats
	 *
     * @warning Do not use this class! This class is useless
     * without using derived classes.
	 *
     * @see texture1D, texture2D, texture3D
     */
	class FFW_API texture {
    public:
        texture();
        virtual ~texture();
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Checks if texture is loaded
         */
        bool isCreated() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Destroys the texture
         */
        void destroy();
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Binds the texture
         */
        void bind() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Unbinds the texture
         */
        void unbind() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the texture handle (OpenGL pointer)
         */
        unsigned int getHandle() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the texture width
         */
        int getWidth() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the texture height
         */
        int getHeight() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the number of layers (if array)
         */
        int getLayers() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the texture depth (if 3D)
         */
        int getDepth() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the internal format
         */
        unsigned int getInternalFormat() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the format
         */
        unsigned int getFormat() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the pixel format
         */
        unsigned int getPixelFormat() const;
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @const
         * @brief Returns the texture format
         */
        unsigned int getTextureFormat() const;
		/*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets integer enviroment parameter
		 * @param Target Target of the parameter
		 * @param Name Name of the parameter
		 * @param Value Value to set
         */
        void setEnvParami(unsigned int Target, unsigned int Name, int Value);
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets float enviroment parameter
		 * @param Target Target of the parameter
		 * @param Name Name of the parameter
		 * @param Value Value to set
         */
        void setEnvParamf(unsigned int Target, unsigned int Name, float Value);
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets integer texture parameter
		 * @param Name Name of the parameter
		 * @param Value Value to set
         */
        void setTexParami(unsigned int Name, int Value);
		/*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets integer texture parameter (array)
		 * @param Name Name of the parameter
		 * @param Value Array of values
         */
		void setTexParamiv(unsigned int Name, int* Values);
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets float texture parameter
		 * @param Name Name of the parameter
		 * @param Value Value to set
         */
        void setTexParamf(unsigned int Name, float Value);
		/*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Sets float texture parameter (array)
		 * @param Name Name of the parameter
		 * @param Value Array of values
         */
		void setTexParamfv(unsigned int Name, float* Values);
        /*!
         * @memberof texture
         * @ingroup Graphics
         * @brief Generates mipmaps
         */
        void generateMipmaps();

    protected:
        bool loaded;
        unsigned int textureFormat;
        unsigned int internalFormat;
        unsigned int format;
        unsigned int pixelFormat;
        unsigned int buffer;

        int width;
        int height;
        int depth;
        int layers;
        bool mipmaps;
        bool initialized;

        const glExtensions* gl;
    };
};
#endif
