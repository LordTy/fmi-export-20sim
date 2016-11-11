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

/* This file describes the model functions
   that are supplied for computation.

   The model itself is the xxmodel.c file
*/

#ifndef XX_MODEL_H
#define XX_MODEL_H

/* Our own include files */
#include "xxtypes.h"
%IF%%NUMBER_MATRICES%
#include "xxmatrix.h"
%ENDIF%
#include "%FMI_PREFIX%Functions.h"

%IF%%EQ(INTEGRATION_METHOD_NAME,VodeAdams)%
#include "cvode/cvode.h"            /* main CVODE header file                       */
#include "cvode/cvode_dense.h"      /* use CVDENSE linear solver each internal step */
#include <nvector/nvector_serial.h> /* serial N_Vector types, fct. and macros       */
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,MeBDFi)%
#include "MeBDFi/MeBDFi.h"
%ENDIF%

/* Model size constants */
#define %VARPREFIX%constants_count %NUMBER_CONSTANTS%
#define %VARPREFIX%parameter_count %NUMBER_PARAMETERS%
#define %VARPREFIX%initialvalue_count %NUMBER_INITIAL_VALUES%
#define %VARPREFIX%variable_count %NUMBER_VARIABLES%
#define %VARPREFIX%state_count %NUMBER_STATES%
%IF%%EQ(INTEGRATION_METHOD_NAME,MeBDFi)%
#define %VARPREFIX%depstate_count %NUMBER_DEPSTATES%
#define %VARPREFIX%algloop_count %NUMBER_ALGLOOPS%
#define %VARPREFIX%constraint_count %NUMBER_CONSTRAINTS%
%ELSE%
%IF%%NUMBER_DEPSTATES%
#define %VARPREFIX%depstate_count %NUMBER_DEPSTATES%
%ENDIF%
%IF%%NUMBER_ALGLOOPS%
#define %VARPREFIX%algloop_count %NUMBER_ALGLOOPS%
%ENDIF%
%IF%%NUMBER_CONSTRAINTS%
#define %VARPREFIX%constraint_count %NUMBER_CONSTRAINTS%
%ENDIF%
%ENDIF%

%IF%%NUMBER_MATRICES%
#define %VARPREFIX%NUMBER_MATRICES %NUMBER_MATRICES%
%ENDIF%
%IF%%NUMBER_UNNAMED%
#define %VARPREFIX%NUMBER_UNNAMED %NUMBER_UNNAMED%
%ENDIF%
%IF%%WORK_ARRAY_SIZE%
#define %VARPREFIX%WORK_ARRAY_SIZE %WORK_ARRAY_SIZE%
%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
#define %VARPREFIX%NUMBER_FAVORITE_PARAMETERS %NUMBER_FAVORITE_PARAMETERS%
%ENDIF%
%IF%%NUMBER_FAVORITE_VARIABLES%
#define %VARPREFIX%NUMBER_FAVORITE_VARIABLES %NUMBER_FAVORITE_VARIABLES%
%ENDIF%
%IF%%NUMBER_IMPORTS%
#define %VARPREFIX%NUMBER_IMPORTS %NUMBER_IMPORTS%
%ENDIF%
%IF%%NUMBER_EXPORTS%
#define %VARPREFIX%NUMBER_EXPORTS %NUMBER_EXPORTS%
%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
#define %VARPREFIX%NUMBEROF_INITIALFUNCTION %NUMBEROF_INITIALFUNCTION%
%ENDIF%
%IF%%NUMBEROF_DELAYFUNCTION%
#define %VARPREFIX%NUMBEROF_DELAYFUNCTION %NUMBEROF_DELAYFUNCTION%
%ENDIF%

%IF%%NUMBEROF_DELAYFUNCTION%
#define %VARPREFIX%delay_count %NUMBEROF_DELAYFUNCTION%
%ENDIF%

