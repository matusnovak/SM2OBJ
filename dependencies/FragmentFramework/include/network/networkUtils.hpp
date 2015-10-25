/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_NETWORK_UTILS
#define FFW_NETWORK_UTILS

#include "../common.h"

/*!
 * @defgroup Network
 */



/*!
 * @ingroup Network
 */
namespace ffw {
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Initializes network
     */
    bool FFW_API initNetwork();
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Terminates network
     */
	void FFW_API terminateNetwork();
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Returns local IP address(es)
	 * @details If the machine has more than one
	 * network adapters, the returned vector will contains
	 * all of the local IPs.
     */
	std::vector<std::string> FFW_API getLocalAddresses();
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Converts IP address in string format to integer format
	 * @details For example: "192.168.0.1" will be converted to 16820416 (0x100A8C0)
     */
	unsigned int FFW_API stringToIpAddress(const std::string& address);
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Converts IP address in integer format to string format
	 * @details For example: 16820416 (0x100A8C0) will be converted to "192.168.0.1"
     */
	std::string FFW_API ipAddressToString(unsigned int address);
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Returns last network error
     */
	int FFW_API getLastNetworkError();
    /*!
     * @memberof ffw
     * @ingroup Network
	 * @brief Returns network error in string format
     */
	std::string FFW_API getNetworkErrorStr(int Error);
};
#endif
