/*
** Filename: eefs_macros.h
**
**      Copyright (c) 2010-2014, United States government as represented by the 
**      administrator of the National Aeronautics Space Administration.  
**      All rights reserved. This software was created at NASAs Goddard 
**      Space Flight Center pursuant to government contracts.
**
**      This is governed by the NASA Open Source Agreement and may be used, 
**      distributed and modified only pursuant to the terms of that agreement.
**
*/

/*
**
** Purpose: This file contains system dependent macros for eefs lower level functions.
**
** Design Notes:
**
** References:
**
*/

#ifndef _eefs_macros_
#define	_eefs_macros_

#include "eeprom.h"

/*
 * System Dependent Lower Level Functions
 */

/* These macros define the lower level EEPROM interface functions.  Defaults to memcpy(Dest, Src, Length) */
#define EEFS_LIB_EEPROM_WRITE(Dest, Src, Length) EEPROMWrite((uint16_t)Dest, (uint8_t*)Src, (uint16_t)Length)
#define EEFS_LIB_EEPROM_READ(Dest, Src, Length)  EEPROMRead((uint16_t)Src, (uint8_t*)Dest, (uint16_t)Length)
#define EEFS_LIB_EEPROM_FLUSH

/* These macros define the lock and unlock interface functions used to guarentee
 * exclusive access to shared resources.  Defaults to undefined since it is implementation dependent */
#define EEFS_LIB_LOCK
#define EEFS_LIB_UNLOCK

/* This macro defines the time interface function.  Defaults to time(NULL) */
#define EEFS_LIB_TIME                           time(NULL)

/* This macro defines the file system write protection interface function.  If the file system
   is read-only then set this macro to TRUE.  If the file system is always write enabled then
   set this macro to FALSE.  If the eeprom has an external write protection interface then a custom
   function can be called to determine the write protect status. */
#define EEFS_LIB_IS_WRITE_PROTECTED              FALSE

#endif

/************************/
/*  End of File Comment */
/************************/

