/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Persist
 * File: persistInternalMapMemory.c
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
// Internal: Determine memory addresses 							*
//*******************************************************************

unsigned short persistInternalMapMemory(struct Persistence_typ* Persistence)
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
	
	UDINT CurrentReadAddress = Persistence->IN.pPersistentVariable;
	UDINT CurrentSize = 0;
	USINT i = 0;

	for( i = 0; i <= PERSIST_MAI_VARLIST; i++){


		// Get variable info
		
		UINT Status = PV_xgetadr(	Persistence->IN.WorkingVariableList[i],
			&(Persistence->Internal.WorkingVariableInfo[i].pWorkingVariable), 
			&(Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable) );
	
		if( Status == 0 ){
	
			// Check for room
		
			if( (CurrentSize + Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable + sizeof(Persistence_Var_Metadata)) <= Persistence->IN.sizeofPersistentVariable ){
		
				// Fits
		
				Persistence->Internal.WorkingVariableInfo[i].pMetadata=	CurrentReadAddress;
				Persistence->Internal.WorkingVariableInfo[i].pMetadata->variableSize= Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable;
				Persistence->Internal.WorkingVariableInfo[i].pPersistentMemory=	CurrentReadAddress+ sizeof(Persistence_Var_Metadata);
				
				CurrentSize += Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable + sizeof(Persistence_Var_Metadata);
				CurrentReadAddress += Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable + sizeof(Persistence_Var_Metadata);				

			} // fits
		
			else{
			
				// Doesn't fit
				
				// Keep counting so you know the total memory required for all variables
				CurrentSize += Persistence->Internal.WorkingVariableInfo[i].sizeofWorkingVariable + sizeof(Persistence_Var_Metadata);
				
				Persistence->OUT.STAT.Error= 	1;
				Persistence->OUT.STAT.ErrorID= 	PERSIST_ERR_OUTOFMEMORY;
				strcpy(Persistence->OUT.STAT.ErrorString, "Out of memory. Check OUT.STAT.RequiredMemory for number of bytes required for WorkingVariableList.");
			
			} // doesn't fit
			
		
		} // Found info
	
		else{
			// Error getting info. That is fine. Ignore it. Maybe log it.
		} // Error getting info
	
	} // loop through var list

	Persistence->OUT.STAT.RequiredMemory = 	CurrentSize;
	
	return Persistence->OUT.STAT.ErrorID;

} // End Fn
