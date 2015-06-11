/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TCP_CLIENT
#define FFW_TCP_CLIENT

#include "../dll.h"
#include "networkUtils.h"
#include <winsock.h>

/*!
    @ingroup Network
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Network
    */
	class FFW_API tcpClient {
    public:
        tcpClient();
        ~tcpClient();
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool isConnected() const;
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool isCreated() const;
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool create();
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool close();
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool connectTo(std::string Address, unsigned short Port);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool connectTo(int Address, unsigned short Port);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        bool setNonBlocking(bool NonBlocking);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        int sendMessage(std::string Message);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        int sendMessageRaw(char* Buffer, size_t BufferSize);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        int getMessage(std::string* Message);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        int getMessageRaw(char* Buffer, size_t BufferSize);
        /*!
            @memberof tcpClient
            @ingroup Network
        */
        void setConnectionTimeout(int Seconds);

    private:
        bool created;
        bool connected;
        SOCKET socketHandle;
        bool nonBlocking;
        int msgBufferSize;
        char* msgBuffer;
        int connectionTimeoutSec;
    };
};
#endif
