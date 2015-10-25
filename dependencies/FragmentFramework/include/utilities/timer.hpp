/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_TIMER
#define FFW_TIMER

#include "../common.h"

/*!
 * @ingroup Utilities
 */
namespace ffw{
    /*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Timer class
	 * @details This class acts as a stopwatch.
	 * The following code captures a time interval:
	 *
	 * ```C++
	 * int main(){
	 *     ffw::timer myTimer;
	 *     myTimer.begin();
	 *     
	 *     // Do something
	 *     for(int i = 0; i < 5; i++){
	 *         // Wait for half a second
	 *         ffw::usleep(500000);
	 *         std::cout << "Delay!" << std::endl;
	 *     }
	 *     
	 *     myTimer.end();
	 *     std::cout << "Time took: " << myTimer.getTimeMicro()
	 *               << " micro seconds!" << std::endl;
	 * }
	 * ```
	 * This will print:
	 *
	 * ```
	 * Delay!
	 * Delay!
	 * Delay!
	 * Delay!
	 * Delay!
	 * Time took: 2500000 micro seconds!
	 * ```
     */
	class FFW_API timer{
    public:
        timer();
        /*!
         * @memberof timer
         * @ingroup Utilities
		 * @brief Starts the timer
         */
        void begin();
        /*!
         * @memberof timer
         * @ingroup Utilities
		 * @brief Stops the timer
         */
        void end();
        /*!
         * @memberof timer
         * @ingroup Utilities
		 * @brief Returns the time in seconds
         */
        double getTime();
        /*!
         * @memberof timer
         * @ingroup Utilities
		 * @brief Returns the time in milli seconds
         */
        unsigned long long getTimeMilli();
        /*!
         * @memberof timer
         * @ingroup Utilities
		 * @brief Returns the time in micro seconds
         */
        unsigned long long getTimeMicro();

    private:
        std::chrono::steady_clock::time_point t1;
        std::chrono::steady_clock::time_point t2;
    };
};
#endif
