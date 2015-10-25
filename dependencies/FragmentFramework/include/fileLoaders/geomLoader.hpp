/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GEOM_LOADER
#define FFW_GEOM_LOADER

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Geomtry loader base class
	 */
    class FFW_API geometryLoader {
    public:
        geometryLoader();
        virtual ~geometryLoader();
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::string& Path) = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Closes the file
         */
        virtual void close() = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Checks if end of file
         */
		virtual bool eof() const  = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Loads object from file
         */
		virtual bool loadObject(unsigned int Index) = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Returns number of objects in file
         */
		virtual unsigned int getObjectCount() const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Checks if an object has vertices
         */
		virtual unsigned int hasObjectVertices(unsigned int Index) const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Checks if an object has normals
         */
		virtual unsigned int hasObjectNormals(unsigned int Index) const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Checks if an object has UV maps
         */
		virtual unsigned int hasObjectTexPos(unsigned int Index) const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Returns the object name
         */
		virtual const std::string& getObjectName(unsigned int Index) const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Returns the polygon (triangle) count of an object
         */
		virtual unsigned int getTriangleCount() const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @const
		 * @brief Reads one polygon (triangle)
         */
		virtual bool getTriangle(ffw::vec3f* P0, ffw::vec3f* P1, ffw::vec3f* P2, ffw::vec3f* N0, ffw::vec3f* N1, ffw::vec3f* N2, ffw::vec2f* T0, ffw::vec2f* T1, ffw::vec2f* T2) = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if the file is open
         */
        bool isOpen() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if the file is open
         */
		operator bool () const;
    protected:
		geometryLoader(const geometryLoader& Other) = default;
		geometryLoader& operator = (const geometryLoader& Other) = default;
        bool loaded;
    };
};
#endif

