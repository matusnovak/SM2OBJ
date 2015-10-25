/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TCP_CLIENT
#define FFW_TCP_CLIENT

#include "../common.h"

/*!
 * @ingroup Network
 */
namespace ffw {
    /*!
	 * @memberof ffw
     * @ingroup Network
     */
	class FFW_API tcpClient {
    public:
        tcpClient();
		tcpClient(tcpClient&& Other);
		tcpClient(const tcpClient& Other) = delete;
        ~tcpClient();
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @const
		 * @brief Checks if connected
         */
        bool isConnected() const;
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @const
		 * @brief Checks if client is created
         */
        bool isCreated() const;
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Creates a client
         */
        bool create();
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Closes a client
         */
        bool close();
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Connects to remote address
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The remote address is invalid
		 * * The port is blocked
		 * @param Address Remote address in string format, for example "192.168.0.1"
		 * @param Port Destination port
         */
        bool connect(const std::string& Address, unsigned short Port);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Connects to remote address
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The remote address is invalid
		 * * The port is blocked
         * @param Address Remote address in string format, for example "192.168.0.1"
		 * @param Port Destination port
         */
        bool connect(int Address, unsigned short Port);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Sets non-blocking flag
		 * @details When non-blocking is disabled, the write() and read()
		 * functions will block the thread when called.
		 * @return False if failed
         */
        bool setNonBlocking(bool NonBlocking);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Writes a message to the server
		 * @return Number of bytes written 
         */
        int write(const std::string& Message);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Writes a message to the server
		 * @return Number of bytes written
		 * @param Buffer Pointer to the buffer to read from
		 * @param BufferSize Size of the buffer
         */
        int write(const char* Buffer, size_t BufferSize);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Reads a message from the server
		 * @return Number of bytes read
		 * @param Message Where to store the message
         */
        int read(std::string* Message);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Reads a message from the server
		 * @return Number of bytes read
		 * @param Buffer Where to store the bytes
		 * @param BufferSize How many bytes to read
         */
        int read(char* Buffer, size_t BufferSize);
        /*!
         * @memberof tcpClient
         * @ingroup Network
		 * @brief Sets connection timeout when connecting to address
		 * @details The default value is 5 seconds
         */
        void setTimeout(int Seconds);
		
		tcpClient& operator = (const tcpClient& Other) = delete;
		tcpClient& operator = (tcpClient&& Other);
    private:
        class impl;
        impl* pimpl;
    };
};
#endif
