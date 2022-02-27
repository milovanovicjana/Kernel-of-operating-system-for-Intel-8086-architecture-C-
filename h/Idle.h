/*
 * Idle.h
 *
 *  Created on: May 2, 2021
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include "Thread.h"

class Idle:public Thread {
public:
	Idle():Thread(){}
	void run(){

		while(1){
			/*
			 * idle nit se beskonacno izvrsava!!
			 * */
		}
	}
};



#endif /* IDLE_H_ */
