
/*--------------------------------------------------------------------
 * TITLE: 		Flash Handle Functions
 * AUTHOR: 		mas/lilb
 * FILENAME: 	flash.c
 * PROJECT: 	m2
 * COPYRIGHT: 	SHRIME, Inc.
 * DESCRIPTION:
 * 		2016-07-14	-	mas/lilb	-	started
 *		2016-07-15	-	mas/lilb	-	subfunctions define
 *
 *--------------------------------------------------------------------*/

#include "mcu.h"
#include "FLASH.h"

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockEnEx
 * DESCRIPTION:
 *    This sub function is used to make flash block valuable
 * PARAMETERS:
 * 		unsigned long BNum: Block Numbers
 * RETURN VALUE: 
 *		BlockNumError:		No block number, error input
 *		BlockEnPass:		Block enable success
 *		BlockEnFail:		Block enable fail
 *--------------------------------------------------------------------*/

 unsigned char RT_FlashBlockEnEx(unsigned long BNum)
 {
	unsigned long FlashBlockEnBase;
	if (BNum == 0)
		FlashBlockEnBase = FLASH_B0_START;						// identify Block Number
	else if (BNum == 1)
		FlashBlockEnBase = FLASH_B1_START;						// also B1
	else
			return (BlockNumError);
		
	flashWrite(0x55555555,FlashBlockEnBase);						// Enable Block
	
	unsigned long checkEn,checkDis;
	
	checkEn = MemoryRead32(FlashBlockEnBase);
	checkDis= MemoryRead32(FlashBlockEnBase + 4);
			
	if(checkEn == 0x55555555 && checkDis == 0xFFFFFFFF)			// check
		return (BlockEnPass);
	else
		return (BlockEnFail);
}
 
 /*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockDisEx
 * DESCRIPTION:
 *    This sub function is used to make flash block disvaluable
 * PARAMETERS:
 * 		unsigned long BNum: Block Numbers
 * RETURN VALUE: 
 *		BlockNumError:		No block number, error input
 *		BlockDisPass:		Block disable success
 *		BlockdisFail:		Block disable fail
 *--------------------------------------------------------------------*/
 
unsigned char RT_FlashBlockDisEx(unsigned long BNum)
{
	unsigned long FlashBlockDisBase;
	if (BNum == 0)
		FlashBlockDisBase = FLASH_B0_START;						// identify Block Number
	else if (BNum == 1)
		FlashBlockDisBase = FLASH_B1_START;						// also B1
	else
		return (BlockNumError);
		
	flashWrite(0x55555555,FlashBlockDisBase + 4);					// Enable Block	
	
	unsigned long checkEn,checkDis;
	
	checkEn = MemoryRead32(FlashBlockDisBase);
	checkDis= MemoryRead32(FlashBlockDisBase + 4);
	
	if(checkEn == 0x55555555 && checkDis == 0x55555555)			//check
		return(BlockDisPass);
	else
		return(BlockDisFail);
}
 
 
/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockEraseEx
 * DESCRIPTION:
 *  	This sub function is used to erase a block named BNo
 * PARAMETERS:
 * 		unsigned long BNum: Block Number
 * RETURN VALUE:
 *		BlockErasePass: 	Erase Success
 *		BlockNumError:		No block number, error input
 *		BlockEraseError:	Block erase fail
 *--------------------------------------------------------------------*/

unsigned char RT_FlashBlockEraseEx(unsigned long BNum)
{
	unsigned long FlashBlockEraseBase;
	
	if (BNum == 0)
		FlashBlockEraseBase = FLASH_B0_START;					// identify Block Number
	else if (BNum == 1)
		FlashBlockEraseBase = FLASH_B1_START;					// also B1
	else
	{
		FlashBlockEraseBase = FLASH_NO_BLOCK;
		return (BlockNumError);
	}
	
	int i;
	
	for(i = 0; i < 6; i++)
	{
		flashErase(FlashBlockEraseBase + i * 512);				// erase 6 sector continually
	}
	
	unsigned long checkMem;										// erase check
	
	for(i = 0; i < 12; i++)
	{
		checkMem = MemoryRead8(FlashBlockEraseBase + i * 256);	// only check intervally
		if(checkMem != 0xFF)
			return (BlockEraseError);							// return if erase fail
	}
	return (BlockErasePass);									// return PASS if all good
}
 
