/*** This file is part of FragmentFramework project ***/

#ifndef FFW_GEOM_SAVER
#define FFW_GEOM_SAVER

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
    class FFW_API geometrySaver {
    public:
        geometrySaver();
        virtual ~geometrySaver();
		virtual bool open(const std::string& Path) = 0;
		virtual bool open(const std::wstring& Path) = 0;
		virtual void close() = 0;
        bool isOpen() const;
		operator bool () const;
	protected:
		geometrySaver(const geometrySaver& Other) = default;
		geometrySaver& operator = (const geometrySaver& Other) = default;
		bool loaded;
	};
};
#endif

