/*** This file is part of FragmentFramework project ***/

#ifndef FFW_MUTEX
#define FFW_MUTEX

#include "../common.h"

/*!
 * @ingroup Utilities
 */
namespace ffw{
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Default mutex class
     */
	class FFW_API mutex {
	public:
		mutex();
		mutex(mutex&& Other);
		virtual ~mutex();
		/*!
         * @memberof mutex
         * @ingroup Utilities
		 * @brief Locks the mutex (blocking)
		 * @return False if an error occured
         */
		bool lock();
		/*!
         * @memberof mutex
         * @ingroup Utilities
		 * @brief Tries to lock the mutex (non-blocking)
		 * @return False if failed to lock
         */
		bool tryLock();
		/*!
         * @memberof mutex
         * @ingroup Utilities
		 * @brief Unlocks the mutex (blocking)
		 * @return False if an error occured
         */
		bool unlock();
		mutex& operator = (mutex&& Other);
		mutex& operator = (const mutex& Other) = delete;
		mutex(const mutex& Other) = delete;
	private:
		class impl;
		impl* pimpl;
	};
};

#endif