/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockInitEx
 * DESCRIPTION:
 *    This sub function is used to Initiallize a flash block
 * PARAMETERS:
 *    unsigned long BNum: Block Number
 * RETURN VALUE:
 *		BlockIniPass: 	Erase Success
 *		BlockNumError:	No block number, error input
 *		BlockIniError:	Block erase fail
 *--------------------------------------------------------------------*/

unsigned char RT_FlashBlockInitEx(unsigned long BNum)
{
	if (BNum != 0 && BNum !=1)
		return (BlockNumError);									// no BNo match
		
	unsigned long checkErase;
	checkErase = RT_FlashBlockEraseEx(BNum);
	
	if (checkErase == 0xF1)
		return (BlockNumError);									// normally not be excessed
	else if (checkErase == 0xF2)
		return (BlockIniError);	
	else
		return (BlockIniPass);
}

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockDbgEx
 * DESCRIPTION:
 *    This sub function is used to debug the state of the block
 * PARAMETERS:
 *    unsigned long BNum: block number
 * RETURN VALUE:
 *	  All above state
 *--------------------------------------------------------------------*/
 
unsigned char RT_FlashBlockDbgTypeEx(unsigned long BNum)
{
	unsigned char i;
	if(DBG_MODE == 0x01)
	{
		i = RT_FlashBlockInitEx(BNum);
		if (i == BlockNumError)
			return BlockNumError;
		if(i == BlockIniError)
			return BlockIniError;
		i = RT_FlashBlockEraseEx(BNum);
		if (i == BlockNumError)
			return BlockNumError;
		if(i == BlockEraseError)
			return BlockEraseError;
		i = RT_FlashBlockEnEx(BNum);
		if (i == BlockNumError)
			return BlockNumError;
		if(i == BlockEnFail)
			return BlockEnFail;		
		i = RT_FlashBlockDisEx(BNum);
		if (i == BlockNumError)
			return BlockNumError;
		if(i == BlockDisFail)
			return BlockDisFail;
		return DBG_MODE_PASS;
	}
	else
		return NO_DBG_MODE;
}

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockDbgLineEx
 * DESCRIPTION:
 *    This sub function is used to debug where the first nonblank Line
 *	  of the block is.
 * PARAMETERS:
 *    unsigned long BNum: block number
 * RETURN VALUE:
 *	  ErrorLineAddr: the error block line address
 *--------------------------------------------------------------------*/
unsigned long RT_FlashBlockDbgLineEx(unsigned long BNum)
{
	unsigned long ErrorLineAddr;
	unsigned long FlashBlockErrorBase;
	if (DBG_MODE == 0x01)
	{
		if (BNum == 0)
			FlashBlockErrorBase = FLASH_B0_START;					// identify Block Number
		else if (BNum == 1)
			FlashBlockErrorBase = FLASH_B1_START;					// also B1
		else
		{
			FlashBlockErrorBase = FLASH_NO_BLOCK;
			return (BlockNumError);
		}
		unsigned long tmpaddr;
		tmpaddr = FlashBlockErrorBase + 8;
		int i,j;
		
		for (i = 0; i < 255; i++)
		{
			j = MemoryRead32(tmpaddr);
			if(j != 0xFFFFFFFF)
			{
				ErrorLineAddr = tmpaddr;
				break;
			}
			tmpaddr = FlashBlockErrorBase + 8 + i * 12;
		}
		if (i == 255)
			return No_Error_Line;
		return ErrorLineAddr;
	}
	else
		return NO_DBG_MODE;
}

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockStateJudgeEx
 * DESCRIPTION:
 *    This sub function is used to judge the state of a flash block
 * PARAMETERS:
 *    unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		state
 *--------------------------------------------------------------------*/

unsigned char RT_FlashBlockStateJudgeEx(unsigned long block_addr)
{
	unsigned long valid_flag;
	unsigned long invalid_flag;
	unsigned char state;
	valid_flag = MemoryRead32(block_addr);
	invalid_flag = MemoryRead32(block_addr+4);
	
	if(valid_flag==0xffffffff && invalid_flag==0xffffffff)
		state = 0x00;									//initial state
	else if(valid_flag==0x55555555 && invalid_flag==0xffffffff)
		state = 0x01;									//valid state
	else if(valid_flag==0x55555555 && invalid_flag==0x55555555)
		state = 0x02;									//data_full, not aviliable for write, but erase
	else if((valid_flag&&invalid_flag)==0x0)
		state = 0x03;									//block forbiden to use
	else 
		state = 0x02;
	return state;
} 
  
