/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_UDP_LISTENER
#define FFW_UDP_LISTENER

#include "../common.h"

/*!
    @ingroup Network
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Network
    */
	class FFW_API udpListener {
    public:
        udpListener();
        ~udpListener();
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool isListening() const;
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool isCreated() const;
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool create();
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool close();
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool listenPort(unsigned short Port);
        /*!
            @memberof udpListener
            @ingroup Network
        */
        bool setNonBlocking(bool NonBlocking);
        /*!
            @memberof udpListener
            @ingroup Network
        */
        int getMessage(std::string* Message, int* Address);
        /*!
            @memberof udpListener
            @ingroup Network
        */
        int getMessageRaw(char* Buffer, size_t Length, int* Address);

    private:
        class impl;
        impl* pimpl;
    };
};
#endif

