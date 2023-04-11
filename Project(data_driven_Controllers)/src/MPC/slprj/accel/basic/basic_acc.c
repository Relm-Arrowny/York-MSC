#include "basic_acc.h"
#include "rtwtypes.h"
#include <string.h>
#include "basic_acc_private.h"
#include "basic_acc_types.h"
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
static void basic_oorCheck ( uint8_T diagSetting , real_T u , real_T bp0 ,
real_T bpn , const char_T * extrapMsgId , const char_T * blockPath ,
SimStruct * S ) ;
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T basic_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T *
tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * *
uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
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
basic_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T
* uBuf , int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx ,
real_T initOutput , boolean_T discrete , boolean_T
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
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } uint32_T plook_lincpa ( real_T
u , const real_T bp [ ] , uint32_T maxIndex , real_T * fraction , uint32_T *
prevIndex ) { uint32_T bpIndex ; if ( u <= bp [ 0U ] ) { bpIndex = 0U ; *
fraction = 0.0 ; } else if ( u < bp [ maxIndex ] ) { bpIndex = linsearch_u32d
( u , bp , * prevIndex ) ; * fraction = ( u - bp [ bpIndex ] ) / ( bp [
bpIndex + 1U ] - bp [ bpIndex ] ) ; } else { bpIndex = maxIndex ; * fraction
= 0.0 ; } * prevIndex = bpIndex ; return bpIndex ; } uint32_T linsearch_u32d
( real_T u , const real_T bp [ ] , uint32_T startIndex ) { uint32_T bpIndex ;
for ( bpIndex = startIndex ; u < bp [ bpIndex ] ; bpIndex -- ) { } while ( u
>= bp [ bpIndex + 1U ] ) { bpIndex ++ ; } return bpIndex ; } void
rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * *
path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( void * S , void * diag ) { SimStruct * castedS = (
SimStruct * ) S ; if ( ! _ssIsErrorStatusAslErrMsg ( castedS ) ) {
_ssSet_slErrMsg ( castedS , diag ) ; } else { _ssDiscardDiagnostic ( castedS
, diag ) ; } } void rt_ssReportDiagnosticAsWarning ( void * S , void * diag )
{ _ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
basic_oorCheck ( uint8_T diagSetting , real_T u , real_T bp0 , real_T bpn ,
const char_T * extrapMsgId , const char_T * blockPath , SimStruct * S ) {
SimStruct * S_0 ; void * diag ; if ( ( diagSetting != 0 ) && ( ( u < bp0 ) ||
( u > bpn ) ) ) { if ( diagSetting == 2 ) { S_0 = S ; diag =
CreateDiagnosticAsVoidPtr ( "Simulink:blocks:PreLookupOutofRangeInputError" ,
1 , 3 , blockPath ) ; rt_ssSet_slErrMsg ( S_0 , diag ) ; } else { S_0 = S ;
diag = CreateDiagnosticAsVoidPtr ( extrapMsgId , 1 , 3 , blockPath ) ;
rt_ssReportDiagnosticAsWarning ( S_0 , diag ) ; } } } static void mdlOutputs
( SimStruct * S , int_T tid ) { B_basic_T * _rtB ; DW_basic_T * _rtDW ;
P_basic_T * _rtP ; X_basic_T * _rtX ; real_T rtb_B_2_3_0 [ 12 ] ; real_T
rtb_B_2_5_0 ; int32_T i ; uint8_T rtb_B_2_11_0 ; uint8_T rtb_B_2_4_0 ; _rtDW
= ( ( DW_basic_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( ( X_basic_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_basic_T * ) ssGetModelRtp ( S ) ) ;
_rtB = ( ( B_basic_T * ) _ssGetModelBlockIO ( S ) ) ; i = ssIsSampleHit ( S ,
2 , 0 ) ; if ( i != 0 ) { memcpy ( & _rtB -> B_2_1_0 [ 0 ] , & _rtDW ->
last_x_PreviousInput [ 0 ] , 12U * sizeof ( real_T ) ) ; _rtB -> B_2_2_0 =
_rtDW -> last_mv_DSTATE ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
memcpy ( & rtb_B_2_3_0 [ 0 ] , & _rtP -> P_3 [ 0 ] , 12U * sizeof ( real_T )
) ; } i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_2_4_0 = _rtDW
-> Output_DSTATE ; if ( ssIsMajorTimeStep ( S ) != 0 ) { rtb_B_2_5_0 = _rtB
-> B_2_25_0_m [ _rtDW -> Output_DSTATE ] ; } else { if ( _rtDW ->
Output_DSTATE > 5 ) { i = 5 ; } else { i = _rtDW -> Output_DSTATE ; }
rtb_B_2_5_0 = _rtB -> B_2_25_0_m [ i ] ; } basic_oorCheck ( _rtP -> P_36 ,
rtb_B_2_5_0 , _rtP -> P_4 [ 0 ] , _rtP -> P_4 [ 5 ] ,
"Simulink:blocks:PreLookupOutofRangeInputWarn_Clip" ,
"basic/LPV System/Prelookup1" , S ) ; _rtB -> B_2_6_0_n = plook_lincpa (
rtb_B_2_5_0 , _rtP -> P_4 , 5U , & _rtB -> B_2_6_1 , & _rtDW ->
Prelookup1_DWORK1 ) ; ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_OUTPUTS )
; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_2_8_0 [ 0 ] =
rtb_B_2_3_0 [ ( ( int32_T ) _rtB -> B_0_0_0 - 1 ) << 1 ] ; _rtB -> B_2_8_0 [
1 ] = rtb_B_2_3_0 [ ( ( ( int32_T ) _rtB -> B_0_0_0 - 1 ) << 1 ) + 1 ] ; }
_rtB -> B_2_9_0 [ 0 ] = _rtX -> Transfer_CSTATE [ 0 ] ; _rtB -> B_2_9_0 [ 1 ]
= _rtX -> Transfer_CSTATE [ 1 ] ; _rtB -> B_2_10_0 = _rtB -> B_2_8_0 [ 0 ] *
_rtB -> B_2_9_0 [ 0 ] + _rtB -> B_2_8_0 [ 1 ] * _rtB -> B_2_9_0 [ 1 ] ; i =
ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) { rtb_B_2_11_0 = _rtDW ->
Output_DSTATE_c ; if ( ssIsMajorTimeStep ( S ) != 0 ) { _rtB -> B_2_12_0 =
_rtB -> B_2_22_0 [ _rtDW -> Output_DSTATE_c ] ; } else { if ( _rtDW ->
Output_DSTATE_c > 5 ) { i = 5 ; } else { i = _rtDW -> Output_DSTATE_c ; }
_rtB -> B_2_12_0 = _rtB -> B_2_22_0 [ i ] ; } } i = ssIsSampleHit ( S , 2 , 0
) ; if ( i != 0 ) { _rtB -> B_2_13_0 = _rtP -> P_6 * _rtB -> B_2_0_0 ; _rtB
-> B_2_14_0 = _rtP -> P_7 * _rtB -> B_2_1_0_m ; _rtB -> B_2_15_0 = _rtP ->
P_8 * _rtB -> B_2_17_0_g ; _rtB -> B_2_16_0 = _rtP -> P_9 * _rtB -> B_2_18_0
; _rtB -> B_2_17_0 = _rtP -> P_10 * _rtB -> B_2_19_0 ; for ( i = 0 ; i < 10 ;
i ++ ) { _rtB -> B_2_18_0_l [ i ] = _rtDW -> Memory_PreviousInput [ i ] ; }
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_2_20_0 =
_rtP -> P_11 * _rtB -> B_1_0_2 ; ssCallAccelRunBlock ( S , 2 , 21 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 2 , 22 ,
SS_CALL_MDL_OUTPUTS ) ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) {
_rtB -> B_2_25_0 [ 0 ] = _rtP -> P_12 [ ( ( int32_T ) _rtB -> B_0_0_0 - 1 )
<< 2 ] ; _rtB -> B_2_25_0 [ 1 ] = _rtP -> P_12 [ ( ( ( int32_T ) _rtB ->
B_0_0_0 - 1 ) << 2 ) + 1 ] ; _rtB -> B_2_25_0 [ 2 ] = _rtP -> P_12 [ ( ( (
int32_T ) _rtB -> B_0_0_0 - 1 ) << 2 ) + 2 ] ; _rtB -> B_2_25_0 [ 3 ] = _rtP
-> P_12 [ ( ( ( int32_T ) _rtB -> B_0_0_0 - 1 ) << 2 ) + 3 ] ; _rtB ->
B_2_26_0 [ 0 ] = _rtP -> P_13 [ ( ( int32_T ) _rtB -> B_0_0_0 - 1 ) << 1 ] ;
_rtB -> B_2_26_0 [ 1 ] = _rtP -> P_13 [ ( ( ( int32_T ) _rtB -> B_0_0_0 - 1 )
<< 1 ) + 1 ] ; } _rtB -> B_2_27_0 [ 0 ] = 0.0 ; _rtB -> B_2_27_0 [ 0 ] +=
_rtB -> B_2_25_0 [ 0 ] * _rtB -> B_2_9_0 [ 0 ] ; _rtB -> B_2_27_0 [ 0 ] +=
_rtB -> B_2_9_0 [ 1 ] * _rtB -> B_2_25_0 [ 2 ] ; _rtB -> B_2_27_0 [ 1 ] = 0.0
; _rtB -> B_2_27_0 [ 1 ] += _rtB -> B_2_9_0 [ 0 ] * _rtB -> B_2_25_0 [ 1 ] ;
_rtB -> B_2_27_0 [ 1 ] += _rtB -> B_2_9_0 [ 1 ] * _rtB -> B_2_25_0 [ 3 ] ; {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_14 ; _rtB -> B_2_28_0 = basic_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_15 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW
-> TransportDelay_IWORK . CircularBufSize ) [ _rtDW -> TransportDelay_IWORK .
Head ] == ssGetT ( S ) ) ) ) ; } _rtB -> B_2_29_0 [ 0 ] = _rtB -> B_2_26_0 [
0 ] * _rtB -> B_2_28_0 ; _rtB -> B_2_30_0 [ 0 ] = _rtB -> B_2_27_0 [ 0 ] +
_rtB -> B_2_29_0 [ 0 ] ; _rtB -> B_2_29_0 [ 1 ] = _rtB -> B_2_26_0 [ 1 ] *
_rtB -> B_2_28_0 ; _rtB -> B_2_30_0 [ 1 ] = _rtB -> B_2_27_0 [ 1 ] + _rtB ->
B_2_29_0 [ 1 ] ; i = ssIsSampleHit ( S , 3 , 0 ) ; if ( i != 0 ) {
rtb_B_2_11_0 = ( uint8_T ) ( ( uint32_T ) rtb_B_2_11_0 + _rtB -> B_2_20_0_p )
; if ( rtb_B_2_11_0 > _rtP -> P_38 ) { _rtB -> B_2_32_0 = _rtB -> B_2_21_0 ;
} else { _rtB -> B_2_32_0 = rtb_B_2_11_0 ; } rtb_B_2_4_0 = ( uint8_T ) ( (
uint32_T ) rtb_B_2_4_0 + _rtB -> B_2_23_0 ) ; if ( rtb_B_2_4_0 > _rtP -> P_39
) { _rtB -> B_2_34_0 = _rtB -> B_2_24_0 ; } else { _rtB -> B_2_34_0 =
rtb_B_2_4_0 ; } } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID4 (
SimStruct * S , int_T tid ) { B_basic_T * _rtB ; P_basic_T * _rtP ; int32_T i
; _rtP = ( ( P_basic_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_basic_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_2_0_0 = _rtP -> P_16 ; _rtB ->
B_2_1_0_m = _rtP -> P_17 ; _rtB -> B_2_2_0_c = _rtP -> P_18 ; _rtB -> B_2_4_0
= _rtP -> P_19 ; _rtB -> B_2_6_0 = _rtP -> P_20 ; _rtB -> B_2_8_0_k = _rtP ->
P_21 ; _rtB -> B_2_9_0_c = _rtP -> P_22 ; _rtB -> B_2_10_0_b = _rtP -> P_23 ;
_rtB -> B_2_11_0 = _rtP -> P_24 ; _rtB -> B_2_12_0_p = _rtP -> P_25 ; _rtB ->
B_2_13_0_c = _rtP -> P_26 ; _rtB -> B_2_14_0_f = _rtP -> P_27 ; _rtB ->
B_2_15_0_g = _rtP -> P_28 ; _rtB -> B_2_17_0_g = _rtP -> P_29 ; _rtB ->
B_2_18_0 = _rtP -> P_30 ; _rtB -> B_2_19_0 = _rtP -> P_31 ; _rtB ->
B_2_20_0_p = _rtP -> P_40 ; _rtB -> B_2_21_0 = _rtP -> P_41 ; _rtB ->
B_2_23_0 = _rtP -> P_42 ; _rtB -> B_2_24_0 = _rtP -> P_43 ; for ( i = 0 ; i <
6 ; i ++ ) { _rtB -> B_2_22_0 [ i ] = _rtP -> P_32 [ i ] ; _rtB -> B_2_25_0_m
[ i ] = _rtP -> P_33 [ i ] ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_basic_T * _rtB ;
DW_basic_T * _rtDW ; P_basic_T * _rtP ; int32_T i ; _rtDW = ( ( DW_basic_T *
) ssGetRootDWork ( S ) ) ; _rtP = ( ( P_basic_T * ) ssGetModelRtp ( S ) ) ;
_rtB = ( ( B_basic_T * ) _ssGetModelBlockIO ( S ) ) ; i = ssIsSampleHit ( S ,
2 , 0 ) ; if ( i != 0 ) { _rtDW -> Delay_DSTATE [ 0U ] = _rtDW ->
Delay_DSTATE [ 1U ] ; _rtDW -> Delay_DSTATE [ 1 ] = 0.0 ; memcpy ( & _rtDW ->
last_x_PreviousInput [ 0 ] , & _rtB -> B_1_0_1 [ 0 ] , 12U * sizeof ( real_T
) ) ; _rtDW -> last_mv_DSTATE = _rtB -> B_1_0_2 ; } i = ssIsSampleHit ( S , 3
, 0 ) ; if ( i != 0 ) { _rtDW -> Output_DSTATE = _rtB -> B_2_34_0 ; _rtDW ->
Output_DSTATE_c = _rtB -> B_2_32_0 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if (
i != 0 ) { for ( i = 0 ; i < 10 ; i ++ ) { _rtDW -> Memory_PreviousInput [ i
] = _rtB -> B_1_0_9 [ i ] ; } } { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S )
; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
basic_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Tail , & _rtDW ->
TransportDelay_IWORK . Head , & _rtDW -> TransportDelay_IWORK . Last ,
simTime - _rtP -> P_14 , uBuffer , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
TransportDelay_IWORK . CircularBufSize ) [ _rtDW -> TransportDelay_IWORK .
Head ] = simTime ; ( * uBuffer ) [ _rtDW -> TransportDelay_IWORK . Head ] =
_rtB -> B_2_20_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID4 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_basic_T * _rtB ;
XDot_basic_T * _rtXdot ; _rtXdot = ( ( XDot_basic_T * ) ssGetdX ( S ) ) ;
_rtB = ( ( B_basic_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Transfer_CSTATE [ 0 ] = _rtB -> B_2_30_0 [ 0 ] ; _rtXdot -> Transfer_CSTATE [
1 ] = _rtB -> B_2_30_0 [ 1 ] ; } static void mdlInitializeSizes ( SimStruct *
S ) { ssSetChecksumVal ( S , 0 , 677598940U ) ; ssSetChecksumVal ( S , 1 ,
1688635401U ) ; ssSetChecksumVal ( S , 2 , 2051433051U ) ; ssSetChecksumVal (
S , 3 , 1421229042U ) ; { mxArray * slVerStructMat = ( NULL ) ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == ( NULL ) ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "10.6" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != ( SLSize )
sizeof ( DW_basic_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof ( DW_basic_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } if ( ssGetSizeofGlobalBlockIO ( S ) != (
SLSize ) sizeof ( B_basic_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof ( B_basic_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } { int ssSizeofParams ; ssGetSizeofParams ( S
, & ssSizeofParams ) ; if ( ssSizeofParams != sizeof ( P_basic_T ) ) { static
char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_basic_T ) ) ; ssSetErrorStatus ( S , msg ) ; } }
_ssSetModelRtp ( S , ( real_T * ) & basic_rtDefaultP ) ; rt_InitInfAndNaN (
sizeof ( real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S
) { { SimStruct * childS ; SysOutputFcn * callSysFcns ; childS =
ssGetSFunction ( S , 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; }
slAccRegPrmChangeFcn ( S , mdlOutputsTID4 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
