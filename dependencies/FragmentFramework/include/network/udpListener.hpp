/*** This file is part of FragmentFramework project ***/

#ifndef FFW_UDP_LISTENER
#define FFW_UDP_LISTENER

#include "../common.h"

/*!
 * @ingroup Network
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Network
     */
	class FFW_API udpListener {
    public:
        udpListener();
		udpListener(udpListener&& Other);
		udpListener(const udpListener& Other) = delete;
        ~udpListener();
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Checks if listening
         */
        bool isListening() const;
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Checks if crated
         */
        bool isCreated() const;
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Crates the listener
         */
        bool create();
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Closes the listener
         */
        bool close();
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Listens to a specific port
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The port is blocked
         */
        bool listen(unsigned short Port);
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Sets non-blocking flag
		 * @details When non-blocking is disabled, the read()
		 * functions will block the thread when called.
		 * @return False if failed
         */
        bool setNonBlocking(bool NonBlocking);
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Reads a data
		 * @param Message Where to store the data
		 * @param Address Where to store the address of the sender
		 * @return Number of bytes read
         */
        int read(std::string* Message, int* Address);
        /*!
         * @memberof udpListener
         * @ingroup Network
		 * @brief Reads a data
		 * @param Buffer Where to store the data
		 * @param Length How many bytes to read
		 * @param Address Where to store the address of the sender
		 * @return Number of bytes read
         */
        int read(char* Buffer, size_t Length, int* Address);

		udpListener& operator = (const udpListener& Other) = delete;
		udpListener& operator = (udpListener&& Other);
    private:
        class impl;
        impl* pimpl;
    };
};
#endif

