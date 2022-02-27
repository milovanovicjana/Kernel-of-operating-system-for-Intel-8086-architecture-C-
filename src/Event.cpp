/*
 * Event.cpp
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#include "Event.h"
#include "Thread.h"
#include "KerEvent.h"

Event::Event(IVTNo ivtNo) {
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif

	myImpl=new KerEvent(ivtNo);
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif

}
void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	if(myImpl)myImpl->wait();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}
void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	if(myImpl)myImpl->signal();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}

Event::~Event() {
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif

	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}

