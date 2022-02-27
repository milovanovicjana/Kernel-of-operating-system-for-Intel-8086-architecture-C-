/*
 * SemaphoreQueque.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "SQueque.h"

SQueque::SQueque() {
	first=0;
	last=0;
	numberOfElem=0;

}

SQueque::~SQueque() {
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

void SQueque::insert(Elem* tmp){

	    numberOfElem++;
		if(first==0)first=tmp;
		else last->next=tmp;
		last=tmp;


}

SQueque::Elem* SQueque::getFirst(){

	if(first==0)return 0;

	Elem *tmp=first;

	if(numberOfElem==1){
		first=0;
		last=0;
	}
	else{
		first=first->next;
		tmp->next=0;
	}
	numberOfElem--;
	return tmp;


}

void SQueque::remove(Elem* tmp){

	if(first==0) return;

	Elem* prev=0;
	Elem* t=first;

	while(t!=0 && t!=tmp){
			prev=t;
			t=t->next;
	}

	if(t==0) return;


	numberOfElem--;

	if(prev==0) first=first->next;
	else prev->next=t->next;

	if(t->next==0){
		last=prev;
		if(last!=0)last->next=0;
	}





}
int SQueque::getNumberOfElem(){
	return numberOfElem;
}
