#ifndef __RH850_INS_PROTO_H__
#define __RH850_INS_PROTO_H__

#include<RH850_Decode.h>
#include<OutputCfg.h>


void Inst_BinsMsbDecode(uint64 inst, uint64 mask);
void Inst_BinsLsbDecode(uint64 inst, uint64 mask);
void Inst_AddImmDecode(uint64 inst, uint64 mask);
void Inst_Imm16Decode(uint64 inst, uint64 mask);
void Inst_Imm9Decode(uint64 inst, uint64 mask);
void Inst_Imm17Decode(uint64 inst, uint64 mask);
void Inst_Disp9Decode(uint64 inst, uint64 mask);
void Inst_Disp17Decode(uint64 inst, uint64 mask);
void Inst_Disp22Decode(uint64 inst, uint64 mask);
void Inst_Disp32Decode(uint64 inst, uint64 mask);

#endif // __RH850_INS_PROTO_H__
