/*
 * SemaphoreQueque.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef SQUEQUE_H_
#define SQUEQUE_H_

#include "PCB.h"
typedef unsigned int Time;

class PCB;
class KernelSem;

class SQueque {

public:

	int numberOfElem;

	struct Elem{
		Elem *next;
		PCB *pcb;
		Time timeToWait;
		int waitOrNo;

		Elem(PCB*p,Time t,int wait,Elem *n=0){
			pcb=p;
			timeToWait=t;
			waitOrNo=wait;
			next=n;
		}
	};

	Elem *first,*last;



	SQueque();

	int getNumberOfElem();

    void insert(Elem* tmp);
    void remove(Elem* tmp);

    Elem* getFirst();//uzima najranije ubacen iz reda



    ~SQueque();
};

#endif /* SQUEQUE_H_ */
