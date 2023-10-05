(********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: PermMemory
 * File: PermMemory.typ
 * Author: Josh
 * Created: May 28, 2014
 ********************************************************************
 * Local data types of program PermMemory
 ********************************************************************)

TYPE
	diffTime_typ : 	STRUCT 
		fromLastSaved : DINT;
		hour : DINT;
		day : DINT;
	END_STRUCT;
	Configuration_typ : STRUCT
		minSaveTimeHour : UDINT;
	END_STRUCT;
		
END_TYPE
