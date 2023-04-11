#ifndef RTW_HEADER_basic_acc_h_
#define RTW_HEADER_basic_acc_h_
#ifndef basic_acc_COMMON_INCLUDES_
#define basic_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "basic_acc_types.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_2_1_0 [ 12 ] ; real_T B_2_2_0 ; real_T B_2_6_1 ;
real_T B_2_8_0 [ 2 ] ; real_T B_2_9_0 [ 2 ] ; real_T B_2_10_0 ; real_T
B_2_12_0 ; real_T B_2_13_0 ; real_T B_2_14_0 ; real_T B_2_15_0 ; real_T
B_2_16_0 ; real_T B_2_17_0 ; real_T B_2_20_0 ; real_T B_2_25_0 [ 4 ] ; real_T
B_2_26_0 [ 2 ] ; real_T B_2_27_0 [ 2 ] ; real_T B_2_28_0 ; real_T B_2_29_0 [
2 ] ; real_T B_2_30_0 [ 2 ] ; real_T B_2_0_0 ; real_T B_2_1_0_m ; real_T
B_2_2_0_c ; real_T B_2_4_0 ; real_T B_2_6_0 ; real_T B_2_8_0_k ; real_T
B_2_9_0_c ; real_T B_2_10_0_b ; real_T B_2_11_0 ; real_T B_2_12_0_p ; real_T
B_2_13_0_c ; real_T B_2_14_0_f ; real_T B_2_15_0_g ; real_T B_2_17_0_g ;
real_T B_2_18_0 ; real_T B_2_19_0 ; real_T B_2_22_0 [ 6 ] ; real_T B_2_25_0_m
[ 6 ] ; real_T B_1_0_1 [ 12 ] ; real_T B_1_0_2 ; real_T B_1_0_3 ; real_T
B_1_0_4 [ 21 ] ; real_T B_1_0_5 [ 252 ] ; real_T B_1_0_6 [ 21 ] ; real_T
B_1_0_7 ; real_T B_1_0_8 [ 12 ] ; uint32_T B_2_6_0_n ; uint32_T B_0_0_0 ;
uint8_T B_2_32_0 ; uint8_T B_2_34_0 ; uint8_T B_2_20_0_p ; uint8_T B_2_21_0 ;
uint8_T B_2_23_0 ; uint8_T B_2_24_0 ; boolean_T B_2_18_0_l [ 10 ] ; boolean_T
B_1_0_9 [ 10 ] ; char_T pad_B_1_0_9 [ 6 ] ; } B_basic_T ; typedef struct {
real_T Delay_DSTATE [ 2 ] ; real_T last_mv_DSTATE ; real_T
last_x_PreviousInput [ 12 ] ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; void * u_PWORK ; void * y_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; int32_T optimizer_sysIdxToRun ;
int32_T RegularNN_sysIdxToRun ; uint32_T Prelookup1_DWORK1 ; struct { int_T
Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize
; } TransportDelay_IWORK ; uint8_T Output_DSTATE ; uint8_T Output_DSTATE_c ;
boolean_T Memory_PreviousInput [ 10 ] ; char_T pad_Memory_PreviousInput [ 4 ]
; } DW_basic_T ; typedef struct { real_T Transfer_CSTATE [ 2 ] ; } X_basic_T
; typedef struct { real_T Transfer_CSTATE [ 2 ] ; } XDot_basic_T ; typedef
struct { boolean_T Transfer_CSTATE [ 2 ] ; } XDis_basic_T ; typedef struct {
real_T Transfer_CSTATE [ 2 ] ; } CStateAbsTol_basic_T ; typedef struct {
real_T Transfer_CSTATE [ 2 ] ; } CXPtMin_basic_T ; typedef struct { real_T
Transfer_CSTATE [ 2 ] ; } CXPtMax_basic_T ; typedef struct { real_T
optimizer_A_Size [ 2 ] ; real_T optimizer_A [ 144 ] ; real_T
optimizer_Ac_Size [ 2 ] ; real_T optimizer_Ac [ 60 ] ; real_T
optimizer_Bu_Size [ 2 ] ; real_T optimizer_Bu [ 12 ] ; real_T
optimizer_Bv_Size [ 2 ] ; real_T pooled1 [ 12 ] ; real_T optimizer_C_Size [ 2
] ; real_T optimizer_C [ 12 ] ; real_T optimizer_Dv_Size [ 2 ] ; real_T
pooled2 ; real_T optimizer_H_Size [ 2 ] ; real_T optimizer_H [ 36 ] ; real_T
optimizer_Hinv_Size [ 2 ] ; real_T optimizer_Hinv [ 36 ] ; real_T
optimizer_I1_Size [ 2 ] ; real_T optimizer_I1 [ 20 ] ; real_T
optimizer_Kr_Size [ 2 ] ; real_T optimizer_Kr [ 100 ] ; real_T
optimizer_Ku1_Size [ 2 ] ; real_T optimizer_Ku1 [ 5 ] ; real_T
optimizer_Kut_Size [ 2 ] ; real_T optimizer_Kut [ 100 ] ; real_T
optimizer_Kv_Size [ 2 ] ; real_T optimizer_Kv [ 105 ] ; real_T
optimizer_Kx_Size [ 2 ] ; real_T optimizer_Kx [ 60 ] ; real_T
optimizer_L_Size [ 2 ] ; real_T optimizer_L [ 12 ] ; real_T
optimizer_Linv_Size [ 2 ] ; real_T optimizer_Linv [ 36 ] ; real_T
optimizer_M_Size [ 2 ] ; real_T optimizer_M [ 12 ] ; real_T
optimizer_Mdis_Size [ 2 ] ; real_T optimizer_Mdis [ 25 ] ; real_T
optimizer_Mlim_Size [ 2 ] ; real_T optimizer_Mlim [ 10 ] ; real_T
optimizer_Mu1_Size [ 2 ] ; real_T optimizer_Mu1 [ 10 ] ; real_T
optimizer_Mv_Size [ 2 ] ; real_T optimizer_Mv [ 210 ] ; real_T
optimizer_Mx_Size [ 2 ] ; real_T optimizer_Mx [ 120 ] ; real_T
optimizer_RMDscale_Size [ 2 ] ; real_T pooled3 ; real_T optimizer_Vdis_Size [
2 ] ; real_T optimizer_Vdis [ 505 ] ; real_T optimizer_utarget_Size [ 2 ] ;
real_T optimizer_utarget [ 20 ] ; real_T optimizer_Mrows_Size [ 2 ] ; int32_T
optimizer_Mrows [ 10 ] ; real_T optimizer_Ndis_Size [ 2 ] ; int32_T
optimizer_Ndis [ 5 ] ; char pad_optimizer_Ndis [ 4 ] ; real_T
optimizer_degrees_Size [ 2 ] ; int32_T optimizer_degrees ; char
pad_optimizer_degrees [ 4 ] ; real_T optimizer_enable_value_Size [ 2 ] ;
int32_T pooled4 ; char pad_pooled4 [ 4 ] ; real_T optimizer_m_Size [ 2 ] ;
int32_T pooled5 ; char pad_pooled5 [ 4 ] ; real_T optimizer_maxdis_Size [ 2 ]
; int32_T optimizer_maxdis ; char pad_optimizer_maxdis [ 4 ] ; real_T
optimizer_myindex_Size [ 2 ] ; int32_T pooled6 ; char pad_pooled6 [ 4 ] ;
real_T optimizer_nx_Size [ 2 ] ; int32_T pooled7 ; char pad_pooled7 [ 4 ] ;
real_T optimizer_p_Size [ 2 ] ; int32_T optimizer_p ; char pad_optimizer_p [
4 ] ; real_T optimizer_CustomEstimation_Size [ 2 ] ; boolean_T pooled8 ; char
pad_pooled8 [ 7 ] ; real_T optimizer_UseActiveSetSolver_Size [ 2 ] ;
boolean_T pooled9 ; char pad_pooled9 [ 7 ] ; } ConstP_basic_T ; struct
P_basic_T_ { real_T P_0 ; real_T P_1 [ 12 ] ; real_T P_2 ; real_T P_3 [ 12 ]
; real_T P_4 [ 6 ] ; real_T P_5 [ 2 ] ; real_T P_6 ; real_T P_7 ; real_T P_8
; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 [ 24 ] ; real_T P_13 [
12 ] ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ;
real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T
P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ;
real_T P_30 ; real_T P_31 ; real_T P_32 [ 6 ] ; real_T P_33 [ 6 ] ; boolean_T
P_34 [ 10 ] ; uint8_T P_35 ; uint8_T P_36 ; uint8_T P_37 ; uint8_T P_38 ;
uint8_T P_39 ; uint8_T P_40 ; uint8_T P_41 ; uint8_T P_42 ; uint8_T P_43 ;
char_T pad_P_43 [ 5 ] ; } ; extern P_basic_T basic_rtDefaultP ; extern const
ConstP_basic_T basic_rtConstP ;
#endif
