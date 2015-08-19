/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TCP_LISTENER
#define FFW_TCP_LISTENER

#include "networkUtils.hpp"

/*!
    @ingroup Network
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Network
    */
	class FFW_API tcpServer {
    public:
        tcpServer();
        ~tcpServer();
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool isListening() const;
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool isCreated() const;
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool create();
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool close();
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool closeClient(SOCKET* Client);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool acceptClient(SOCKET* Client, int* Address, unsigned short* Port);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool listenPort(unsigned short Port);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool setNonBlocking(bool NonBlocking);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int sendMessage(SOCKET Client, const std::string& Message);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int sendMessageRaw(SOCKET Client, const char* Buffer, size_t BufferSize);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int getMessage(SOCKET Client, std::string* Message);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int getMessageRaw(SOCKET Client, char* Buffer, size_t BufferSize);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        void setMaximumConnections(int Max);

    private:
        class impl;
        impl* pimpl;
    };
};
#endif
