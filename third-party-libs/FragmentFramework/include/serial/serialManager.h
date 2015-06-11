/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_SERIAL
#define FFW_SERIAL

#include "../dll.h"
#include <string>
#include <windows.h>

/*!
    @ingroup Serial
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Serial
    */
	class FFW_API serialManager {
    public:
        serialManager();
        ~serialManager();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool connect(const std::string& portName, unsigned int baudRate);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool isConnected();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        unsigned int isSerialAvailable();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool sendMessage(std::string message);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool sendBytes(char* data, unsigned int length);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool readBytes(char* data, unsigned int length);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool disconnect();

    private:
        HANDLE serialHandler;
        COMSTAT serialStatus;
        DWORD serialError;
        bool connected;
    };
};
#endif
