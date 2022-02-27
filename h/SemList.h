/*
 * SemaphoreList.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_


class KerSem;
class SemList {

public:

	int numberOfElem;

	struct Elem{
		KerSem *kerSem;
		Elem *next,*prev;
		Elem(KerSem *ks,Elem *p=0,Elem *n=0){
			kerSem=ks;
			next=n;
			prev=p;
		}
	};

	Elem *first,*last;

	SemList();

	int getNumberOfElem();

	void insert(KerSem* sem);
	void remove(KerSem* sem);


	 ~SemList();
};

#endif /* SEMLIST_H_ */
