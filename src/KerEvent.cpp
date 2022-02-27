/*
 * KerEvent.cpp
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#include "KerEvent.h"
#include "SCHEDULE.H"
#include "PCB.h"

KerEvent::KerEvent(IVTNo ivtNo) {
//objekat nad kojim se ceka prekid
	 value=0;
     this->ivtNo=ivtNo;
     owner=PCB::running;

     if(IVTEntry::IVTtable[ivtNo] == 0){
    	 //nista
     }
     else {
     		IVTEntry::IVTtable[ivtNo]->setEvent(this);

     }

}

KerEvent::~KerEvent() {
	signal();//odblokirati ako je trenutno blikirana
	if(IVTEntry::IVTtable[ivtNo]!=0){
		IVTEntry::IVTtable[ivtNo]->setEvent(0);
		//uklanjamo event
	}

}

void KerEvent::signal(){
	if(owner!=0){//mozda je visak

	if(value!=-1){//tada se nit jos uvek nije blokirala, a dogadjaj se sada desio
		value=1;
	}
	else{//ako je -1 tada se nit blokirala vec i ceka signal da je odblokira

		value=0;
		owner->currentState=PCB::READY;
		Scheduler::put(owner);
	}

	}
}
void KerEvent::wait(){
	if(owner!=0){
		if(PCB::running==owner){
			if(value==1){//desio se dogadjaj pre nego sto je nit usla u wait
				value=0;
			}
			else{//prvo u wait pa ceka na dogadjaj
				owner->currentState=PCB::BLOCKED;
				value=-1;
				dispatch();
			}
		}
	}
}


