#include <stdint.h>
#include <keyboard_driver.h>
void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 1:
			fetchKeyboardEvent();
			break;
	}
	return;
}

