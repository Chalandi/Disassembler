#include<RH850_InsDef.h>
#include<RH850_InsProto.h>
#include<OutputCfg.h>

//=============================================================================
// prototypes
//=============================================================================
static uint64 InstructionFetch16(uint16 const * const pInstruction);
static uint64 InstructionFetch32(uint16 const * const pInstruction);
static uint64 InstructionFetch48(uint16 const * const pInstruction);
static uint64 InstructionFetch64(uint16 const * const pInstruction);
static boolean DecodeInstruction(const uint64 instruction, const uint8 instructionsize);

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pInstruction 
///
/// \return uint64 
//-----------------------------------------------------------------------------
static uint64 InstructionFetch16(uint16 const * const pInstruction)
{
  return((uint64)*pInstruction);
}
//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pInstruction 
///
/// \return uint64 
//-----------------------------------------------------------------------------
static uint64 InstructionFetch32(uint16 const * const pInstruction)
{
  uint64 data = (uint32)(pInstruction[0]<<16 | pInstruction[1]);
  return(data);
}
//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pInstruction 
///
/// \return uint64 
//-----------------------------------------------------------------------------
static uint64 InstructionFetch48(uint16 const * const pInstruction)
{
  uint64 data = (uint64)(((uint64)(pInstruction[0])<<32) | ((uint64)(pInstruction[1])<<16) | pInstruction[2]);
  return(data);
}
//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pInstruction 
///
/// \return uint64 
//-----------------------------------------------------------------------------
static uint64 InstructionFetch64(uint16 const * const pInstruction)
{
  uint64 data = (uint64)(((uint64)(pInstruction[0])<<48) | ((uint64)(pInstruction[1])<<32) | ((uint64)(pInstruction[2])<<16) | pInstruction[3]);
  return(data);
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  instruction 
/// \param  mask 
///
/// \return uint16 
//-----------------------------------------------------------------------------
uint64 DecodeOperand(uint64 instruction, uint64 mask)
{
  uint64 byte = 0;
  uint64  bit  = 0;
  uint8  pos  = 0;

  for(uint32 i=0U; i < 64U; i++)
  {
    if(mask & ((uint64)1<<i))
    {
      bit = (instruction & ((uint64)1<<i)) ? 1 : 0;
      byte |= (bit << pos);
      pos++;
    }
  }

  return(byte);
}
//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  instruction 
///
/// \return boolean 
//-----------------------------------------------------------------------------
static boolean DecodeInstruction(const uint64 instruction, const uint8 instructionsize)
{
  boolean boInstructionfound = 0;
  uint64 operand;

  for(int i=0; (i < (sizeof(instructionsList)/sizeof(tinstruction)) && !boInstructionfound);i++)
  {
    /* search for instruction in the table */
    if(((uint8)instructionsize == (uint8)instructionsList[i].length)  && ((uint64)(instruction) & (uint64)(instructionsList[i].mask)) == (uint64)(instructionsList[i].opcode))
    {
      /* instruction is found */
      boInstructionfound = 1;

      /* print the instruction name */
      OUTPUT(instructionsList[i].print,instructionsList[i].name);

      /* search for the operands */
      for(int j=0; j < instructionsList[i].param_nbr;j++)
      {

        /* check if the operand needs a special treatment (math, shift...) */
        if(instructionsList[i].member[j].member_search != NULL_PTR)
        {
          /* call the appropriate service to decode and print the operand */
          instructionsList[i].member[j].member_search((uint64)instruction,(uint64)(instructionsList[i].member[j].member_mask));
        }
        else
        {
          /* decode the operand without any special treatment */
          operand = DecodeOperand((uint64)instruction,(uint64)(instructionsList[i].member[j].member_mask));

          /* print the operand */
          switch(instructionsList[i].member[j].member_type)
          {
            case REG:  OUTPUT((instructionsList[i].member[j].print),RegName[operand]); break;
            case IMM:  OUTPUT((instructionsList[i].member[j].print),operand);break;
            case CCCC: OUTPUT((instructionsList[i].member[j].print),ConditionCodeName[operand]); break;
            case DISP: OUTPUT((instructionsList[i].member[j].print),operand); break;
            default: break;
          }
        }
      }
    }
  }
  return(boInstructionfound);
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  pdata 
///
/// \return uint8 
//-----------------------------------------------------------------------------
uint8 FetchAndDecode(uint8 const* pdata)
{
  
  if(DecodeInstruction(InstructionFetch16((uint16*)&pdata[0]), 2))/* fetch for 16bits instruction */
  {
    return(2);
  }
  else if(DecodeInstruction(InstructionFetch32((uint16*)&pdata[0]), 4))/* fetch for 32bits instruction */
  {
    return(4);
  }
  else if(DecodeInstruction(InstructionFetch48((uint16*)&pdata[0]), 6)) /* fetch for 48bits instruction */
  {
    return(6);
  }
  else if(DecodeInstruction(InstructionFetch64((uint16*)&pdata[0]), 8)) /* fetch for 64bits instruction */
  {
    return(8);
  }
  else
  {
    /* instruction not defined, check the next */
    OUTPUT("----\n");
    return(2); //could be also 4, 6, or 8
  }
}