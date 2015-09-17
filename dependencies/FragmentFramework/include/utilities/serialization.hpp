/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SERIALIZATION
#define FFW_SERIALIZATION

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API serialization {
    public:
        /*!
            @memberof serialization
            @ingroup Utilities
        */
        bool serialize(ffw::var* Data, bool Formated);
        /*!
            @memberof serialization
            @ingroup Utilities
        */
        bool deserialize(ffw::var* Data, std::vector<std::string>* Missing);

        struct item {
            item(void* Ptr, const std::string& Name, size_t Code):ptr(Ptr),name(Name),code(Code){}
            void* ptr;
            std::string name;
            size_t code;
        };

    private:
		std::vector<item> varList;

    protected:
        /*!
            @memberof serialization
            @ingroup Utilities
            @protected
        */
        template <class T> void serializeItem(T* Ptr, const std::string& Name){
            varList.push_back(item(Ptr, Name, typeid(T).hash_code()));
        }

    };
};
#endif

