/*
 * SemaphoreList.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "SemList.h"

SemList::SemList() {
	first=0;
	last=0;
	numberOfElem=0;
}
int SemList::getNumberOfElem(){
	return numberOfElem;
}

SemList::~SemList() {
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

void SemList::insert(KerSem *sem){
	//nemam lock i unlock
	numberOfElem++;
	Elem* newElem=new Elem(sem,last);

	if(first==0)first=newElem;
	else last->next=newElem;
	last=newElem;

}

void SemList::remove(KerSem *sem){
	//nemam lock i unlock

	if(first==0) return;

	Elem* tmp=first;

	while(tmp!=0 && tmp->kerSem!=sem){
		tmp=tmp->next;
	}

	if(tmp==0) return;

	numberOfElem--;

	if(tmp->prev!=0) tmp->prev->next = tmp->next;

	if(tmp->next!=0) tmp->next->prev = tmp->prev;

	if(tmp == first) first = first->next;

	if(tmp == last) last = last->prev;

	delete tmp;





}
