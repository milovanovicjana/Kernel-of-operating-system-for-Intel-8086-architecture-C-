/*
 * PCBList.h
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

#include "PCB.h"

class PCB;

typedef int ID;

class PCBList {
public:
	int numberOfElem;

	struct Elem{
		Elem* next;
		PCB * pcb;
		Elem(PCB *p=0,Elem*n=0){
			pcb=p;
			next=n;
		}
	};

	Elem *first,*last;

	PCBList(){
		numberOfElem=0;
	    first=last=0;
	}


	int getNumberOfElem();

    void insertFirst(PCB*p);
    void insertLast(PCB*p);

    PCB* getById(ID id);
    PCB* getAndRemoveById(ID id);

    PCB* removeLast();
    PCB* removeFirst();

    ~PCBList();



};

#endif /* PCBLIST_H_ */
