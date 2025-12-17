/************************************************************************/
/**
* @LC	  10/17/2016
* @file   soThread.h
* @Author Alejandro Rodriguez (alejandro.rodriguez92@gmail.com)
* @date   10/17/2016
* @brief  Declaration Standardheader
* @bug	  No know Bugs
*/
/************************************************************************/

#pragma once
#include "soStandardTools.h"

#ifdef SO_FOUR_THREADS
#define SO_THREAD_NUMBER 4
#elif SO_EIGTH_THREADS
#define SO_THREAD_NUMBER 8
#else
#define SO_THREAD_NUMBER 1
#endif // !SO_FOUR_THREADS || SO_EIGTH_THREADS

#define SO_LOCKTHREAD(_name)	omp_lock_t _name; 
#define SO_INIT_LOCK(_name)		omp_init_lock(&_name);
#define SO_SET_LOCK(_name)		omp_set_lock(&_name);
#define SO_UNSET_LOCK(_name)	omp_unset_lock(&_name);
#define SO_DESTROY_LOCK(_name)	omp_destroy_lock(&_name);

namespace SoulSDK
{
	/*void StartUpThreads()
	{
		omp_set_num_threads(SO_THREAD_NUMBER);
	}*/
}