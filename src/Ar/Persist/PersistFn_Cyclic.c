/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Persist
 * File: PersistFn_Cyclic.c
 * Author: davidblackburn
 * Created: October 14, 2013
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
// Copy values from working memory to persistent memory 			*
//*******************************************************************

// Passes first tests

unsigned short PersistFn_Cyclic(struct Persistence_typ* Persistence)
{

	// Check for invalid inputs or initialization error
	if( Persistence == 0 ) return (UINT)PERSIST_ERR_INVALIDINPUT;	

	if( 	(Persistence->IN.pPersistentVariable == 0)
		||	(Persistence->IN.sizeofPersistentVariable == 0)
	){
		Persistence->OUT.STAT.Error = 1;
		Persistence->OUT.STAT.ErrorID = PERSIST_ERR_INVALIDINPUT;
		strcpy(Persistence->OUT.STAT.ErrorString, "Invalid inputs");
		return (UINT)PERSIST_ERR_INVALIDINPUT;
	}

	if( Persistence->OUT.STAT.Error ) return Persistence->OUT.STAT.ErrorID; // error initializing
	
	// Initialize if not initialized
	if( !Persistence->OUT.STAT.Initialized ) return PersistFn_Init(Persistence);

	// Backup values to persistent memory
	persistInternalBackup(Persistence);

	// Check for memory realignment
	if( Persistence->Internal.iVariable > PERSIST_MAI_VARLIST ) Persistence->Internal.iVariable = 0;
	
	if( strcmp(Persistence->IN.WorkingVariableList[Persistence->Internal.iVariable], "") != 0 ){
		
		// Get current (possibly different after transfer) variable info
		PV_xgetadr( Persistence->IN.WorkingVariableList[Persistence->Internal.iVariable],
			&(Persistence->Internal.ValidWorkingVariable.pWorkingVariable), 
			&(Persistence->Internal.ValidWorkingVariable.sizeofWorkingVariable) );

		if( 	Persistence->Internal.ValidWorkingVariable.pWorkingVariable != Persistence->Internal.WorkingVariableInfo[Persistence->Internal.iVariable].pWorkingVariable
			||	Persistence->Internal.ValidWorkingVariable.sizeofWorkingVariable != Persistence->Internal.WorkingVariableInfo[Persistence->Internal.iVariable].sizeofWorkingVariable 	
		){
				
			// Variable has changed size or location. Data is invalid and memory needs to be remapped
			if( Persistence->IN.pDataValid != 0 ) *(BOOL*)Persistence->IN.pDataValid = 0;
			return persistInternalMapMemory(Persistence);
		
		} // Variable moved or changed size
	
	} // variable in list

	// Move on to next variable
	Persistence->Internal.iVariable++;
	if( Persistence->Internal.iVariable > PERSIST_MAI_VARLIST ) Persistence->Internal.iVariable = 0;
	
	return Persistence->OUT.STAT.ErrorID;

} // End Fn //
