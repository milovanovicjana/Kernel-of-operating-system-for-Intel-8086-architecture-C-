/*
 * Event.h
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KerEvent;


#define PREPAREENTRY(entryNo, callOld) \
	void interrupt intr##entryNo(...); \
	IVTEntry ivtEntry##entryNo(entryNo, intr##entryNo); \
	void interrupt intr##entryNo(...){\
		if(callOld==1){\
			ivtEntry##entryNo.callOldRoutine();\
		}\
		ivtEntry##entryNo.signal();\
		dispatch();\
}

class Event {

public:

	Event (IVTNo ivtNo);
	~Event ();
	void wait ();

protected:

	friend class KerEvent;
	void signal(); // can call KernelEv

private:

	KerEvent* myImpl;
};
#endif /* EVENT_H_ */
