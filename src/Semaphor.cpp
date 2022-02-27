/*
 * Sempahore.cpp
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include "KerSem.h"
#include "Semaphor.h"
#include "Thread.h"

Semaphor::Semaphor(int init) {

#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	myImpl= new KerSem(init);


#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif


}
int Semaphor::wait(Time maxTimeToWait) {

#ifndef BCC_BLOCK_IGNORE
	lockI

#endif
	int retVal=0;
	retVal = myImpl->wait(maxTimeToWait);

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
	return retVal;

}

void Semaphor::signal() {


#ifndef BCC_BLOCK_IGNORE
	lockI
#endif

	 myImpl->signal();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif

}


int Semaphor::val() const {

#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	int retVal=0;
	retVal = myImpl->val();
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
	return retVal;

}

Semaphor::~Semaphor() {
#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif

}