/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockLineReadEx
 * DESCRIPTION:
 *    This sub function is used to read the value of a flash block
 * PARAMETERS:
 *    unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		no return data
 *--------------------------------------------------------------------*/ 

  void RT_FlashBlockLineReadEx(unsigned long block_addr, unsigned char bias_addr)
{
	unsigned long block_data_addr;
	block_data_addr = block_addr + 8 + (bias_addr-1)*12;
	block_data_word1 = MemoryRead32(block_data_addr);
	block_data_word2 = MemoryRead32(block_data_addr+4);
	block_data_word3 = MemoryRead32(block_data_addr+8);
}

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockLineWriteEx
 * DESCRIPTION:
 *    	This sub function is used to write the value of a flash block
 * PARAMETERS:
 *    	unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		
 *--------------------------------------------------------------------*/ 

int RT_FlashBlockLineWriteEx(unsigned long block_addr, unsigned char bias_addr, unsigned long word1, unsigned long word2, unsigned long word3)  
{
	RT_FlashBlockLineReadEx(block_addr, bias_addr);
	
	if(block_data_word1 == 0xffffffff && block_data_word1 == 0xffffffff && block_data_word1 == 0xffffffff )
	{
		flashWrite(word1, block_addr+8+(bias_addr-1)*12);
		flashWrite(word2, block_addr+8+(bias_addr-1)*12+4);
		flashWrite(word3, block_addr+8+(bias_addr-1)*12+8);
		return 0;
	}
	else
		return 1;
}
 
 /*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockDataLookUpEx
 * DESCRIPTION:
 *    	This sub function is used to write the value of a flash block
 * PARAMETERS:
 *    	unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		
 *--------------------------------------------------------------------*/ 
 
int RT_FlashBlockDataLookUpEx(unsigned long block_addr, unsigned char data_num)  //find:return 1   not find:return 0
{
	int state,i, find = 0;
	unsigned long word3_temp, word1_temp;
	//state = RT_FlashBlockStateJudgeEx();			org
	state = RT_FlashBlockStateJudgeEx(block_addr);		// by mas
	if(state == ValidState || state == DataFull)
	{
		for(i=255;i>0;i--)
		{
			RT_FlashBlockLineReadEx(block_addr, i);
			word3_temp = block_data_word3 >> 24;
			if(word3_temp == DataLable)
			{
				word1_temp = block_data_word1 & 0xff;
				if(word1_temp == data_num)
				{
					find = DataFind;
					break;
				}
			}
		}
	}	
	else
	{
		find = BlockCantfind;
	}
	return find;
}

/*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockRoomCheckEx
 * DESCRIPTION:
 *    	This sub function is used to write the value of a flash block
 * PARAMETERS:
 *    	unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		
 *--------------------------------------------------------------------*/ 
 
int RT_FlashBlockRoomCheckEx(unsigned long block_addr)
{
	long state,i;
	long spare_room_addr1=0;
	//state = RT_FlashBlockStateJudgeEx();	org
	state = RT_FlashBlockStateJudgeEx(block_addr);	//by mas
	if(state == ValidState || state == DataFull)
	{
		for(i=255;i>0;i--)
		{
			RT_FlashBlockLineReadEx(block_addr, i);
			if(block_data_word1==0xffffffff &&block_data_word2==0xffffffff &&block_data_word3==0xffffffff)
			{
				spare_room_addr1++;	//by mas
			}
			else
			{
				break;
			}
		}
	}	
	spare_room_addr1 = 256 - spare_room_addr1;
	return spare_room_addr1;
}

 /*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockWriteEx
 * DESCRIPTION:
 *    	This sub function is used to write the value of a flash block
 * PARAMETERS:
 *    	unsigned long block_addr: flash block address
 * RETURN VALUE:
 *		
 *--------------------------------------------------------------------*/ 

 int RT_FlashBlockWriteEx(unsigned long block_addr, unsigned long word1, unsigned long word2, unsigned long word3)
{
	int spare_room_addr;
	int state;
	//state = RT_FlashBlockStateJudgeEx();	org
	state = RT_FlashBlockStateJudgeEx(block_addr);	//by mas
	if(state == ValidState)
	{
		//spare_room_addr = RT_FlashBlockRoomCheckEx();	org
		spare_room_addr = RT_FlashBlockRoomCheckEx(block_addr);	//by mas
		if(spare_room_addr < 255)
		{
			RT_FlashBlockLineWriteEx(block_addr,spare_room_addr,word1, word2, word3);
			return WriteSucc;
		}
		else
		{
			return DataFull;
		}
	}
	else
	{
		return CantWrite;
	}
}

 /*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockCheckEx
 * DESCRIPTION:
 *    	This sub function is used to find whitch block is under usage
 * PARAMETERS:
 *    	No input parameters
 * RETURN VALUE:
 *		0:	not fine
 *		1:	find
 *--------------------------------------------------------------------*/

