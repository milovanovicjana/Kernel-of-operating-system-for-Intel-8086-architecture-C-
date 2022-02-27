/*
 * PCB.h
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "SCHEDULE.h"
#include "Thread.h"
#include "PCBList.h"


extern volatile int lockFlag;
class PCBList;


class PCB {


public:

	PCB(Thread*,StackSize,TIME);//konstruktor

	enum State {INITIAL,READY,BLOCKED,FINISHED};
	State currentState;
	static PCB *running;//trenutni proces koji se izvrsava
	static ID broj;
	ID id;//id procesa

	unsigned int* stack;
	unsigned int sp,ss,bp;

	Thread* thread;
	static Thread* idleThread;
	static Thread* mainThread;

	TIME timeSlice;

	StackSize stackSize;
	static PCBList *ListOfPCB;
	PCBList *waitingPCB;

	//za semafore

	int retVal;


	void start();
	void finish();
	void waitToComplete();
	static void wrapper();

	ID getId();
	Thread* getThread();

	~PCB();


};

#endif
