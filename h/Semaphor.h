/*
 * Sempahore.h
 *
 *  Created on: May 17, 2021
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

typedef unsigned int Time;

class KerSem;

class Semaphor {

private:

	KerSem* myImpl;

public:

	Semaphor (int init=1);
	virtual ~Semaphor ();
	virtual int wait (Time maxTimeToWait);
	virtual void signal();

	int val () const; // Returns the current value of the semaphore

};

#endif /* SEMAPHOR_H_ */
