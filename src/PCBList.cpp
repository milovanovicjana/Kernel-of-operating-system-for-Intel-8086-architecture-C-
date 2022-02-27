/*
 * PCBList.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: OS1
 */

#include "PCBList.h"
#include "PCB.h"




PCBList::~PCBList() {
	Elem *tmp=first;
	Elem*old=0;
	while(tmp!=0){
		old=tmp;
		tmp=tmp->next;
		delete old;
	}
	first=last=0;
	numberOfElem=0;
}

int PCBList:: getNumberOfElem(){
	return numberOfElem;
}

void PCBList::insertLast(PCB*p){
	Elem* newElem=new Elem(p);
	numberOfElem++;
	if(first==0)first=newElem;
	else last->next=newElem;
	last=newElem;

}

void PCBList::insertFirst(PCB*p){

	Elem* newElem=new Elem(p);
	numberOfElem++;
	if(first==0){
		last=newElem;
	}
	else{
	newElem->next=first;
	}
	first=newElem;

}

PCB* PCBList:: getById(ID id){

	Elem *tmp=first;
	while(tmp!=0){
		if(tmp->pcb->getId()==id){
			return tmp->pcb;
		}
		tmp=tmp->next;
	}
	return 0;
}


PCB* PCBList:: getAndRemoveById(ID id){

	Elem *tmp=first;
	Elem *prev=0;
	PCB *p=0;
	while(tmp!=0){
		if(tmp->pcb->getId()==id){
			break;
		}
		tmp=tmp->next;
	}
	if(tmp==0)return 0;
	//ako je prvi u listi
	if(prev==0){
		p=tmp->pcb;
		numberOfElem--;
		first=first->next;
		if(first==0)last=0;
		tmp->next=0;

	}
	else{
		prev->next=tmp->next;
		if(tmp->next==0){
			last=prev;
			p=tmp->pcb;
			numberOfElem--;
		}
	}

	delete tmp;
	return p;
}


PCB* PCBList:: removeLast(){

	if(first==0)return 0;
	PCB* p=0;
	Elem *prev=0;
	Elem *tmp=first;
	while(tmp->next!=0){
		prev=tmp;
		tmp=tmp->next;
	}
	p=tmp->pcb;
	delete tmp;
	if(prev!=0){
		last=prev;
		prev->next=0;
	}
	else{
		last=first=0;
	}
	numberOfElem--;
	return p;

}

PCB* PCBList:: removeFirst(){

	if(first==0)return 0;
	PCB* p=0;
	Elem *tmp=first;
	if(numberOfElem==1){
		p=tmp->pcb;
		delete tmp;
		first=0;
		last=0;
	}
	else{
		first=first->next;
		p=tmp->pcb;
		tmp->next=0;
		delete tmp;
	}
	numberOfElem--;
	return p;


}


