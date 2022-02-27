/*
 * KerEvent.h
 *
 *  Created on: May 26, 2021
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_
#include "IVTEntry.h"

class PCB;


class KerEvent {
private:
	PCB* owner;
	IVTNo ivtNo;
	int value;
public:
	KerEvent(IVTNo ivtNo);

	void wait();
	void signal();

	~KerEvent();

};

#endif /* KEREVENT_H_ */
