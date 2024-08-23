/*
 * cpu_specifications_utilities.c
 *
 *  Created on: Aug 23, 2024
 *      Author: k-abe
 */
#include <stdbool.h>  // bool

bool is_little_endian(void)
{
	int x = 1;   // 0x00000001

	if( *(char *)&x ){
	     // little endian. memory image 01 00 00 00
		return true;
	} else {
	     // big endian. memory image 00 00 00 01
		return false;
	}
}
