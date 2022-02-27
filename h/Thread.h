/*
 * Thread.h
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <dos.h>
#include<iostream.h>


#define lockI asm{ pushf; cli;}
#define unlockI asm popf;

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int TIME;
const TIME defaultTimeSlice = 2;
typedef int ID;

class PCB;

class Thread {




public:
	PCB *myPCB;

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);



	friend class PCB;
	Thread(StackSize stacksize=defaultStackSize,TIME timeSlice=defaultTimeSlice);
	virtual void run(){}

};

void dispatch();

#endif /* THREAD_H_ */
