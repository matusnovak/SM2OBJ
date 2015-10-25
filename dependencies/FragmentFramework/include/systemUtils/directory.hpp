/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_DIR
#define FFW_DIR

#include "../common.h"

/*!
 * @ingroup System-Utilities
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup System-Utilities
     */
	class FFW_API directory {
    public:
		directory();
		~directory();
        /*!
		 * @memberof directory
		 * @ingroup System-Utilities
		 */
        bool open(std::string path);
        /*!
		 * @memberof directory
		 * @ingroup System-Utilities
		 */
		const std::vector<std::string>& getDirs();
        /*!
		 * @memberof directory
		 * @ingroup System-Utilities
		 */
		const std::vector<std::string>& getFiles();

    private:

        std::vector<std::string>* files;
        std::vector<std::string>* dirs;
    };
};
#endif
