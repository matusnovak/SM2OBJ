/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_GEOMETRY
#define FFW_LOAD_SAVE_GEOMETRY

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API geometryLoader {
    public:
        geometryLoader();
        virtual ~geometryLoader();
        /*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual bool eof() const  = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual bool loadObject(unsigned int Index) = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int getObjectCount() const = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectVertices(unsigned int Index) const = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectNormals(unsigned int Index) const = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectTexPos(unsigned int Index) const = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual const std::string& getObjectName(unsigned int Index) const = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int getTriangleCount() = 0;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
            @pure
        */
		virtual bool getTriangle(ffw::vec3f* P0, ffw::vec3f* P1, ffw::vec3f* P2, ffw::vec3f* N0, ffw::vec3f* N1, ffw::vec3f* N2, ffw::vec2f* T0, ffw::vec2f* T1, ffw::vec2f* T2) = 0;
        /*!
            @memberof geometryLoader
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof geometryLoader
            @ingroup Utilities
        */
		operator bool () const;
    protected:
		geometryLoader(const geometryLoader& Other) = default;
		geometryLoader& operator = (const geometryLoader& Other) = default;
        bool loaded;
    };

	/*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API geometrySaver {
    public:
        geometrySaver();
        virtual ~geometrySaver();
		/*!
            @memberof geometrySaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::string& Path) = 0;
		/*!
            @memberof geometrySaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::wstring& Path) = 0;
		/*!
            @memberof geometrySaver
            @ingroup Utilities
            @pure
        */
		virtual void close() = 0;
        /*!
            @memberof geometrySaver
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof geometrySaver
            @ingroup Utilities
        */
		operator bool () const;
	protected:
		geometrySaver(const geometrySaver& Other) = default;
		geometrySaver& operator = (const geometrySaver& Other) = default;
		bool loaded;
	};
};
#endif

