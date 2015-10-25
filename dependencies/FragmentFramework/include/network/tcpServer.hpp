/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TCP_LISTENER
#define FFW_TCP_LISTENER

#include "../common.h"

/*!
 * @ingroup Network
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Network
     */
	class FFW_API tcpServer {
    public:
        tcpServer();
		tcpServer(tcpServer&& Other);
		tcpServer(const tcpServer& Other) = delete;
        ~tcpServer();
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @const
		 * @brief Checks if the server is listening
         */
        bool isListening() const;
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @const
		 * @brief Checks if the server is created
         */
        bool isCreated() const;
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Creates the server
         */
        bool create();
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Closes the server
         */
        bool close();
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Drops a client
         */
        bool dropClient(unsigned int* Client);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Accepts a client
         */
        bool acceptClient(unsigned int* Client, int* Address, unsigned short* Port);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Starts listening to a port
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The port is blocked
         */
        bool listen(unsigned short Port);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Sets non-blocking flag
		 * @details When non-blocking is disabled, the write() and read()
		 * functions will block the thread when called.
		 * @return False if failed
         */
        bool setNonBlocking(bool NonBlocking);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Writes a message to the client
		 * @param Client Index of the client
		 * @param Message What message to send
		 * @return Number of bytes written
         */
        int write(unsigned int Client, const std::string& Message);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Writes a message to the client
		 * @param Client Index of the client
		 * @param Buffer Pointer to the buffer to read from
		 * @param BufferSize Size of the buffer
		 * @return Number of bytes written
         */
        int write(unsigned int Client, const char* Buffer, size_t BufferSize);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Reads a message from the client
		 * @param Client Index of the client
		 * @param Message Where to store the message
		 * @return The number of bytes read
         */
        int read(unsigned int Client, std::string* Message);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Reads a message from the client
		 * @param Client Index of the client
		 * @param Buffer Where to store the message
		 * @param BufferSize How many bytes to read
		 * @return The number of bytes read
         */
        int read(unsigned int Client, char* Buffer, size_t BufferSize);
        /*!
         * @memberof tcpServer
         * @ingroup Network
		 * @brief Sets maximum connected clients
         */
        void setMaxConnections(int Max);

		tcpServer& operator = (const tcpServer& Other) = delete;
		tcpServer& operator = (tcpServer&& Other);
    private:
        class impl;
        impl* pimpl;
    };
};
#endif
