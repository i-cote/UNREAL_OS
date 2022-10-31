#include <stdint.h>
extern uint8_t * stackAddrAfterPushState;

static uint64_t saved_registors[16];

void save_registors()
{
	memcpy(saved_registors,stackAddrAfterPushState,16*sizeof(uint64_t));
}

void fetch_saved_registors(uint64_t * dest,int length)
{
	memcpy(dest,saved_registors,length);
}
