/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UDP_SENDER
#define FFW_UDP_SENDER

#include "../common.h"

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
        bool connectTo(const std::string& Address, unsigned short Port);
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
        int sendMessage(const std::string& Message);
        /*!
            @memberof udpSender
            @ingroup Network
        */
        int sendMessageRaw(char* Buffer, size_t Length);

    private:
        class impl;
        impl* pimpl;
    };
};
#endif
