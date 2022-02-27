/*
 * KernelSem.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "KerSem.h"
#include "PCB.h"

//pravi se lista svih semafora
SemList KerSem::allSemaphores;

KerSem::KerSem(int init) {
	//blockedQueque=new SQueque();
	value=init;
	allSemaphores.insert(this);

}

KerSem::~KerSem() {

	while(value<0){

		signal();
	}

	allSemaphores.remove(this);
}


void KerSem::block(Time maxTimeToWait){

	int tmp;
	if(maxTimeToWait>0) tmp=1;
	else tmp=0;
	SQueque::Elem *el=new SQueque::Elem(PCB::running,maxTimeToWait,tmp);
	blockedQueque.insert(el);
	PCB::running->currentState=PCB::BLOCKED;

	dispatch();

}

void KerSem::deblock(){

	SQueque::Elem *el=blockedQueque.getFirst();
	el->pcb->currentState=PCB::READY;
	Scheduler::put(el->pcb);

	//proveriti
	el->pcb->retVal=1;


}

int KerSem::wait(Time maxTimeToWait){
	if(--value<0){
		block(maxTimeToWait);
		//DA LI OOVO TREBA DOLE?
		return PCB::running->retVal;
	}

	return 1;



}


void KerSem::signal(){

	if(value++<0){
		deblock();
	}

}

int KerSem::val()const{
	return value;
}

void KerSem::SemaphoreTick(){
	for(SemList::Elem* sem=allSemaphores.first;sem!=0;sem=sem->next){
		for(SQueque::Elem* sem2=sem->kerSem->blockedQueque.first;sem2!=0;sem2=sem2->next){

			if(sem2->timeToWait>0){
				sem2->timeToWait--;

			}

			if(sem2->waitOrNo=1 && sem2->timeToWait==0){//ako je odbrojao do nule i ako ne ceka neograniceno!


				sem->kerSem->value++;
				sem->kerSem->blockedQueque.remove(sem2);

				sem2->pcb->currentState=PCB::READY;
				sem2->pcb->retVal=0;
				Scheduler::put(sem2->pcb);


			}

		}

	}
}
