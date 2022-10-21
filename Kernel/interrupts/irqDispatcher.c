#include <stdint.h>
#include <keyboard_driver.h>
void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			timer_handler();
			break;
		case 1:
			fetchKeyboardEvent();
			break;
	}
	return;
}

