/*** This file is part of FragmentFramework project ***/

#ifndef FFW_THREAD
#define FFW_THREAD

#include "../common.h"

/*!
 * @ingroup Utilities
 */
namespace ffw{
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Default thread class
	 * @details This class can be used to create a single thread.
	 * If more then one thread is needed, create more instances of this
	 * class.
	 * 
	 * The following code creates a simple thread:
	 *
	 * ```C++
	 * struct dataStruct {
	 *     std::string msg;
	 *     int counter;
	 * };
	 * 
	 * // This is a thread function
	 * // All thread functions must have one parameter void* and
	 * // return type of void*. This applies for both member and
	 * // non-member functions.
	 * void* threadFunc(void* Data){
	 *     struct dataStruct* threadData = static_cast<dataStruct*>(Data);
	 *     for(int i = 0; i < threadData->counter; i++){
	 *         // Sleep for half a second
	 *         ffw::usleep(500000);
	 *         std::cout << threadData->msg << i << std::endl;
	 *     }
	 *     return threadData->counter;
	 * }
	 * 
	 * int main(){
	 *      ...
	 *      ffw::thread myThread;
	 *      myThread.bindFunction(&threadFunc);
	 *      
	 *      dataStruct myData;
	 *      myData.msg = "This is a message! ";
	 *      myData.counter = 5;
	 * 
	 *      // Pass pointer to our data to the threadFunc 1st parameter
	 *      myThread.start(&myData);
	 *      std::cout << "Waiting for the thread to finish" << std::endl;
	 *      myThread.join();
	 *      std::cout << "Thread ended!" << std::endl;
	 * }
	 * ```
	 *
	 * This will print the following:
	 *
	 * ```
	 * Waiting for the read to finish
	 * This is a message! 0
	 * This is a message! 1
	 * This is a message! 2
	 * This is a message! 3
	 * This is a message! 4
	 * Thread ended!
	 * ```
     */
	class FFW_API thread{
	public:
		thread();
		thread(thread&& Other);
		virtual ~thread();
		/*!
         * @memberof thread
         * @ingroup Utilities
		 * @brief Starts the thread
		 * @return False if an error occured or there is no binded function
         */
		bool start(void* DataPtr);
		/*!
         * @memberof thread
         * @ingroup Utilities
		 * @brief Joins the function (blocking)
		 * @return False if an error occured
         */
		bool join();
		/*!
         * @memberof thread
         * @ingroup Utilities
		 * @brief Joins the function and gets the return value (blocking)
		 * @return False if an error occured
         */
		bool join(void** ReturnValue);
		/*!
         * @memberof thread
         * @ingroup Utilities
		 * @brief Binds a function
		 * @details Binds a static member/non-member function
         */
		void bindFunction(void* (*Func)(void*));
		/*!
         * @memberof thread
         * @ingroup Utilities
		 * @brief Binds a function
		 * @details Binds a non-static member function. An instance to the
		 * class is also needed. The Instance parameter must not be NULL.
         */
		template <class T> void bindFunction(void* (T::*MemFuncPtr)(void*), T* Instance){
			this->setFunction(std::bind(MemFuncPtr, Instance, std::placeholders::_1));
		}
		
		thread& operator = (thread&& Other);
		thread& operator = (const thread& Other) = delete;
		thread(const thread& Other) = delete;
	private:
		void setFunction(std::function<void*(void*)> Func);
		static void *internalThreadFunc(void* This);
		class impl;
		impl* pimpl;
	};
};

#endif
