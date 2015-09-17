/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_THREAD
#define FFW_THREAD

#include "../common.h"

namespace ffw{
	class FFW_API thread{
	public:
		thread();
		virtual ~thread();
		bool start(void* DataPtr);
		bool join();
		bool join(void** ReturnValue);
		void bindFunction(void* (*Func)(void*));
		template <class T> void bindFunction(void* (T::*MemFuncPtr)(void*), T* Instance){
			this->setFunction(std::bind(MemFuncPtr, Instance, std::placeholders::_1));
		}

	private:
		void setFunction(std::function<void*(void*)> Func);
		static void *internalThreadFunc(void* This);
		class impl;
		impl* pimpl;
	};
};

#endif
