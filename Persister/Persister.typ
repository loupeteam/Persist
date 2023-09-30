(*Enum for persisters*)

TYPE
	PERM_enum : 
		(
		PERM_CONFIGURATION,
		PERM_HOME_DATA,
		PERM_AXIS_PARS,
		PERM_AXIS_CFG,
		PERM_MISC,
		PERM_
		);
	Transfer_typ : 	STRUCT 
		cyclic : BOOL;
		transfer : BOOL;
		bootAfterTransfer : BOOL;
	END_STRUCT;
END_TYPE
