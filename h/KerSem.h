/*
 * KernelSem.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "SQueque.h"
#include "SemList.h"


typedef unsigned int Time;

class KerSem {

	int value;
	SQueque blockedQueque;

public:


	KerSem(int init);//konstruktor

	int wait (Time maxTimeToWait);
	void signal();

	int val()const;

	static SemList allSemaphores;


	static void SemaphoreTick();

	void block(Time maxTimeToWait);
	void deblock();

	 ~KerSem();
};

#endif /* KERSEM_H_ */
