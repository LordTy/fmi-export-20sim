/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  %FILE_NAME%
 *  subm:  %SUBMODEL_NAME%
 *  model: %MODEL_NAME%
 *  expmt: %EXPERIMENT_NAME%
 *  date:  %GENERATION_DATE%
 *  time:  %GENERATION_TIME%
 *  user:  %USER_NAME%
 *  from:  %COMPANY_NAME%
 *  build: %GENERATION_BUILD%
 **********************************************************/

/* Standard include files */
#include <stdlib.h>

/* 20-sim include files */
#include "xxmodel.h"
#include "xxinteg.h"
#include "xxfuncs.h"
#include "xxsubmod.h"
#include "motionprofiles.h"
#include "EulerAngles.h"


/* The initialization function for submodel */
XXBoolean %FUNCTIONPREFIX%InitializeSubmodel (%VARPREFIX%ModelInstance* model_instance)
{
	/* Initialization phase (allocating memory) */
	model_instance->%XX_INITIALIZE% = XXTRUE;
	model_instance->steps = 0;
	model_instance->m_initState = XXTRUE;
 
	%FUNCTIONPREFIX%CalculateInitial (model_instance);

	/* initialize the integration method */
	if (%FUNCTIONPREFIX%%INTEGRATION_METHOD_NAME%Initialize (model_instance) == XXFALSE)
	{
		model_instance->m_initState = XXFALSE;
		return XXFALSE;
	}

%IF%%0%
	/* Calculate the model for the first time */
	%FUNCTIONPREFIX%CalculateStatic (model_instance);
	%FUNCTIONPREFIX%CalculateInput (model_instance);
	%FUNCTIONPREFIX%CalculateDynamic (model_instance);
	%FUNCTIONPREFIX%CalculateOutput (model_instance);
%ENDIF%

	/* End of initialization phase */
	model_instance->%XX_INITIALIZE% = XXFALSE;
	model_instance->m_initState = XXFALSE;

	return XXTRUE;
}

/* The function that calculates the submodel */
XXBoolean %FUNCTIONPREFIX%CalculateSubmodel (%VARPREFIX%ModelInstance* model_instance, XXDouble t, XXDouble outputTime)
{
	/* Copy the time */
	model_instance->time = t;

	/* Calculate the model */
	%FUNCTIONPREFIX%CalculateInput (model_instance);
	if (%FUNCTIONPREFIX%%INTEGRATION_METHOD_NAME%Step (model_instance, outputTime) == XXFALSE)
		return XXFALSE;
	%FUNCTIONPREFIX%CalculateOutput (model_instance);
	return XXTRUE;
}

/* The termination function for submodel */
XXBoolean %FUNCTIONPREFIX%TerminateSubmodel (%VARPREFIX%ModelInstance* model_instance, XXDouble t)
{
	/* Copy the time */
	model_instance->time = t;

	/* Calculate the final model equations */
	%FUNCTIONPREFIX%CalculateFinal (model_instance);

	/* and terminate the model itself (releasing memory) */
	%FUNCTIONPREFIX%ModelTerminate (model_instance);
	if( %FUNCTIONPREFIX%%INTEGRATION_METHOD_NAME%Terminate (model_instance) == XXFALSE)
		return XXFALSE;

	return XXTRUE;
}
