#include <naiveConsole.h>
#include <interrupts.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_EXECPTION_ID 6

static void zero_division();

static void invalid_opcode();

void exceptionDispatcher(int exception) {
	_cli();
	switch (exception)	{
	case ZERO_EXCEPTION_ID:
		zero_division();
		break;
	
	case INVALID_OPCODE_EXECPTION_ID:
		invalid_opcode();
		break;
	}
	_sti();
}

static void zero_division() { //MDOIFICAR PARA MODO VIDEO 
	ncPrint("no dividas por cero bola ");
	while (1)	{}  
	//llama a shell
	
}

static void invalid_opcode() {
	ncPrint("invalid opcode");
	while (1)	{} 
}