int RT_FlashBlockCheckEx()  //to find whitch block is under usage : ReadBlock, WirteBlock, 1: find  0:not find
{
	unsigned long valid_flag, invalid_flag, valid_flag1, invalid_flag1;
	unsigned long valid_flag2, invalid_flag2, valid_flag3, invalid_flag3;
	int block_status;
	valid_flag = MemoryRead32(Block0);
	invalid_flag = MemoryRead32(Block0 + 4);	
	valid_flag1 = MemoryRead32(Block1);
	invalid_flag1 = MemoryRead32(Block1 + 4);
	valid_flag2 = MemoryRead32(Block2);
	invalid_flag2 = MemoryRead32(Block2 + 4);	
	valid_flag3 = MemoryRead32(Block3);
	invalid_flag3 = MemoryRead32(Block3 + 4);
	
	if(valid_flag==0xffffffff && valid_flag1 == 0xffffffff)
	{
		flashWrite(0x55555555, Block0);
	}
	if(valid_flag2==0xffffffff && invalid_flag2 == 0xffffffff)
	{
		flashWrite(0x55555555, Block2);
	}
	if(valid_flag3==0xffffffff && invalid_flag3 == 0xffffffff)
	{
		flashWrite(0x55555555, Block3);
	}
	valid_flag = MemoryRead32(Block0);
	invalid_flag = MemoryRead32(Block0 + 4);
	if(valid_flag == 0x55555555 && invalid_flag == 0xffffffff)
	{
		ReadBlock = Block0;
		WriteBlock = Block0;
		block_status = 1;
	}
	else if(valid_flag1 == 0x55555555 && invalid_flag1 == 0xffffffff)
	{
		ReadBlock = Block1;
		WriteBlock = Block1;
		block_status = 1;
	}
	else
	{
		block_status = 0;
	}
	return block_status;
}

 /*--------------------------------------------------------------------
 * SUBFUNCTION: RT_FlashBlockTransDataEx
 * DESCRIPTION:
 *    	This sub function is used to transfer data between blocks
 * PARAMETERS:
 *    	No input parameters
 * RETURN VALUE:
 *		No return value
 *--------------------------------------------------------------------*/
 
void RT_FlashBlockTransDataEx()
{
	unsigned long word1_temp;
	int spare_num, data_sum, i;
	WriteBlock=(WriteBlock==Block0)?Block1:Block0;
	flashWrite(0x55555555, WriteBlock);
	spare_num = RT_FlashBlockRoomCheckEx(ReadBlock);
	spare_num = spare_num -1;
	RT_FlashBlockLineReadEx(ReadBlock, spare_num);      //read the last data 
	word1_temp = block_data_word1&0xff;
	//MemoryWrite32(0x01000150, 0x1);
	if(word1_temp ==121)
	{
		data_sum = block_data_word1>>8&0xff;
		RT_FlashBlockWriteEx(WriteBlock, block_data_word1, block_data_word2, block_data_word3);
	}
	else
	{
		RT_FlashBlockWriteEx(WriteBlock, block_data_word1, block_data_word2, block_data_word3);
		RT_FlashBlockDataLookUpEx(ReadBlock, 121);
		RT_FlashBlockWriteEx(WriteBlock, block_data_word1, block_data_word2, block_data_word3);
		data_sum = block_data_word1>>8&0xff;
	}
	//MemoryWrite32(0x01000160, data_sum);
	
	for(i=0; i<data_sum;i++)
	{
		RT_FlashBlockDataLookUpEx(ReadBlock, i);
		RT_FlashBlockWriteEx(WriteBlock,  block_data_word1, block_data_word2, block_data_word3);
	}
	if(ReadBlock == Block0)
		RT_FlashBlockEraseEx(0);  		//mas
	if(ReadBlock == Block1)
		RT_FlashBlockEraseEx(1);
	ReadBlock=WriteBlock;
}

