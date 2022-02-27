/*
 * PCB.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include <dos.h>
Thread* PCB::idleThread=0;
Thread* PCB::mainThread=0;
ID PCB::broj=0;
PCBList* PCB::ListOfPCB=new PCBList();
PCB* PCB::running=0;

PCB::~PCB(){

	delete stack;
	ListOfPCB->getAndRemoveById(id);

}

PCB::PCB(Thread* t,StackSize s,TIME time){

	//inicijalizacija steka
	if(s>65536) stackSize=65536/sizeof(unsigned);
	else{
		stackSize=s/sizeof(unsigned);
	}


    stack=new unsigned int[stackSize];

    /*
     *segmenti i
     *ofsetni registar cine
     *pc!
     * */

    stack[stackSize-1]=0x200;

#ifndef BCC_BLOCK_IGNORE
    stack[stackSize-2]=FP_SEG(&wrapper);
    stack[stackSize-3]=FP_OFF(&wrapper);
#endif

#ifndef BCC_BLOCK_IGNORE
    ss=FP_SEG(stack+stackSize-12);
    sp=FP_OFF(stack+stackSize-12);
#endif

    bp=sp;

	id=++broj;
	timeSlice=time;
	thread=t;
	currentState=INITIAL;
	waitingPCB=new PCBList();
	ListOfPCB->insertFirst(this);//napraviti u klasi lista

	//za semafore

	retVal=0;

}



void PCB::start(){
	if(currentState!=INITIAL) return;
	else {
		currentState=READY;
		Scheduler::put(this);
	}

}

void PCB::finish(){

	lockFlag=0;


#ifndef BCC_BLOCK_IGNORE
	lockI
#endif

	while(this->waitingPCB->first){
		PCB *tmp=waitingPCB->removeFirst();
		tmp->currentState=READY;
		Scheduler::put(tmp);
	}


	delete waitingPCB;
	waitingPCB=0;
	currentState=FINISHED;




#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif


	lockFlag=1;
	dispatch();


}

void PCB::waitToComplete(){

	if(currentState==FINISHED || currentState==INITIAL || thread==idleThread || this==PCB::running)return;

	else{
		PCB::running->currentState=BLOCKED;
		waitingPCB->insertLast(PCB::running);
		dispatch();
	}
}

void PCB::wrapper(){
	PCB::running->thread->run();
	PCB::running->finish();
}

Thread* PCB::getThread(){
	return thread;

}

ID PCB::getId(){
	return id;
}