typedef struct %VARPREFIX%ModelInstance
{
/* Global pointer to co-simulator callback functions */
%IF%%FMI1%
	fmiCallbackFunctions fmiCallbackFunctions;
%ENDIF%
%IF%%FMI2%
	const fmi2CallbackFunctions* fmiCallbackFunctions;
%ENDIF%

	/* FMU */
	%FMI_PREFIX%String instanceName;

	/* Store the path to the extracted resource folder location provided by the
	 * co-simulation engine for this model instance
	 */
	const char* resourceLocation;

	/* Simulation variables */
	XXDouble start_time;
	XXDouble finish_time;
	XXBoolean m_use_finish_time;
	XXDouble step_size;
	XXDouble time;
	XXInteger steps;
	XXBoolean %XX_INITIALIZE%;
	XXBoolean major;
	XXBoolean stop_simulation;
	
	XXBoolean m_reinitState;
	XXBoolean m_initState;

	/* Model state */
	XXDouble MEMORY[
%IF%%NUMBER_CONSTANTS%
		%VARPREFIX%constants_count +
%ENDIF%
%IF%%NUMBER_PARAMETERS%
		%VARPREFIX%parameter_count + 
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
		%VARPREFIX%initialvalue_count + 
%ENDIF%
%IF%%NUMBER_VARIABLES%
		%VARPREFIX%variable_count + 
%ENDIF%
%IF%%NUMBER_STATES%
		%VARPREFIX%state_count /* states */ +
		%VARPREFIX%state_count /* rates */ +
%ENDIF%
%IF%%NUMBER_DEPSTATES%
		%VARPREFIX%depstate_count /* dependent states */ +
		%VARPREFIX%depstate_count /* dependent rates */ +
%ENDIF%
%IF%%NUMBER_ALGLOOPS%
		%VARPREFIX%algloop_count /* algebraic loop in */ +
		%VARPREFIX%algloop_count /* algebraic loop out */ +
%ENDIF%
%IF%%NUMBER_CONSTRAINTS%
		%VARPREFIX%constraint_count /* constraint in */ +
		%VARPREFIX%constraint_count /* constraint loop out */ +
%ENDIF%
		1
	];
%IF%%NUMBER_MATRICES%
	XXMatrix %XX_MATRIX_ARRAY_NAME%[%VARPREFIX%NUMBER_MATRICES];		/* matrices */
%ENDIF%
%IF%%NUMBER_UNNAMED%
	XXDouble %XX_UNNAMED_ARRAY_NAME%[%VARPREFIX%NUMBER_UNNAMED];		/* unnamed */
%ENDIF%
%IF%%WORK_ARRAY_SIZE%
	XXDouble workarray[%VARPREFIX%WORK_ARRAY_SIZE];
%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
	XXDouble %XX_FAVORITE_PARS_ARRAY_NAME%[%VARPREFIX%NUMBER_FAVORITE_PARAMETERS];	/* favorite parameters */
%ENDIF%
%IF%%NUMBER_FAVORITE_VARIABLES%
	XXDouble %XX_FAVORITE_VARS_ARRAY_NAME%[%VARPREFIX%NUMBER_FAVORITE_VARIABLES];		/* favorite variables */
%ENDIF%
%IF%%NUMBER_IMPORTS%
	XXDouble %XX_EXT_IN_ARRAY_NAME%[%VARPREFIX%NUMBER_IMPORTS]; /* import variables */
%ENDIF%
%IF%%NUMBER_EXPORTS%
	XXDouble %XX_EXT_OUT_ARRAY_NAME%[%VARPREFIX%NUMBER_EXPORTS]; /* export variables */
%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
	XXDouble initial_value_array[%VARPREFIX%NUMBEROF_INITIALFUNCTION];	/* initial*/
%ENDIF%
%IF%%NUMBEROF_DELAYFUNCTION%
	XXDouble delay_update_array[%VARPREFIX%NUMBEROF_DELAYFUNCTION];
	XXDouble delay_last_values[%VARPREFIX%NUMBEROF_DELAYFUNCTION];
%ENDIF%
%IF%%NUMBER_STATES%
	/* Integration method intermediate variables */
%IF%%EQ(INTEGRATION_METHOD_NAME,Discrete)%

	/* discrete time can be behind of continuous time
	 * dependent on the step size 
	 */
	XXDouble m_discrete_time;
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,RungeKutta2)%
	XXDouble q0[%VARPREFIX%state_count];
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,RungeKutta4)%
	XXDouble q0[%VARPREFIX%state_count];
	XXDouble q1[%VARPREFIX%state_count];
	XXDouble q2[%VARPREFIX%state_count];
	XXDouble q3[%VARPREFIX%state_count];
	XXDouble q4[%VARPREFIX%state_count];
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,VodeAdams)%
	double m_initial_step_size;
	double m_maximum_step_size;
	double m_absolute_tolerance;
	double m_relative_tolerance;
	XXBoolean m_use_initial_step;
	XXBoolean m_use_maximum_step;
	double m_last_step_size;

	int m_flag;

	/* 
	  now we should know how big it is
	void *m_prev_memory;
	void *m_prev_cvdense_mem;
	*/
	
	N_Vector m_cvode_y;
	N_Vector m_cvode_y0;
	void *m_cvode_mem;

	XXBoolean m_use_bdf;
	XXBoolean m_use_newton;

	XXBoolean m_dense_performed;
