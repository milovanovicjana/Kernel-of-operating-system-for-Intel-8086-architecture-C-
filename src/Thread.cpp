/*
 * Thread.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#include "Thread.h"
#include "pcb.h"

Thread::Thread(StackSize stacksize,TIME timeSlice) {

#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
		myPCB = new PCB(this, stacksize, timeSlice);


#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif

}

Thread::~Thread() {

#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
		waitToComplete();
		delete myPCB;
		myPCB=0;


#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif


}

void Thread::start(){

#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
		myPCB->start();


#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif

}

void Thread::waitToComplete(){

#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
		myPCB->waitToComplete();


#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif


}

ID Thread::getId(){
#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
	  ID id=myPCB->getId();

#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif
	return id;
}

ID Thread::getRunningId(){


#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
	ID id=PCB::running->getId();


#ifndef BCC_BLOCK_IGNORE
		unlockI

	#endif

		return id;

}

Thread* Thread::getThreadById(ID id){

#ifndef BCC_BLOCK_IGNORE
		lockI

#endif
		Thread* t=0;
		PCB *p=PCB::ListOfPCB->getById(id);
		if(p!=0){
			t=p->getThread();
		}

#ifndef BCC_BLOCK_IGNORE
		unlockI

#endif
		return t;

}



