#ifndef __RH850_INS_MACRO_H__
#define __RH850_INS_MACRO_H__

#include<Types.h>

#define REG     0
#define IMM     1
#define DISP    2
#define CCCC    3
#define NOTHING 4

#define PRINT_REG      "%s,"
#define PRINT_REG_END  "%s\n"

#define PRINT_REG_ADD      "[%s],"
#define PRINT_REG_ADD_END  "[%s]\n"

#define PRINT_INS      "%s "
#define PRINT_INS_END  "%s\n"
#define PRINT_INS_1    "%s"

#define PRINT_IMM         "0x%x,"
#define PRINT_SIG_IMM     "%d,"
#define PRINT_SIG_IMM_END " %d\n"
#define PRINT_SIG_H_IMM   "-0x%x,"
#define PRINT_IMM_END     "0x%x\n"

#define PRINT_CCCC      "%s,"
#define PRINT_CCCC_1    "%s"

#define PRINT_DISP         " 0x%x"
#define PRINT_DISP_END     " 0x%x\n"
#define PRINT_SIG_DISP_END " %x\n"

#define ADD_1_OPCODE 0x01C0ULL
#define ADD_2_OPCODE 0x0240ULL
#define ADD_MASK     0x07E0ULL

#define ADDI_OPCODE  0x06000000ULL
#define ADDI_MASK    0x07E00000ULL

#define ADF_OPCODE   0x07E003A0ULL
#define ADF_MASK     0x07E007E0ULL

#define AND_OPCODE   0x0140ULL
#define AND_MASK     0x07E0ULL

#define ANDI_OPCODE  0x06C00000ULL
#define ANDI_MASK    0x07E00000ULL

#define B_1_OPCODE   0x0580ULL
#define B_1_MASK     0x0F80ULL

#define B_2_OPCODE   0x07E00001ULL
#define B_2_MASK     0xFFE00001ULL

#define BINS_1_OPCODE  0x07E00090ULL
#define BINS_2_OPCODE  0x07E000B0ULL
#define BINS_3_OPCODE  0x07E000D0ULL
#define BINS_MASK      0x07E007F1ULL

#define BSH_OPCODE     0x07E00342ULL
#define BSH_MASK       0x07FF07FFULL

#define BSW_OPCODE     0x07E00340ULL
#define BSW_MASK       0x07FF07FFULL

#define CALLT_OPCODE   0x0200ULL
#define CALLT_MASK     0xFFC0ULL

#define CAXI_OPCODE    0x07E000EEULL
#define CAXI_MASK      0x07E007FFULL

#define CLL_OPCODE     0xFFFFF160ULL
#define CLL_MASK       0xFFFFFFFFULL

#define CLR1_1_OPCODE  0x87C00000ULL
#define CLR1_1_MASK    0xC7E00000ULL

#define CLR1_2_OPCODE  0x07E000E4ULL
#define CLR1_2_MASK    0x07E0FFFFULL

#define JMP_1_OPCODE 0x0060ULL
#define JMP_1_MASK   0xFFE0ULL

#define NOP_OPCODE   0x0000ULL
#define NOP_MASK     0xFFFFULL

#define JR_1_OPCODE 0x07800000ULL
#define JR_1_MASK   0xFFC00001ULL

#define JR_2_OPCODE 0x07800000ULL
#define JR_2_MASK   0xFFC00001ULL

#define RH850_INSTRUCTIONS_DEFINITIONS  static const tinstruction instructionsList[] ={
#define RH850_INST_BEGIN {
#define RH850_INST_OPCODE_DEF(opcode,mask,name,print,length,param_nbr) opcode,mask,name,print,length,param_nbr,{
#define RH850_INST_OPERAND_DEF(mask,type,print,search) {mask,type,print,search},
#define RH850_INST_END }},
#define RH850_INSTRUCTIONS_END    };

//R      1-bit data of code specifying reg1 or regID
//r      1-bit data of code specifying reg2
//w      1-bit data of code specifying reg3
//D      1-bit data of displacement (indicates higher bits of displacement)
//d      1-bit data of displacement
//I      1-bit data of immediate (indicates higher bits of immediate)
//i      1-bit data of immediate
//V      1-bit data of code specifying vector (indicates higher bits of vector)
//v      1-bit data of code specifying vector
//cccc   4-bit data for condition code specification (See Table 7.4 Condition Codes)
//bbb    3-bit data for bit number specification
//L      1-bit data of code specifying general-purpose register in register list
//S      1-bit data of code specifying EIPC/FEPC, EIPSW/FEPSW in register list
//P      1-bit data of code specifying PSW in register list

static uint8 const * const RegName[32]  = { "r0",
                                            "r1",
                                            "r2",
                                            "r3",
                                            "r4",
                                            "r5",
                                            "r6",
                                            "r7",
                                            "r8",
                                            "r9",
                                            "r10",
                                            "r11",
                                            "r12",
                                            "r13",
                                            "r14",
                                            "r15",
                                            "r16",
                                            "r17",
                                            "r18",
                                            "r19",
                                            "r20",
                                            "r21",
                                            "r22",
                                            "r23",
                                            "r24",
                                            "r25",
                                            "r26",
                                            "r27",
                                            "r28",
                                            "r29",
                                            "r30",
                                            "r31"
                                          };

static uint8 const * const ConditionCodeName[16] = { "V",
                                                     "C",
                                                     "Z",
                                                     "NH",
                                                     "S",
                                                     "T",
                                                     "LT",
                                                     "LE",
                                                     "NV",
                                                     "NC",
                                                     "NZ",
                                                     "H",
                                                     "NS",
                                                     "SA",
                                                     "GE",
                                                     "GT",
                                                   };

#endif // __RH850_INS_MACRO_H__
