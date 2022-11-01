#include <video.h>
#include <interrupts.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXECPTION_ID 6

static void zero_division();

static void invalid_opcode();

static void double_fault();

void exceptionDispatcher(int exception) {
	_cli();
	switch (exception)	{
	case ZERO_EXCEPTION_ID:
		zero_division();
		break;
	
	case INVALID_OPCODE_EXECPTION_ID:
		invalid_opcode();
		break;
	case DOUBLE_FAULT_EXCEPTION_ID:
		double_fault();
		break;	
	}
	_sti();
}

static void zero_division() {
	printString("\n");
	printString("Zero division exception\n");
}

static void invalid_opcode() {
	printString("\n");
	printString("Invalid opcode exception\n");
}
static void double_fault(){
	printString("\n");
	printString("Double Fault exception\nThis shouldn't happen but div zero exception suddenly stopped working :(\n");
}
