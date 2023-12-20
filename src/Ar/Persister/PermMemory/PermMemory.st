(********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: PermMemory
 * File: PermMemory.st
 * Author: Josh
 * Created: May 28, 2014
 ********************************************************************
 * Implementation of program PermMemory
 ********************************************************************)

PROGRAM _INIT

	// Persisters and CSV backups are set up in FirstInitProg
	
	// Initialize buffer for keeping track of configuration and misc. struct value changes.
	brsmemcpy(ADR(permConfigurationBuff), ADR(gPermConfiguration), SIZEOF(permConfigurationBuff));
	brsmemcpy(ADR(permMiscBuff), ADR(gPermMisc), SIZEOF(permMiscBuff));
	brsmemcpy(ADR(permAxisCfgBuff), ADR(gPermAxisCfgs), SIZEOF(permAxisCfgBuff));
	
	//Initialize Get Time Function
	getTime.enable := 1;
	
	//Convert minimum time to save config files from hour to seconds
	minSaveTime := Configuration.minSaveTimeHour * 3600;
	
END_PROGRAM


PROGRAM _CYCLIC
	IF (gTransfer.transfer) THEN
		RETURN;
	END_IF
	
	IF( backupAll )THEN
		backupAll := 0;
		
		FOR i:=0 TO NUM_PERSISTERS-1 BY 1 DO
			IF gDataValid[i] THEN
				gPermBackup[i].IN.CMD.SaveVariableListToFile := 1;
			ELSE
				Message:= CONCAT(CONCAT('Permanent data is invalid for the file:',gPermBackup[i].IN.PAR.FileName),'. Would you like to save anyway?');
				MessageBox_AddMsg(ADR(Message), ADR('Yes Overwrite'),ADR(gPermBackup[i].IN.CMD.SaveVariableListToFile),ADR('Cancel'),0);
			END_IF	
		END_FOR
		IF gHomeDataOk THEN
			gBackupHome.IN.CMD.SaveVariableListToFile := 1;
		ELSE
			Message:= CONCAT(CONCAT('Homing data is invalid:',gPermBackup[i].IN.PAR.FileName),'. Would you like to save anyway?');
			MessageBox_AddMsg(ADR(Message), ADR('Yes Overwrite'),ADR(gBackupHome.IN.CMD.SaveVariableListToFile),ADR('Cancel'),0);			
		END_IF
	END_IF
	
	IF( restoreAll )THEN
		restoreAll := 0;
		FOR i:=0 TO NUM_PERSISTERS-1 BY 1 DO
			gPermBackup[i].IN.CMD.OpenFile := 1;
		END_FOR
	END_IF
	
	FOR i:=0 TO NUM_PERSISTERS-1  DO

		IF gDataValid[i] THEN
			PersistNames[i]:= gPermBackup[i].IN.PAR.FileName;
		ELSE
			PersistNames[i]:= CONCAT(gPermBackup[i].IN.PAR.FileName, ' (Corrupt - Reload!)');			
		END_IF	
		PersistFn_Cyclic(gPersister[i]);
		
		CSVFn_Cyclic(gPermBackup[i]);
		
		IF (gPermBackup[i].OUT.STAT.Done AND gPermBackup[i].IN.CMD.OpenFile) THEN
			gDataValid[i] := TRUE;
			errcolAddError(ADR('Data restored'), ADR(gPermBackup[i].IN.PAR.FileName), 0, 0, gErrorCollector);
		END_IF
		
		IF (gPermBackup[i].OUT.STAT.Done OR gPermBackup[i].OUT.STAT.Error) THEN
			gPermBackup[i].IN.CMD.OpenFile := 0;
			gPermBackup[i].IN.CMD.SaveVariableListToFile := 0;
		END_IF
		
	END_FOR
	
	//Handle home data separately and manually
	CSVFn_Cyclic(gBackupHome);	
	gBackupHome.IN.CMD.AcknowledgeError:= FALSE;
	gBackupHome.IN.CMD.OpenFile := 0;
	gBackupHome.IN.CMD.SaveVariableListToFile := 0;
					
	VariableList ACCESS ADR(gPersister[SelectedPersist].IN.WorkingVariableList);
	VariableFinder.VariableName:=	VariableList[SelectedVariable];
	VariableFinder();
	

	getTime();
	currentTime := getTime.DT1;
	
	// Check the configuration.csv file cyclically for changes. 
	IF DiffDT(currentTime,gPermLastSavedTime[0]) > minSaveTime AND (brsmemcmp(ADR(gPermConfiguration), ADR(permConfigurationBuff), SIZEOF(gPermConfiguration)) <> 0) THEN
		gPermBackup[PERM_CONFIGURATION].IN.CMD.UpdateFile := TRUE;
		brsmemcpy(ADR(permConfigurationBuff), ADR(gPermConfiguration), SIZEOF(permConfigurationBuff));
		gPermLastSavedTime[0] := currentTime;
	END_IF
	IF DiffDT(currentTime,gPermLastSavedTime[1]) > minSaveTime AND (brsmemcmp(ADR(gPermMisc), ADR(permMiscBuff), SIZEOF(gPermMisc)) <> 0) THEN
		gPermBackup[PERM_MISC].IN.CMD.UpdateFile := TRUE;
		brsmemcpy(ADR(permMiscBuff), ADR(gPermMisc), SIZEOF(permMiscBuff));
		gPermLastSavedTime[1] := currentTime;
	END_IF
	IF DiffDT(currentTime,gPermLastSavedTime[2]) > minSaveTime AND (brsmemcmp(ADR(gPermAxisCfgs), ADR(permAxisCfgBuff), SIZEOF(gPermAxisCfgs)) <> 0) THEN
		gPermBackup[PERM_AXIS_CFG].IN.CMD.UpdateFile := TRUE;
		brsmemcpy(ADR(permAxisCfgBuff), ADR(gPermAxisCfgs), SIZEOF(permAxisCfgBuff));
		gPermLastSavedTime[2] := currentTime;
	END_IF
	
	
	IF ((gPermBackup[PERM_CONFIGURATION].OUT.STAT.Done) OR (gPermBackup[PERM_CONFIGURATION].OUT.STAT.Error)) THEN
		gPermBackup[PERM_CONFIGURATION].IN.CMD.UpdateFile := FALSE;
	END_IF
	IF ((gPermBackup[PERM_MISC].OUT.STAT.Done) OR (gPermBackup[PERM_MISC].OUT.STAT.Error)) THEN
		gPermBackup[PERM_MISC].IN.CMD.UpdateFile := FALSE;
	END_IF
	IF ((gPermBackup[PERM_AXIS_CFG].OUT.STAT.Done) OR (gPermBackup[PERM_AXIS_CFG].OUT.STAT.Error)) THEN
		gPermBackup[PERM_AXIS_CFG].IN.CMD.UpdateFile := FALSE;
	END_IF	
END_PROGRAM
