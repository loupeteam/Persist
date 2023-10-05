(********************************************************************
 * COPYRIGHT -- Automation Resources Group
 ********************************************************************
 * Library: ErrorLib
 * File: ErrorLib_enum.typ
 * Author: David Blackburn
 * Created: November 23, 2011
 ********************************************************************
 * Data types of library ErrorLib
 ********************************************************************)

TYPE
	ERRCOL_ERR_enum : 
		(
		ERRCOL_ERROR := 50000,
		ERRCOL_ERR_ALLOC,
		ERRCOL_ERR_INVALIDINPUT,
		ERRCOL_ERR_NOTINIT,
		ERRCOL_ERR_FULLSOURCES,
		ERRCOL_ERR_FULLERRORS,
		ERRCOL_ERR_INVALIDSOURCE,
		ERRCOL_ERR_INVALIDERROR,
		ERRCOL_ERR_EMPTYLIST,
		ERRCOL_ERR_INCONSISTENTERROR,
		ERRCOL_ERR_
		);
END_TYPE
