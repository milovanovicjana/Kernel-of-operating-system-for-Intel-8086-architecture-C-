
#include <iostream.h>

#include <dos.h>
#include "Idle.h"
#include "PCB.h"
#include "KerSem.h"

extern volatile unsigned tss = 0, tsp = 0, tbp = 0;
extern volatile int lockFlag = 1;
extern volatile unsigned timerCnt = 2;
extern volatile int context_switch = 0;



void tick();
void inic();
void  restore();

int userMain(int argc, char* argv[]);

unsigned oldTimerOFF, oldTimerSEG;


#define lockCout lockFlag=0;
#define unlockCout lockFlag=1;\
		if(context_switch==1){\
			dispatch();\
}





void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}




void dispatch() {

	//ekspilicitna
	//promena konteksta!!!s

#ifndef BCC_BLOCK_IGNORE
lockI
#endif
      context_switch = 1;

#ifndef BCC_BLOCK_IGNORE
	asm int 8h;
#endif
#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif
}

void interrupt timer(){

	if (context_switch==0) {
				if (timerCnt > 0) timerCnt--;
				tick();

				KerSem::SemaphoreTick();

	}
	//if (PCB::running && ((timerCnt == 0 || context_switch) && (PCB::running->timeSlice!=0 || (PCB::running->timeSlice==0 && PCB::running->currentState==PCB::FINISHED) ))  ) {
	if (PCB::running && (timerCnt == 0 || context_switch)){

		if(!lockFlag){

						context_switch = 1;

		}
		else{


#ifndef BCC_BLOCK_IGNORE

			asm {

				mov tsp, sp
				mov tss, ss
				mov tbp, bp

			}
#endif

			context_switch = 0;

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			if (PCB::running->currentState == PCB::READY ) {
				if(PCB::running == PCB::idleThread->myPCB) {
					//tada ne radimo nista, idle ne ubacujemo!
				}
				else {//u ostalim slucajevima, uvek ubaci
					Scheduler::put(PCB::running);
				}
			}

			PCB::running = Scheduler::get();

			if (!PCB::running) {
				PCB::running = PCB::idleThread->myPCB;

			}

     		tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			timerCnt = PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif

		}

	}

	if(context_switch==0){
#ifndef BCC_BLOCK_IGNORE

			asm int 60h;
#endif
	}

}


void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void runMainAndIdle(){

	PCB::running= PCB::mainThread->myPCB;
	PCB::running->currentState = PCB::READY;

	PCB::idleThread = new Idle();
	PCB::idleThread->start();

	Scheduler::get();
	PCB::idleThread->myPCB->currentState = PCB::READY;

	//idle izbaci iz schedulera!!!
}

int main(int argc, char* argv[]){


#ifndef BCC_BLOCK_IGNORE
	lockI
#endif
	inic();

	PCB::mainThread = new Thread(defaultStackSize, 2);


#ifndef BCC_BLOCK_IGNORE
	asm cli
#endif

	runMainAndIdle();

#ifndef BCC_BLOCK_IGNORE
	unlockI
#endif


	int ret=userMain(argc,argv);

	restore();

	return ret;



}
