/*
 * File: PersistFn_Init.c
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of Persist, licensed under the MIT License.
 * 
 */

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "Persist.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif


//*******************************************************************
// Copy values from persistent memory to working memory 			*
//*******************************************************************

// Passes first tests

unsigned short PersistFn_Init(Persistence_typ* Persistence)
{

	// Check for invalid inputs

	if( Persistence == 0 ) return (UINT)PERSIST_ERR_INVALIDINPUT;	

	if( 	(Persistence->IN.pPersistentVariable == 0)
		||	(Persistence->IN.sizeofPersistentVariable == 0)
	){
		Persistence->OUT.STAT.Error= 	1;
		Persistence->OUT.STAT.ErrorID= 	PERSIST_ERR_INVALIDINPUT;
		strcpy(Persistence->OUT.STAT.ErrorString, "Invalid inputs");
		return (UINT)PERSIST_ERR_INVALIDINPUT;
	}

	
	// Initialize

	memset( &(Persistence->Internal), 0, sizeof(Persistence->Internal) );
	memset( &(Persistence->OUT), 0, sizeof(Persistence->OUT) );
	
	persistInternalMapMemory(Persistence);

	persistInternalRestore(Persistence);
	
	if( !Persistence->OUT.STAT.Error ) Persistence->OUT.STAT.Initialized = 1;

	return Persistence->OUT.STAT.ErrorID;

} // End Fn
