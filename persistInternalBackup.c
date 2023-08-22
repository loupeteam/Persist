/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Persist
 * File: persistInternalBackup.c
 * Author: dfblackburn
 * Created: March 24, 2015
 ********************************************************************
 * Implementation of library Persist
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

	#include "Persist.h"

#ifdef __cplusplus
	};
#endif

#include <string.h>

//*******************************************************************
// Internal: Backup to persistent memory 							*
//*******************************************************************

unsigned short persistInternalBackup(struct Persistence_typ* Persistence)
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

	
	// Loop through variable list

	BOOL dataValid;
	
	if( Persistence->IN.pDataValid != 0 ){
		dataValid = *(BOOL*)Persistence->IN.pDataValid;
	}
	else {
		dataValid = 1;
	}
	
	
	USINT i;
	DTGetTime_typ getTime;
	
	getTime.enable = 0;
	DTGetTime(&getTime);

	if( dataValid ){
	
		for( i = 0; i <= PERSIST_MAI_VARLIST; i++ ){
		
			if( 	(Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory != 0)
				&&	(Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable != 0)
				&&	(Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable != 0)
				&&  (memcmp((void*)Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory, 
						(void*)Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable, 
						Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable) != 0)
				){
				
					memcpy(	(void*)Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory, 
						(void*)Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable, 
						Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable);
						Persistence->Internal.WorkingVariableInfo[i].pMetaData->dataChanged = 1;
				} // Valid variable
				
			} // Loop through variables
			
		} // if(dataValid)

		return 0;

	} // End Fn