%ENDIF%
%IF%%EQ(INTEGRATION_METHOD_NAME,MeBDFi)%
	/* the structure containts all the member variables */
	MeBDFiMethod m_mebdfi_method;
%ENDIF%
%ENDIF%
	/* Memory offset pointers */
%IF%%NUMBER_CONSTANTS%
	XXDouble* %XX_CONSTANT_ARRAY_NAME%;	/* constants */
%ENDIF%
%IF%%NUMBER_PARAMETERS%
	XXDouble* %XX_PARAMETER_ARRAY_NAME%;	/* parameters */
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
	XXDouble* %XX_INITIAL_VALUE_ARRAY_NAME%;	/* initial values */
%ENDIF%
%IF%%NUMBER_VARIABLES%
	XXDouble* %XX_VARIABLE_ARRAY_NAME%;	/* variables */
%ENDIF%
%IF%%NUMBER_STATES%
	XXDouble* %XX_STATE_ARRAY_NAME%;	/* states */
	XXDouble* %XX_RATE_ARRAY_NAME%;	/* rates (or new states) */
%ENDIF%
%IF%%NUMBER_DEPSTATES%
	XXDouble* %XX_DEP_STATE_ARRAY_NAME%;	/* dependent states */
	XXDouble* %XX_DEP_RATE_ARRAY_NAME%;		/* dependent rates */
%ENDIF%
%IF%%OR(NUMBER_ALGLOOPS,NUMBER_CONSTRAINTS)%
	XXDouble* %XX_ALG_IN_ARRAY_NAME%;	/* algebraic loop + constraint in */
	XXDouble* %XX_ALG_OUT_ARRAY_NAME%;	/* algebraic loop + constraint out */
%ENDIF%
} %VARPREFIX%ModelInstance;

/* Variable arrays */
%IF%%NUMBER_CONSTANTS%
#define %VARPREFIX%%XX_CONSTANT_ARRAY_NAME% model_instance->%XX_CONSTANT_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_PARAMETERS%
#define %VARPREFIX%%XX_PARAMETER_ARRAY_NAME% model_instance->%XX_PARAMETER_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_INITIAL_VALUES%
#define %VARPREFIX%%XX_INITIAL_VALUE_ARRAY_NAME% model_instance->%XX_INITIAL_VALUE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_VARIABLES%
#define %VARPREFIX%%XX_VARIABLE_ARRAY_NAME% model_instance->%XX_VARIABLE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_STATES%
#define %VARPREFIX%%XX_STATE_ARRAY_NAME% model_instance->%XX_STATE_ARRAY_NAME%
#define %VARPREFIX%%XX_RATE_ARRAY_NAME% model_instance->%XX_RATE_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_DEPSTATES%
#define %VARPREFIX%%XX_DEP_STATE_ARRAY_NAME% model_instance->%XX_DEP_STATE_ARRAY_NAME%
#define %VARPREFIX%%XX_DEP_RATE_ARRAY_NAME% model_instance->%XX_DEP_RATE_ARRAY_NAME%
%ENDIF%
%IF%%OR(NUMBER_ALGLOOPS,NUMBER_CONSTRAINTS)%
#define %VARPREFIX%%XX_ALG_IN_ARRAY_NAME% model_instance->%XX_ALG_IN_ARRAY_NAME%
#define %VARPREFIX%%XX_ALG_OUT_ARRAY_NAME% model_instance->%XX_ALG_OUT_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_MATRICES%
#define %VARPREFIX%%XX_MATRIX_ARRAY_NAME% model_instance->%XX_MATRIX_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_UNNAMED%
#define %VARPREFIX%%XX_UNNAMED_ARRAY_NAME% model_instance->%XX_UNNAMED_ARRAY_NAME%
%ENDIF%
%IF%%WORK_ARRAY_SIZE%
#define %VARPREFIX%workarray model_instance->workarray
%ENDIF%
%IF%%NUMBER_IMPORTS%
#define %VARPREFIX%%XX_EXT_IN_ARRAY_NAME% model_instance->%XX_EXT_IN_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_EXPORTS%
#define %VARPREFIX%%XX_EXT_OUT_ARRAY_NAME% model_instance->%XX_EXT_OUT_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_FAVORITE_PARAMETERS%
#define %VARPREFIX%%XX_FAVORITE_PARS_ARRAY_NAME% model_instance->%XX_FAVORITE_PARS_ARRAY_NAME%
%ENDIF%
%IF%%NUMBER_FAVORITE_VARIABLES%
#define %VARPREFIX%%XX_FAVORITE_VARS_ARRAY_NAME% model_instance->%XX_FAVORITE_VARS_ARRAY_NAME%
%ENDIF%

