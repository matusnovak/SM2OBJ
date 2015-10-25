/*** This file is part of FragmentFramework project ***/

#ifndef FFW_UDP_SENDER
#define FFW_UDP_SENDER

#include "../common.h"

/*!
 * @ingroup Network
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Network
     */
	class FFW_API udpSender {
    public:
        udpSender();
		udpSender(udpSender&& Other);
		udpSender(const udpSender& Other) = delete;
        ~udpSender();
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @const
		 * @brief Checks if connected
         */
        bool isConnected() const;
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @const
		 * @brief Checks if created
         */
        bool isCreated() const;
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Creates the sender
         */
        bool create();
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Closes the sender
         */
        bool close();
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Connects to remote address
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The remote address is invalid
		 * * The port is blocked
         */
        bool connect(const std::string& Address, unsigned short Port);
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Connects to remote address
		 * @return False if one of following:
		 * * The network has not been initialized
		 * * The function create() has not been called or failed
		 * * The remote address is invalid
		 * * The port is blocked
         */
        bool connect(int Address, unsigned short Port);
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @details When non-blocking is disabled, the write()
		 * functions will block the thread when called.
		 * @return False if failed
         */
        bool setNonBlocking(bool NonBlocking);
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Writes a data
		 * @param Message What message to send
		 * @return Number of bytes written
         */
        int write(const std::string& Message);
        /*!
         * @memberof udpSender
         * @ingroup Network
		 * @brief Writes a data
		 * @param Buffer Pointer to the data to send
		 * @param Length Size of the buffer
		 * @return Number of bytes written
         */
        int write(const char* Buffer, size_t Length);

		udpSender& operator = (const udpSender& Other) = delete;
		udpSender& operator = (udpSender&& Other);
    private:
        class impl;
        impl* pimpl;
    };
};
#endif
