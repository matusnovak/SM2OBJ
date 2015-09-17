/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TCP_LISTENER
#define FFW_TCP_LISTENER

#include "../common.h"

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
        bool closeClient(unsigned int* Client);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        bool acceptClient(unsigned int* Client, int* Address, unsigned short* Port);
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
			
			@code
			int main() {
			    int x;
				int y;
				for(){
					// do something
				}
			}
        */
        int sendMessage(unsigned int Client, const std::string& Message);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int sendMessageRaw(unsigned int Client, const char* Buffer, size_t BufferSize);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int getMessage(unsigned int Client, std::string* Message);
        /*!
            @memberof tcpServer
            @ingroup Network
        */
        int getMessageRaw(unsigned int Client, char* Buffer, size_t BufferSize);
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
