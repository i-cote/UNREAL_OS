#ifndef  REGISTORS_SNAPSHOT_H
#define  REGISTORS_SNAPSHOT_H
#include <stdint.h>
void save_registors();
void fetch_saved_registors(uint64_t * dest,int length);
#endif
