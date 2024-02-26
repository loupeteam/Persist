/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Persist
 * File: persistInternalRestore.c
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
// Internal: Restore from persistent memory 						*
//*******************************************************************

unsigned short persistInternalRestore(struct Persistence_typ* Persistence)
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
	
	if( dataValid ){
	
		for( i = 0; i <= PERSIST_MAI_VARLIST; i++ ){
		
			if( 	(Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory != 0)
				&&	(Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable != 0)
				&&	(Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable != 0)
			){
				if(Persistence->Internal.WorkingVariableInfo[i].pMetadata != 0){ //we have metadata
					if(Persistence->Internal.WorkingVariableInfo[i].pMetadata->variableSize != Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable){ //the size in the metadata doesn't match
						*(BOOL*)Persistence->IN.pDataValid = 0;
						return (UINT)PERSIST_ERR_DATAMOVED_CHANGED;
					}
					if(Persistence->Internal.WorkingVariableInfo[i].pMetadata->pSelf == 0){
						Persistence->Internal.WorkingVariableInfo[i].pMetadata->pSelf = Persistence->Internal.WorkingVariableInfo[i].pMetadata;
					}
					else if(Persistence->Internal.WorkingVariableInfo[i].pMetadata->pSelf != Persistence->Internal.WorkingVariableInfo[i].pMetadata){
						*(BOOL*)Persistence->IN.pDataValid = 0;
						return (UINT)PERSIST_ERR_DATAMOVED_CHANGED;
					}
				}

			
				memcpy(	(void*)Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable, 
					(void*)Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory, 
					Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable);
			
			} // Valid variable
			
		} // Loop through variables
		
	} // if(dataValid)

	return 0;

} // End Fn