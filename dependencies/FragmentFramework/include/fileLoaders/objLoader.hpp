/*** This file is part of FragmentFramework project ***/

#ifndef FFW_OBJ_LOADER
#define FFW_OBJ_LOADER

#include "geomLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit geometryLoader
	 * @brief OBJ file loader
	 */
	class FFW_API objLoader: public geometryLoader {
	public:
		objLoader();
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @brief Move constructor
		 */
		objLoader(objLoader&& Other);
		~objLoader();
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool open(const std::string& Path) override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool open(const std::wstring& Path) override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		void close() override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		bool eof() const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool loadObject(unsigned int Index) override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		unsigned int getObjectCount() const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		unsigned int hasObjectVertices(unsigned int Index) const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		unsigned int hasObjectNormals(unsigned int Index) const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		unsigned int hasObjectTexPos(unsigned int Index) const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		const std::string& getObjectName(unsigned int Index) const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 * @const
		 */
		unsigned int getTriangleCount() const override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 * @override
		 */
		bool getTriangle(ffw::vec3f* P0, ffw::vec3f* P1, ffw::vec3f* P2, ffw::vec3f* N0, ffw::vec3f* N1, ffw::vec3f* N2, ffw::vec2f* T0, ffw::vec2f* T1, ffw::vec2f* T2) override;
		/*!
		 * @memberof objLoader
		 * @ingroup File-Loaders
		 */
		objLoader& operator = (objLoader&& Other);
		// Copy constructor is not allowed
		objLoader(const objLoader& Other) = delete;
		// Copy assigment is not allowed
		objLoader& operator = (const objLoader& Other) = delete;

	private:
		class impl;
		impl* pimpl;
	};
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOBJ(const std::string& Path, float** Vertices, unsigned int* NumVertices);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API loadOBJ(const std::wstring& Path, float** Vertices, unsigned int* NumVertices);
};
#endif
