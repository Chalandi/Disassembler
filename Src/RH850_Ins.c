#include<RH850_InsProto.h>
#include<RH850_InsMacro.h>

//=============================================================================
// Prototypes
//=============================================================================

static sint8 SignExtended5(uint8 data);
static sint16 SignExtended16(uint16 data);
static sint16 SignExtended9(uint16 data);
static sint32 SignExtended17(uint32 data);
static sint32 SignExtended22(uint32 data);
static uint32 SignExtended32(uint32 data);

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_BinsMsbDecode(uint64 inst, uint64 mask)
{
  uint64 pos, with, msb;

   msb = DecodeOperand(inst,(uint64)0x0000F000U);
   pos = DecodeOperand(inst,(uint64)0x0000080EU);

   if((inst & (uint64)BINS_MASK) == (uint64)BINS_1_OPCODE)
   {
    /* msb >= 16, lsb >= 16 */
     with = msb - pos + 1 + 32;
   }
   else if((inst & (uint64)BINS_MASK) == (uint64)BINS_2_OPCODE)
   {
    /* msb >= 16, lsb < 16 */
     with = msb - pos + 1 + 16;
   }
   else
   {
    /* msb < 16, lsb < 16 */
    with = msb - pos + 1;
   }

   /* print with */
   OUTPUT(PRINT_IMM,with);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_BinsLsbDecode(uint64 inst, uint64 mask)
{
  uint64 pos;

   pos = DecodeOperand(inst,(uint64)0x0000080EU);

   if((inst & (uint64)BINS_MASK) == (uint64)BINS_1_OPCODE)
   {
    /* msb >= 16, lsb >= 16 */
     pos = pos + 16;
   }
   else if((inst & (uint64)BINS_MASK) == (uint64)BINS_2_OPCODE)
   {
    /* msb >= 16, lsb < 16 */
     pos = pos;
   }
   else
   {
    /* msb < 16, lsb < 16 */
    pos = pos;
   }

   /* print pos */
   OUTPUT(PRINT_IMM,pos);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Disp9Decode(uint64 inst, uint64 mask)
{
  uint64 Disp = DecodeOperand(inst,mask);
  Disp = Disp << 1;
  OUTPUT(PRINT_SIG_DISP_END,(sint16)SignExtended9((uint16)Disp));
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Disp17Decode(uint64 inst, uint64 mask)
{
  uint64 Disp = DecodeOperand(inst,mask);
  Disp = Disp << 1;
  OUTPUT(PRINT_SIG_DISP_END,(sint32)SignExtended17((uint32)Disp));
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Disp22Decode(uint64 inst, uint64 mask)
{
  uint64 Disp = DecodeOperand(inst,mask);
  Disp = Disp << 1;
  OUTPUT(PRINT_DISP_END,(sint32)SignExtended22((uint32)Disp));
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Disp32Decode(uint64 inst, uint64 mask)
{
  uint64 Disp = DecodeOperand(inst,mask);
  Disp = Disp << 1;
  OUTPUT(PRINT_DISP_END,(uint32)SignExtended32((uint32)Disp));
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_AddImmDecode(uint64 inst, uint64 mask)
{
  sint8 imm = SignExtended5((uint8)DecodeOperand(inst,mask));
  OUTPUT(PRINT_SIG_IMM,(sint8)SignExtended5((uint8)imm));
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Imm16Decode(uint64 inst, uint64 mask)
{
  sint16 imm = SignExtended16((uint16)DecodeOperand(inst,mask));
  OUTPUT(PRINT_SIG_IMM,(sint16)imm);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Imm9Decode(uint64 inst, uint64 mask)
{
  sint16 imm = SignExtended9((uint16)DecodeOperand(inst,mask));
  OUTPUT(PRINT_SIG_IMM_END,(sint16)imm);
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  inst 
/// \param  mask 
///
/// \return void 
//-----------------------------------------------------------------------------
void Inst_Imm17Decode(uint64 inst, uint64 mask)
{
  sint32 imm = SignExtended17((uint32)DecodeOperand(inst,mask));
  OUTPUT(PRINT_SIG_IMM_END,(sint32)imm);
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint8 
//-----------------------------------------------------------------------------
static sint8 SignExtended5(uint8 data)
{
  sint8 res;

  if((data & ((uint8)1<<4)) == ((uint8)1<<4))
  {
    res = (sint8)((data | (uint8)0xF0U));
  }
  else
  {
    res = (sint8)((data & (uint8)0x0FU));
  }
  return(res);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint16 
//-----------------------------------------------------------------------------
static sint16 SignExtended16(uint16 data)
{
  sint16 res;

  if((data & ((uint16)1<<15)) == ((uint16)1<<15))
  {
    res = (sint16)((data | (uint16)0xFF00U));
  }
  else
  {
    res = (sint16)((data & (uint16)0x00FFU));
  }
  return(res);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint16 
//-----------------------------------------------------------------------------
static sint16 SignExtended9(uint16 data)
{
  sint16 res;

  if((data & ((uint16)1<<8)) == ((uint16)1<<8))
  {
    res = (sint16)((data | (uint16)0xFF00U));
  }
  else
  {
    res = (sint16)((data & (uint16)0x01FFU));
  }
  return(res);
}


//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint32 
//-----------------------------------------------------------------------------
static sint32 SignExtended17(uint32 data)
{
  sint32 res;

  if((data & ((uint32)1<<16)) == ((uint32)1<<16))
  {
    res = (sint32)((data | (uint32)0xFFFFFE00U));
  }
  else
  {
    res = (sint32)((data & (uint32)0x0000003FU));
  }
  return(res);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint32 
//-----------------------------------------------------------------------------
static sint32 SignExtended22(uint32 data)
{
  sint32 res;

  if((data & ((uint32)1<<21)) == ((uint32)1<<21))
  {
    res = (sint32)((data | (~(uint32)(0x00003FFFU))));
  }
  else
  {
    res = (sint32)((data & (uint32)0x00003FFFU));
  }
  return(res);
}

//-----------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  data 
///
/// \return sint32 
//-----------------------------------------------------------------------------
static uint32 SignExtended32(uint32 data)
{
  return(data);
}