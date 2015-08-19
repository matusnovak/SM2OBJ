/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_FILE
#define FFW_FILE

#include "../config.h"
#include <string>
#include <fstream>

/*!
    @ingroup Utilities
*/
namespace ffw{
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	class FFW_API file{
    public:
        file();
        ~file();
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool open(const std::string& Path, bool IsBinary, bool Write, bool DeleteContents);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool open(const std::wstring& Path, bool IsBinary, bool Write, bool DeleteContents);
        /*!
            @memberof file
            @ingroup Utilities
        */
        void close();
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool isOpen();
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool read(void* Data, size_t Size);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool write(void* Data, size_t Size);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool readLine(std::string* Str);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool writeLine(const std::string& Str);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool readChar(char* Chr);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool writeChar(char Chr);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoPos(unsigned int Pos);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoPosOffset(unsigned int Pos);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoLine(unsigned int Num);
		/*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoLineOffset(unsigned int Num);
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoEnd();
		/*!
            @memberof file
            @ingroup Utilities
        */
		bool reset();
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool gotoBeginning();
        /*!
            @memberof file
            @ingroup Utilities
        */
		size_t countLines();
        /*!
            @memberof file
            @ingroup Utilities
        */
		size_t getSize();
        /*!
            @memberof file
            @ingroup Utilities
        */
		size_t getPos();
        /*!
            @memberof file
            @ingroup Utilities
        */
        bool eof();
    private:
        std::fstream fileStream;
    };
};
#endif
