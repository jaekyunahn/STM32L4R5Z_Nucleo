/*
 * fw.c
 *
 *  Created on: Jan 12, 2025
 *      Author: ajg10
 */
#include "mw.h"

void mwInit(void)
{
  fatfsInit();
  threadInit();
}
