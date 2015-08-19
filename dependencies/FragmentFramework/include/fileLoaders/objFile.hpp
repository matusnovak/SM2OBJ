/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_OBJ
#define FFW_LOAD_SAVE_OBJ

#include "geomFile.hpp"

/*!
    @ingroup Utilities
*/
namespace ffw{
	class objFile{};
	/*!
        @memberof ffw
        @ingroup Utilities
    */
	template <> class FFW_API geometryLoader<objFile>: public geometryFileLoader {
	public:
		geometryLoader();
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		geometryLoader(geometryLoader&& Other);
		~geometryLoader();
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		bool open(const std::string& Path) override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		bool open(const std::wstring& Path) override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		void close() override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		bool eof() const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		bool loadObject(unsigned int Index) override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		unsigned int getObjectCount() const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		unsigned int hasObjectVertices(unsigned int Index) const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		unsigned int hasObjectNormals(unsigned int Index) const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		unsigned int hasObjectTexPos(unsigned int Index) const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		const std::string& getObjectName(unsigned int Index) const override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		unsigned int getTriangleCount() override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		bool getTriangle(ffw::vec3f* P0, ffw::vec3f* P1, ffw::vec3f* P2, ffw::vec3f* N0, ffw::vec3f* N1, ffw::vec3f* N2, ffw::vec2f* T0, ffw::vec2f* T1, ffw::vec2f* T2) override;
		/*!
            @memberof geometryLoader<objFile>
            @ingroup Utilities
        */
		geometryLoader& operator = (geometryLoader&& Other);
		// Copy constructor is not allowed
		geometryLoader(const geometryLoader& Other) = delete;
		// Copy assigment is not allowed
		geometryLoader& operator = (const geometryLoader& Other) = delete;

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
