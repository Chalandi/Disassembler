#ifndef __RH850_DECODE_H__
#define __RH850_DECODE_H__

#include"Types.h"

//=============================================================================
// prototypes
//=============================================================================
uint8 FetchAndDecode(uint8 const* pdata);
uint64 DecodeOperand(uint64 instruction, uint64 mask);

#endif // __RH850_DECODE_H__
