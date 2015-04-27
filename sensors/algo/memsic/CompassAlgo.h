/*****************************************************************************
* Copyright (C), 2014, MEMSIC Inc.
* File Name		: CompassAlgo.h
* Author		: Yan Guopu		Version: 1.0	Data: 2014/11/09
* Description	: This file is the head file of CompassAlgo.lib. It provides the
* 			      interface function declarations of the lib.
* History		: 1. Data		:
* 	  		  2. Author		:
*		  	  3. Modification	:
*****************************************************************************/

#ifndef _COMPASSALGO_H_
#define _COMPASSALGO_H_

//Create a new name for existing types
#ifndef COMPASSLIB_TYPES
#define COMPASSLIB_TYPES
typedef   signed char  int8; 	// signed 8-bit number    (-128 to +127)
typedef unsigned char  uint8; 	// unsigned 8-bit number  (+0 to +255)

typedef   signed int  int16; 	// signed 16-bt number    (-32,768 to +32,767)
typedef unsigned int  uint16; 	// unsigned 16-bit number (+0 to +65,535)
#endif

#define NVM_SIZE        			1024
#define NVM_PATH				"/data/misc/sensors/magpara"	//ZTE

/*******************************************************************************************
* Function Name	: AlgoInitial
* Description	: Pass the calibrate acc and mag para
* Input		: fAccCalPara[0-8] --- Acc cal para;
* 		  fMagCalPara[0-8] --- Mag cal para;
********************************************************************************************/
int AlgoInitial(double *fMagCalPara);

/*******************************************************************************************
* Function Name	: AlgoMainFunction
* Description	: Pass the Acc raw data, Mag raw data and SET flag bit to the algorithm library.
* Input		: fRawData[3-5] --- Acceleration raw data of three axis;
* 		  fRawData[0-2] --- Magnetic raw data of three axis;
*		  flagTemp[0]   --- Calibration status. 0 = no need to calibrate.
*			1 = need to calibrate
*		  flagTemp[1]   --- SET and RESET flag bit. 0 = S&R finish.
*			1 = S&R not finish.
* Output	: None.
********************************************************************************************/
int MemsicAlgo(float *fRawData, uint8 *flagTemp, uint8 sampleRate, float *MemsicCorMag, uint8 *bStatus);

/*******************************************************************************************
* Function Name	: MemsicVirtualSensor
* Description	:
* Input		: None;
* Output	:
********************************************************************************************/
int MemsicOrientationSensor(float *dataOut);

/*******************************************************************************************
* Function Name	: GetBatType
* Description	:
* Input		: None;
* Output	:
********************************************************************************************/
//int GetBatType(void);

/*******************************************************************************************
* Function Name	: CheckRaild
* Description	: Check if there is interference when start the sensor
* Input		: None;
* Output	:
********************************************************************************************/
int CheckRaild(float *fRawData);

/*******************************************************************************************
* Function Name	: AlgoMagParaLoad
* Description	: Read the mag para from the file in cell phone.
* Input		: None
* Output	: None.
* Return	: 0.
********************************************************************************************/
int AlgoMagParaLoad(void);

/*******************************************************************************************
* Function Name	: AlgoMagParaStore
* Description	: Save the mag para in the file in cell phone.
* Input		: None
* Output	: None.
* Return	: 0.
********************************************************************************************/
int AlgoMagParaStore(void);

#endif // _COMPASSALGO_H_






