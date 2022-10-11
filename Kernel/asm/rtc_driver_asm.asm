GLOBAL _startClock
GLOBAL _stopClock

GLOBAL _getCurrentHours
GLOBAL _getCurrentMinutes
GLOBAL _getCurrentSeconds
GLOBAL _getCurrentSeconds

GLOBAL _setHours
GLOBAL _setMinutes
GLOBAL _setSeconds

section .text

_startClock:
	mov al,0xb
	out 0x70, al
	mov al,0
	out 0x71, al
	ret

_stopClock:
	mov al,0xb
	out 0x70, al
	mov al,128
	out 0x71, al
	ret


_getCurrentHours:
	mov al, 4
	out 0x70, al
	in ax, 0x71
	ret
_getCurrentMinutes:
	mov al, 2
	out 0x70, al
	in ax, 0x71
	ret
_getCurrentSeconds:
	mov al, 0
	out 0x70, al
	in ax, 0x71
	ret


_setHours:
	mov al, 4
	out 0x70, al
	mov al,12
	out 0x71, al
	ret
_setMinutes:
	mov al, 2
	out 0x70, al
	mov al,33
	out 0x71, al
	ret
_setSeconds:
	mov al, 0
	out 0x70, al
	mov al,25
	out 0x71, al
	ret
