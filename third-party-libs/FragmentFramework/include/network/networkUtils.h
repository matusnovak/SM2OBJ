/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_NETWORK_UTILS
#define FFW_NETWORK_UTILS

#include "../dll.h"
#include <vector>
#include <string>

/*!
    @ingroup Network
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Network
    */
    bool FFW_API initWinsock();
    /*!
        @memberof ffw
        @ingroup Network
    */
	void FFW_API closeWinsock();
    /*!
        @memberof ffw
        @ingroup Network
    */
	std::vector<std::string> FFW_API getLocalAddresses();
    /*!
        @memberof ffw
        @ingroup Network
    */
	const unsigned int FFW_API stringToIpAddress(std::string address);
    /*!
        @memberof ffw
        @ingroup Network
    */
	const std::string FFW_API ipAddressToString(unsigned int address);
    /*!
        @memberof ffw
        @ingroup Network
    */
	int FFW_API getLastWsaError();
    /*!
        @memberof ffw
        @ingroup Network
    */
	const std::string FFW_API getWsaErrorStr(int Error);
};
#endif
