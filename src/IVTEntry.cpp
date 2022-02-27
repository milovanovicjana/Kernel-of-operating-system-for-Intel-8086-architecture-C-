/*
 * IVTEntry.cpp
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <dos.h>
#include "KerEvent.h"
#include "Thread.h"
IVTEntry* IVTEntry::IVTtable[256]={0};

IVTEntry::IVTEntry(IVTNo entry,interruptPointer newRoutine) {
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	myEvent=0;
	myEntry=entry;
	IVTtable[myEntry]=this;
#ifndef BCC_BLOCK_IGNORE
	myOldRoutine=getvect(entry);
	setvect(entry,newRoutine);
	unlockI
#endif

}

IVTEntry::~IVTEntry() {
#ifndef BCC_BLOCK_IGNORE
	lockI
	setvect(myEntry, myOldRoutine);
#endif
	IVTtable[myEntry] = 0;
	myEvent = 0;
	callOldRoutine();
#ifndef BCC_BLOCK_IGNORE
	unlockI
	#endif


}

IVTEntry *IVTEntry::getIVTEntry(IVTNo num){
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	IVTEntry *en = IVTtable[num];
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
	return en;
}

void IVTEntry::setEvent(KerEvent *ev){

#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	this->myEvent = ev;
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}


void IVTEntry::signal(){


#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	if (myEvent!=0)myEvent->signal();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}


void IVTEntry::callOldRoutine(){


#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	if (myOldRoutine!=0)myOldRoutine();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}
