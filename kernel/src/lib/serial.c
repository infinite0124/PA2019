#include "common.h"
#include "x86.h"

#define SERIAL_PORT 0x3F8

void init_serial(void) {}

static inline int
serial_idle(void)
{
	return (in_byte(SERIAL_PORT + 5) & 0x20) != 0;
}

void serial_printc(char ch)
{
	//Log("%x ",ch);
	while (!serial_idle())
		; // wait untile serial is idle
//	BREAK_POINT
	out_byte(0x3f8,ch);
	// print 'ch' via out instruction here
	//HIT_BAD_TRAP;
}