#define %VARPREFIX%%XX_TIME% model_instance->time
#define %VARPREFIX%step_size model_instance->step_size
#define %VARPREFIX%%XX_INITIALIZE% model_instance->%XX_INITIALIZE%
#define %VARPREFIX%major model_instance->major
#define %VARPREFIX%start_time model_instance->start_time
#define %VARPREFIX%finish_time model_instance->finish_time

/* Initialization methods */
XXBoolean %FUNCTIONPREFIX%ModelInstance_Constructor(%VARPREFIX%ModelInstance* model_instance,
													fmi2String instanceName,
													fmi2Type fmuType,
													fmi2String fmuResourceLocation,
													const fmi2CallbackFunctions *functions);
void %FUNCTIONPREFIX%ModelInitialize (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%ModelTerminate (%VARPREFIX%ModelInstance* model_instance);

/* Computation methods */
void %FUNCTIONPREFIX%CalculateInitial (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%CalculateStatic (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%CalculateInput (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%CalculateDynamic (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%CalculateOutput (%VARPREFIX%ModelInstance* model_instance);
void %FUNCTIONPREFIX%CalculateFinal (%VARPREFIX%ModelInstance* model_instance);

%IF%%NUMBEROF_DELAYFUNCTION%
/* delay methods */
void %FUNCTIONPREFIX%DelayUpdate (%VARPREFIX%ModelInstance* model_instance);
XXDouble %FUNCTIONPREFIX%ModelDelay (%VARPREFIX%ModelInstance* model_instance, XXDouble argument1, XXDouble argument2, XXInteger id);
#define XXDelay(arg1, arg2, id) %FUNCTIONPREFIX%ModelDelay(model_instance, arg1, arg2, id)

%ENDIF%
%IF%%NUMBEROF_INITIALFUNCTION%
XXDouble %FUNCTIONPREFIX%ModelInitialValue (%VARPREFIX%ModelInstance* model_instance, XXDouble argument, XXInteger identifier);
#define XXInitialValue(arg, id) %FUNCTIONPREFIX%ModelInitialValue(model_instance, arg, id)

%ENDIF%
%IF%%NUMBEROF_WARNSTATEMENT%
XXBoolean %FUNCTIONPREFIX%ModelWarning (%VARPREFIX%ModelInstance* model_instance, XXString message, XXInteger id);
#define XXWarning(message, id) %FUNCTIONPREFIX%ModelWarning(model_instance, message, id)
%ENDIF%
%IF%%NUMBEROF_STOPSTATEMENT%
XXBoolean %FUNCTIONPREFIX%ModelStopSimulation (%VARPREFIX%ModelInstance* model_instance, XXString message, XXInteger id);
#define XXStopSimulation(message, id) %FUNCTIONPREFIX%ModelStopSimulation(model_instance, message, id)
%ENDIF%

#endif
