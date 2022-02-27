/*
 * IVTEntry.h
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*interruptPointer)(...);
typedef unsigned char IVTNo;
class KerEvent;

class IVTEntry {
private:
	interruptPointer myOldRoutine;
	IVTNo myEntry;
	KerEvent *myEvent;
public:
	friend class KerEvent;
	IVTEntry(IVTNo entry,interruptPointer newRoutine);

	 ~IVTEntry();
	 static IVTEntry* IVTtable[256];
	 static IVTEntry* getIVTEntry(IVTNo num);
	 void setEvent(KerEvent* ev);
	 void callOldRoutine();
	 void signal();


};

#endif /* IVTENTRY_H_ */
