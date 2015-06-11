/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LIST_DIRECTORY
#define FFW_LIST_DIRECTORY

#include "../dll.h"
#include "../math/math.h"
#include <vector>
#include <string>

/*!
    @ingroup System
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup System
    */
	class FFW_API listDirectory {
    public:
		listDirectory();
		~listDirectory();
        /*!
            @memberof listDirectory
            @ingroup System
        */
        bool open(std::string path);
        /*!
            @memberof listDirectory
            @ingroup System
        */
		const std::vector<std::string>& getDirectories();
        /*!
            @memberof listDirectory
            @ingroup System
        */
		const std::vector<std::string>& getFiles();

    private:
        bool isFileDirectory(std::string path);

        std::vector<std::string>* files;
        std::vector<std::string>* dirs;
    };
};
#endif
