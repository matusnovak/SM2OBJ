/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOAD_SAVE_GEOMETRY
#define FFW_LOAD_SAVE_GEOMETRY

#include "../config.h"
#include "../utilities/fileUtilities.hpp"
#include <string>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API geometryFileLoader {
    public:
        geometryFileLoader();
        virtual ~geometryFileLoader();
        /*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::string& Path) = 0;
        /*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
        virtual void close() = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool eof() const  = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool loadObject(unsigned int Index) = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int getObjectCount() const = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectVertices(unsigned int Index) const = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectNormals(unsigned int Index) const = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int hasObjectTexPos(unsigned int Index) const = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual const std::string& getObjectName(unsigned int Index) const = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual unsigned int getTriangleCount() = 0;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
            @pure
        */
		virtual bool getTriangle(ffw::vec3f* P0, ffw::vec3f* P1, ffw::vec3f* P2, ffw::vec3f* N0, ffw::vec3f* N1, ffw::vec3f* N2, ffw::vec2f* T0, ffw::vec2f* T1, ffw::vec2f* T2) = 0;
        /*!
            @memberof geometryFileLoader
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof geometryFileLoader
            @ingroup Utilities
        */
		operator bool () const;
    protected:
		geometryFileLoader(const geometryFileLoader& Other) = default;
		geometryFileLoader& operator = (const geometryFileLoader& Other) = default;
        bool loaded;
    };

	/*!
        @memberof ffw
        @ingroup Utilities
    */
    class FFW_API geometryFileSaver {
    public:
        geometryFileSaver();
        virtual ~geometryFileSaver();
		/*!
            @memberof geometryFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::string& Path) = 0;
		/*!
            @memberof geometryFileSaver
            @ingroup Utilities
            @pure
        */
		virtual bool open(const std::wstring& Path) = 0;
		/*!
            @memberof geometryFileSaver
            @ingroup Utilities
            @pure
        */
		virtual void close() = 0;
        /*!
            @memberof geometryFileSaver
            @ingroup Utilities
        */
        bool isOpen() const;
		/*!
            @memberof geometryFileSaver
            @ingroup Utilities
        */
		operator bool () const;
	protected:
		geometryFileSaver(const geometryFileSaver& Other) = default;
		geometryFileSaver& operator = (const geometryFileSaver& Other) = default;
		bool loaded;
	};

	template<class T> class geometryLoader: public geometryFileLoader {
	};

	template<class T> class geometrySaver: public geometryFileSaver {
	};
};
#endif

