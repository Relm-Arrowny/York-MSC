#include "dcsdemo_acc.h"
#include <string.h>
#include "rtwtypes.h"
#include "dcsdemo_acc_private.h"
#include "multiword_types.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T dcsdemo_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T
* tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T *
* uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = *
bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ; real_T * xBuf = ( NULL ) ;
int_T numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf = *
uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0
; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ;
real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf =
* uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr
) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer
* newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false
) ; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
uBufPtr = tempU ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
dcsdemo_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart ,
real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T
newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
void * S , void * diag ) { SimStruct * castedS = ( SimStruct * ) S ; if ( !
_ssIsErrorStatusAslErrMsg ( castedS ) ) { _ssSet_slErrMsg ( castedS , diag )
; } else { _ssDiscardDiagnostic ( castedS , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( void * S , void * diag ) {
_ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_3_26_0 ; B_dcsdemo_T *
_rtB ; DW_dcsdemo_T * _rtDW ; P_dcsdemo_T * _rtP ; X_dcsdemo_T * _rtX ;
real_T tmp [ 8 ] ; real_T tmp_1 [ 4 ] ; real_T tmp_4 [ 4 ] ; real_T tmp_0 [ 2
] ; real_T tmp_2 [ 2 ] ; real_T tmp_3 [ 2 ] ; int32_T i ; uint8_T rtb_B_3_2_0
; _rtDW = ( ( DW_dcsdemo_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_dcsdemo_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_dcsdemo_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_dcsdemo_T * ) _ssGetModelBlockIO ( S ) )
; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { memcpy ( & _rtB ->
B_3_0_0 [ 0 ] , & _rtP -> P_3 [ 0 ] , 12U * sizeof ( real_T ) ) ; } _rtB ->
B_3_1_0 [ 0 ] = _rtX -> Transfer_CSTATE [ 0 ] ; _rtB -> B_3_1_0 [ 1 ] = _rtX
-> Transfer_CSTATE [ 1 ] ; i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
rtb_B_3_2_0 = _rtDW -> Output_DSTATE ; _rtB -> B_3_3_0 = _rtB -> B_3_25_0 [
_rtDW -> Output_DSTATE ] ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 )
{ _rtB -> B_3_4_0 = _rtP -> P_5 ; } ssCallAccelRunBlock ( S , 3 , _rtDW ->
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ,
SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
ssCallAccelRunBlock ( S , 3 , 6 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB ->
B_3_7_0 [ 0 ] , & _rtDW -> last_x_PreviousInput [ 0 ] , 12U * sizeof ( real_T
) ) ; _rtB -> B_3_8_0 = _rtDW -> last_mv_DSTATE ; _rtB -> B_3_9_0 = _rtP ->
P_8 * _rtB -> B_3_3_0_k ; _rtB -> B_3_10_0 = _rtP -> P_9 * _rtB -> B_3_4_0_c
; _rtB -> B_3_11_0 = _rtP -> P_10 * _rtB -> B_3_20_0_m ; _rtB -> B_3_12_0 =
_rtP -> P_11 * _rtB -> B_3_21_0 ; _rtB -> B_3_13_0 = _rtP -> P_12 * _rtB ->
B_3_22_0 ; for ( i = 0 ; i < 10 ; i ++ ) { _rtB -> B_3_14_0_n [ i ] = _rtDW
-> Memory_PreviousInput [ i ] ; } ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_3_16_0 = _rtP -> P_13 * _rtB -> B_2_0_2 ;
ssCallAccelRunBlock ( S , 3 , 17 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 3 , 18 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB ->
B_3_19_0 [ 0 ] , & _rtP -> P_14 [ 0 ] , 24U * sizeof ( real_T ) ) ; memcpy (
& _rtB -> B_3_20_0 [ 0 ] , & _rtP -> P_15 [ 0 ] , 12U * sizeof ( real_T ) ) ;
} for ( i = 0 ; i < 2 ; i ++ ) { tmp [ i << 2 ] = _rtB -> B_3_19_0 [ ( (
int32_T ) _rtB -> B_0_0_0 [ i ] - 1 ) << 2 ] ; tmp [ ( i << 2 ) + 1 ] = _rtB
-> B_3_19_0 [ ( ( ( int32_T ) _rtB -> B_0_0_0 [ i ] - 1 ) << 2 ) + 1 ] ; tmp
[ ( i << 2 ) + 2 ] = _rtB -> B_3_19_0 [ ( ( ( int32_T ) _rtB -> B_0_0_0 [ i ]
- 1 ) << 2 ) + 2 ] ; tmp [ ( i << 2 ) + 3 ] = _rtB -> B_3_19_0 [ ( ( (
int32_T ) _rtB -> B_0_0_0 [ i ] - 1 ) << 2 ) + 3 ] ; tmp_0 [ i ] = _rtB ->
B_0_0_1 [ i ] ; tmp_1 [ i << 1 ] = _rtB -> B_3_20_0 [ ( ( int32_T ) _rtB ->
B_0_0_0 [ i ] - 1 ) << 1 ] ; tmp_1 [ ( i << 1 ) + 1 ] = _rtB -> B_3_20_0 [ (
( ( int32_T ) _rtB -> B_0_0_0 [ i ] - 1 ) << 1 ) + 1 ] ; tmp_2 [ i ] = _rtB
-> B_0_0_1 [ i ] ; tmp_3 [ i ] = _rtB -> B_3_1_0 [ i ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_16
; B_3_26_0 = dcsdemo_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer
, _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_17 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK . Head ] == ssGetT ( S ) )
) ) ; } for ( i = 0 ; i < 4 ; i ++ ) { tmp_4 [ i ] = tmp [ i + 4 ] * tmp_0 [
1 ] + tmp [ i ] * tmp_0 [ 0 ] ; } _rtB -> B_3_28_0 [ 0 ] = ( tmp_1 [ 0 ] *
tmp_2 [ 0 ] + tmp_2 [ 1 ] * tmp_1 [ 2 ] ) * B_3_26_0 + ( tmp_4 [ 0 ] * tmp_3
[ 0 ] + tmp_3 [ 1 ] * tmp_4 [ 2 ] ) ; _rtB -> B_3_28_0 [ 1 ] = ( tmp_2 [ 0 ]
* tmp_1 [ 1 ] + tmp_2 [ 1 ] * tmp_1 [ 3 ] ) * B_3_26_0 + ( tmp_3 [ 0 ] *
tmp_4 [ 1 ] + tmp_3 [ 1 ] * tmp_4 [ 3 ] ) ; i = ssIsSampleHit ( S , 3 , 0 ) ;
if ( i != 0 ) { rtb_B_3_2_0 = ( uint8_T ) ( ( uint32_T ) rtb_B_3_2_0 + _rtB
-> B_3_23_0 ) ; if ( rtb_B_3_2_0 > _rtP -> P_52 ) { _rtB -> B_3_30_0 = _rtB
-> B_3_24_0 ; } else { _rtB -> B_3_30_0 = rtb_B_3_2_0 ; } } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_c . TUbufferPtrs [ 0
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_18 ; _rtB -> B_3_31_0 = dcsdemo_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK_e . CircularBufSize , & _rtDW
-> TransportDelay_IWORK_e . Last , _rtDW -> TransportDelay_IWORK_e . Tail ,
_rtDW -> TransportDelay_IWORK_e . Head , _rtP -> P_19 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK_e .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK_e . Head ] == ssGetT ( S )
) ) ) ; } i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { rtb_B_3_2_0 = (
uint8_T ) ( ( uint32_T ) _rtDW -> Output_DSTATE_j + _rtB -> B_3_26_0 ) ; if (
rtb_B_3_2_0 > _rtP -> P_54 ) { _rtB -> B_3_35_0 = _rtB -> B_3_27_0 ; } else {
_rtB -> B_3_35_0 = rtb_B_3_2_0 ; } } UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID5 ( SimStruct * S , int_T tid ) { B_dcsdemo_T * _rtB ;
P_dcsdemo_T * _rtP ; _rtP = ( ( P_dcsdemo_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_dcsdemo_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB -> B_3_0_0_m = _rtP
-> P_23 ; _rtB -> B_3_1_0_c = _rtP -> P_24 ; _rtB -> B_3_2_0 = _rtP -> P_25 ;
_rtB -> B_3_3_0_k = _rtP -> P_26 ; _rtB -> B_3_4_0_c = _rtP -> P_27 ; _rtB ->
B_3_5_0 = _rtP -> P_28 ; _rtB -> B_3_7_0_b = _rtP -> P_29 ; _rtB -> B_3_9_0_p
= _rtP -> P_30 ; _rtB -> B_3_11_0_c = _rtP -> P_31 ; _rtB -> B_3_12_0_f =
_rtP -> P_32 ; _rtB -> B_3_13_0_g = _rtP -> P_33 ; _rtB -> B_3_14_0 = _rtP ->
P_34 ; _rtB -> B_3_15_0 = _rtP -> P_35 ; _rtB -> B_3_16_0_g = _rtP -> P_36 ;
_rtB -> B_3_17_0 = _rtP -> P_37 ; _rtB -> B_3_18_0 = _rtP -> P_38 ; _rtB ->
B_3_20_0_m = _rtP -> P_39 ; _rtB -> B_3_21_0 = _rtP -> P_40 ; _rtB ->
B_3_22_0 = _rtP -> P_41 ; _rtB -> B_3_23_0 = _rtP -> P_55 ; _rtB -> B_3_24_0
= _rtP -> P_56 ; memcpy ( & _rtB -> B_3_25_0 [ 0 ] , & _rtP -> P_42 [ 0 ] ,
13U * sizeof ( real_T ) ) ; _rtB -> B_3_26_0 = _rtP -> P_57 ; _rtB ->
B_3_27_0 = _rtP -> P_58 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_dcsdemo_T * _rtB ;
DW_dcsdemo_T * _rtDW ; P_dcsdemo_T * _rtP ; int32_T i ; _rtDW = ( (
DW_dcsdemo_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_dcsdemo_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_dcsdemo_T * ) _ssGetModelBlockIO ( S ) )
; i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { _rtDW -> Output_DSTATE =
_rtB -> B_3_30_0 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { memcpy
( & _rtDW -> last_x_PreviousInput [ 0 ] , & _rtB -> B_2_0_1 [ 0 ] , 12U *
sizeof ( real_T ) ) ; _rtDW -> last_mv_DSTATE = _rtB -> B_2_0_2 ; for ( i = 0
; i < 10 ; i ++ ) { _rtDW -> Memory_PreviousInput [ i ] = _rtB -> B_2_0_9 [ i
] ; } } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK
. TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW ->
TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK . Head < (
_rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
dcsdemo_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Tail , & _rtDW ->
TransportDelay_IWORK . Head , & _rtDW -> TransportDelay_IWORK . Last ,
simTime - _rtP -> P_16 , uBuffer , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
TransportDelay_IWORK . CircularBufSize ) [ _rtDW -> TransportDelay_IWORK .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
_rtB -> B_3_16_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_c . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_e . Head = ( ( _rtDW -> TransportDelay_IWORK_e
. Head < ( _rtDW -> TransportDelay_IWORK_e . CircularBufSize - 1 ) ) ? (
_rtDW -> TransportDelay_IWORK_e . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_e . Head == _rtDW -> TransportDelay_IWORK_e . Tail ) {
if ( ! dcsdemo_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK_e . CircularBufSize , & _rtDW -> TransportDelay_IWORK_e
. Tail , & _rtDW -> TransportDelay_IWORK_e . Head , & _rtDW ->
TransportDelay_IWORK_e . Last , simTime - _rtP -> P_18 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_e . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_e . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_e . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_e . Head ] = 0.0 ; } i = ssIsSampleHit ( S , 4 , 0 ) ;
if ( i != 0 ) { _rtDW -> Output_DSTATE_j = _rtB -> B_3_35_0 ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID5 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_dcsdemo_T * _rtB ;
P_dcsdemo_T * _rtP ; XDot_dcsdemo_T * _rtXdot ; X_dcsdemo_T * _rtX ; uint32_T
ri ; _rtXdot = ( ( XDot_dcsdemo_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_dcsdemo_T * ) ssGetContStates ( S ) ) ; _rtP = ( ( P_dcsdemo_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_dcsdemo_T * ) _ssGetModelBlockIO ( S ) )
; _rtXdot -> Transfer_CSTATE [ 0 ] = _rtB -> B_3_28_0 [ 0 ] ; _rtXdot ->
Internal_CSTATE [ 0 ] = 0.0 ; _rtXdot -> Transfer_CSTATE [ 1 ] = _rtB ->
B_3_28_0 [ 1 ] ; _rtXdot -> Internal_CSTATE [ 1 ] = 0.0 ; for ( ri = _rtP ->
P_44 [ 0U ] ; ri < _rtP -> P_44 [ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE
[ _rtP -> P_43 [ ri ] ] += _rtP -> P_20 [ ri ] * _rtX -> Internal_CSTATE [ 0U
] ; } for ( ri = _rtP -> P_44 [ 1U ] ; ri < _rtP -> P_44 [ 2U ] ; ri ++ ) {
_rtXdot -> Internal_CSTATE [ _rtP -> P_43 [ ri ] ] += _rtP -> P_20 [ ri ] *
_rtX -> Internal_CSTATE [ 1U ] ; } for ( ri = _rtP -> P_46 [ 0U ] ; ri < _rtP
-> P_46 [ 1U ] ; ri ++ ) { _rtXdot -> Internal_CSTATE [ _rtP -> P_45 [ ri ] ]
+= _rtP -> P_21 [ ri ] * _rtB -> B_3_31_0 ; } } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3750796624U
) ; ssSetChecksumVal ( S , 1 , 4228202574U ) ; ssSetChecksumVal ( S , 2 ,
327808828U ) ; ssSetChecksumVal ( S , 3 , 710407112U ) ; { mxArray *
slVerStructMat = ( NULL ) ; mxArray * slStrMat = mxCreateString ( "simulink"
) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat
, 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.6" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_dcsdemo_T ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof ( DW_dcsdemo_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } if ( ssGetSizeofGlobalBlockIO ( S ) != (
SLSize ) sizeof ( B_dcsdemo_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof ( B_dcsdemo_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } { int ssSizeofParams ; ssGetSizeofParams ( S
, & ssSizeofParams ) ; if ( ssSizeofParams != sizeof ( P_dcsdemo_T ) ) {
static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_dcsdemo_T ) ) ; ssSetErrorStatus ( S , msg ) ; } }
_ssSetModelRtp ( S , ( real_T * ) & dcsdemo_rtDefaultP ) ; rt_InitInfAndNaN (
sizeof ( real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S
) { { SimStruct * childS ; SysOutputFcn * callSysFcns ; childS =
ssGetSFunction ( S , 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; }
slAccRegPrmChangeFcn ( S , mdlOutputsTID5 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
