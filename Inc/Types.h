#ifndef __TYPES_H__
#define __TYPES_H__

#define NULL_PTR (void*)0

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

typedef signed char        sint8;
typedef signed short       sint16;
typedef signed long        sint32;
typedef signed long long   sint64;

typedef unsigned char      boolean;

typedef void (*pMemberDecode)(uint64 inst, uint64 mask);

typedef struct
{
 const uint64        member_mask;
 const uint64        member_type;
 const uint8 * const print;
 const pMemberDecode member_search;
}insmem;

typedef struct
{
  const uint64        opcode;
  const uint64        mask;
  const uint8 * const name;
  const uint8 * const print;
  const uint8         length;
  const uint8         param_nbr;
  const insmem        member[10];
}tinstruction;

#endif // __TYPES_H__
