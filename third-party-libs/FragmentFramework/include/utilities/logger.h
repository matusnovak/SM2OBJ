/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOGGER
#define FFW_LOGGER

#include "../dll.h"
#include <string>
#include <sstream>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API logger {
    public:
        /*!
            @memberof logger
            @ingroup Utilities
            @static
        */
        static void initLogger(std::string Path);
        /*!
            @memberof logger
            @ingroup Utilities
            @static
        */
        static void initLogger();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& print();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& verbose();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& debug();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& notice();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& info();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& warning();
        /*!
            @memberof logger
            @ingroup Utilities
        */
        std::ostringstream& error();
        /*!
            @memberof logger
            @ingroup Utilities
            @static
        */
        static void clearLog();
        /*!
            @memberof logger
            @ingroup Utilities
            @static
        */
        static void setVerbosity(int Level);
        /*!
            @memberof logger
            @ingroup Utilities
            @static
        */
        static void setConsoleOutput(bool Enabled);
        virtual ~logger();

    private:
        int type;
        std::ostringstream os;
        void addLine();
        std::string getTime();
    };
};
#endif
