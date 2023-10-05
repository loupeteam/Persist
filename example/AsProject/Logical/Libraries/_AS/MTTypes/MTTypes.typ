
TYPE
	MTBodeType : 	STRUCT  (*Bode diagram data.*)
		FrequencyVector : ARRAY[0..160]OF REAL; (*Frequency vector. Unit: [Hz].*)
		MagnitudeVector : ARRAY[0..160]OF REAL; (*Magnitude vector. Unit: [dB].*)
		PhaseVector : ARRAY[0..160]OF REAL; (*Phase vector. Unit: [�].*)
		MinFrequency : REAL; (*Minimum frequency shown on the Bode plot. Unit: [Hz].*)
		MaxFrequency : REAL; (*Maximum frequency shown on the Bode plot. Unit: [Hz].*)
		MinMagnitude : REAL; (*Minimum magnitude shown on the Bode plot. Unit: [dB].*)
		MaxMagnitude : REAL; (*Maximum magnitude shown on the Bode plot. Unit: [dB].*)
		MinPhase : REAL; (*Minimum phase shown on the Bode plot. Unit: [�].*)
		MaxPhase : REAL; (*Maximum phase shown on the Bode plot. Unit: [�].*)
	END_STRUCT;
	MTCommType : 	STRUCT  (*Datatype for internal use.*)
		ID : DINT; (*Datatype for internal use.*)
		Valid : BOOL; (*Datatype for internal use.*)
		Counter : UDINT; (*Datatype for internal use.*)
	END_STRUCT;
	MTFrequencyResponseType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType; (*Datatype for internal use.*)
		Frequency : ARRAY[0..160]OF REAL; (*Datatype for internal use.*)
		Magnitude : ARRAY[0..160]OF REAL; (*Datatype for internal use.*)
		Phase : ARRAY[0..160]OF REAL; (*Datatype for internal use.*)
		MinFrequency : REAL; (*Datatype for internal use.*)
		MaxFrequency : REAL; (*Datatype for internal use.*)
		MinMagnitude : REAL; (*Datatype for internal use.*)
		MaxMagnitude : REAL; (*Datatype for internal use.*)
		MinPhase : REAL; (*Datatype for internal use.*)
		MaxPhase : REAL; (*Datatype for internal use.*)
		CheckID : DINT := -20583; (*Datatype for internal use.*)
	END_STRUCT;
	MTPIDIntegrationEnum : 
		( (*PID integration enumeration.*)
		mtINTEGRATION_FREE := 0, (*PID integration part can increase or decrease.*)
		mtHOLD_INTEGRATION_POSITIVE := +1, (*The output has reached its maximum allowed value and the integration has stopped.*)
		mtHOLD_INTEGRATION_NEGATIVE := -1 (*The output has reached its minimum allowed value and the integration has stopped.*)
		);
	MTPIDParametersType : 	STRUCT  (*PID parameters type.*)
		Gain : REAL; (*Proportional gain. Permitted range of values: Gain> 0.*)
		IntegrationTime : REAL; (*Integral action time of the integral component. Unit: [s]. Permitted range of values: IntegrationTime = 0s or IntegrationTime >= task cycle time*)
		DerivativeTime : REAL; (*Derivative time (derivative action time) of the derivative component. Unit: [s]. Permitted range of values: DerivativeTime >= 0s.*)
		FilterTime : REAL; (*Filter time constant of the derivative component. Unit: [s]. Permitted range of values: FilterTime >= 0s.*)
	END_STRUCT;
	MTStateSpaceType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType; (*Datatype for internal use.*)
		A : REFERENCE TO LREAL; (*Datatype for internal use.*)
		B : REFERENCE TO LREAL; (*Datatype for internal use.*)
		C : REFERENCE TO LREAL; (*Datatype for internal use.*)
		D : REFERENCE TO LREAL; (*Datatype for internal use.*)
		NbStates : USINT; (*Datatype for internal use.*)
		NbInputs : USINT; (*Datatype for internal use.*)
		NbOutputs : USINT; (*Datatype for internal use.*)
		SampleTime : REAL; (*Datatype for internal use.*)
		CheckID : DINT := -52417; (*Datatype for internal use.*)
	END_STRUCT;
	MTTransferFcnType : 	STRUCT  (*Datatype for internal use.*)
		Communication : MTCommType; (*Datatype for internal use.*)
		Numerator : ARRAY[0..5]OF REAL; (*Datatype for internal use.*)
		Denominator : ARRAY[0..5]OF REAL; (*Datatype for internal use.*)
		SampleTime : REAL; (*Datatype for internal use.*)
		CheckID : DINT := -45012; (*Datatype for internal use.*)
	END_STRUCT;
END_TYPE
