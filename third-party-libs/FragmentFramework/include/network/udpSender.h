/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UDP_SENDER
#define FFW_UDP_SENDER

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
	class FFW_API udpSender {
    public:
        udpSender();
        ~udpSender();
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool isConnected() const;
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool isCreated() const;
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool create();
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool close();
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool connectTo(std::string Address, unsigned short Port);
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool connectTo(int Address, unsigned short Port);
        /*!
            @memberof udpSender
            @ingroup Network
        */
        bool setNonBlocking(bool NonBlocking);
        /*!
            @memberof udpSender
            @ingroup Network
        */
        int sendMessage(std::string Message);
        /*!
            @memberof udpSender
            @ingroup Network
        */
        int sendMessageRaw(char* Buffer, unsigned int Length);

    private:
        bool created;
        bool connected;
        SOCKET socketHandle;
        sockaddr_in listenerAddress;
        bool nonBlocking;
    };
};
#endif
