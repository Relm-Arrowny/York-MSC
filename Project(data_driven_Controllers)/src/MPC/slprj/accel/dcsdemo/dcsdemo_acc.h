#ifndef RTW_HEADER_dcsdemo_acc_h_
#define RTW_HEADER_dcsdemo_acc_h_
#ifndef dcsdemo_acc_COMMON_INCLUDES_
#define dcsdemo_acc_COMMON_INCLUDES_
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
#include "dcsdemo_acc_types.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_3_0_0 [ 12 ] ; real_T B_3_1_0 [ 2 ] ; real_T
B_3_3_0 ; real_T B_3_4_0 ; real_T B_3_7_0 [ 12 ] ; real_T B_3_8_0 ; real_T
B_3_9_0 ; real_T B_3_10_0 ; real_T B_3_11_0 ; real_T B_3_12_0 ; real_T
B_3_13_0 ; real_T B_3_16_0 ; real_T B_3_19_0 [ 24 ] ; real_T B_3_20_0 [ 12 ]
; real_T B_3_28_0 [ 2 ] ; real_T B_3_31_0 ; real_T B_3_0_0_m ; real_T
B_3_1_0_c ; real_T B_3_2_0 ; real_T B_3_3_0_k ; real_T B_3_4_0_c ; real_T
B_3_5_0 ; real_T B_3_7_0_b ; real_T B_3_9_0_p ; real_T B_3_11_0_c ; real_T
B_3_12_0_f ; real_T B_3_13_0_g ; real_T B_3_14_0 ; real_T B_3_15_0 ; real_T
B_3_16_0_g ; real_T B_3_17_0 ; real_T B_3_18_0 ; real_T B_3_20_0_m ; real_T
B_3_21_0 ; real_T B_3_22_0 ; real_T B_3_25_0 [ 13 ] ; real_T B_2_0_1 [ 12 ] ;
real_T B_2_0_2 ; real_T B_2_0_3 ; real_T B_2_0_4 [ 21 ] ; real_T B_2_0_5 [
252 ] ; real_T B_2_0_6 [ 21 ] ; real_T B_2_0_7 ; real_T B_2_0_8 [ 12 ] ;
real_T B_1_0_0 ; real_T B_1_1_0 ; real_T B_1_2_0 ; real_T B_1_3_0 ; real_T
B_1_4_1 ; real_T B_1_6_0 [ 4 ] ; real_T B_1_7_0 [ 2 ] ; real_T B_1_8_0 ;
real_T B_0_0_1 [ 2 ] ; uint32_T B_1_4_0 ; uint32_T B_0_0_0 [ 2 ] ; uint8_T
B_3_30_0 ; uint8_T B_3_35_0 ; uint8_T B_3_23_0 ; uint8_T B_3_24_0 ; uint8_T
B_3_26_0 ; uint8_T B_3_27_0 ; boolean_T B_3_14_0_n [ 10 ] ; boolean_T B_2_0_9
[ 10 ] ; char_T pad_B_2_0_9 [ 2 ] ; } B_dcsdemo_T ; typedef struct { real_T
last_mv_DSTATE ; real_T last_x_PreviousInput [ 12 ] ; struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay_RWORK_n ; void * Scope_PWORK [ 2 ] ; void * u_PWORK ; void *
y_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_c ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_AlgLoopData ; int32_T
optimizer_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_sysIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_blkIdxToRun ; int32_T
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Task_0_parentSysIdxToRun ;
int32_T RegularOrthotope_sysIdxToRun ; uint32_T Prelookup1_DWORK1 ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_e ; uint8_T Output_DSTATE ; uint8_T Output_DSTATE_j ;
boolean_T Memory_PreviousInput [ 10 ] ; char_T pad_Memory_PreviousInput [ 4 ]
; } DW_dcsdemo_T ; typedef struct { real_T Transfer_CSTATE [ 2 ] ; real_T
Internal_CSTATE [ 2 ] ; } X_dcsdemo_T ; typedef struct { real_T
Transfer_CSTATE [ 2 ] ; real_T Internal_CSTATE [ 2 ] ; } XDot_dcsdemo_T ;
typedef struct { boolean_T Transfer_CSTATE [ 2 ] ; boolean_T Internal_CSTATE
[ 2 ] ; } XDis_dcsdemo_T ; typedef struct { real_T optimizer_A_Size [ 2 ] ;
real_T optimizer_A [ 144 ] ; real_T optimizer_Ac_Size [ 2 ] ; real_T
optimizer_Ac [ 60 ] ; real_T optimizer_Bu_Size [ 2 ] ; real_T optimizer_Bu [
12 ] ; real_T optimizer_Bv_Size [ 2 ] ; real_T pooled1 [ 12 ] ; real_T
optimizer_C_Size [ 2 ] ; real_T optimizer_C [ 12 ] ; real_T optimizer_Dv_Size
[ 2 ] ; real_T pooled2 ; real_T optimizer_H_Size [ 2 ] ; real_T optimizer_H [
36 ] ; real_T optimizer_Hinv_Size [ 2 ] ; real_T optimizer_Hinv [ 36 ] ;
real_T optimizer_I1_Size [ 2 ] ; real_T optimizer_I1 [ 20 ] ; real_T
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
boolean_T pooled9 ; char pad_pooled9 [ 7 ] ; } ConstP_dcsdemo_T ; struct
P_dcsdemo_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 [ 6 ] ; real_T P_3 [ 12 ]
; real_T P_4 [ 2 ] ; real_T P_5 ; real_T P_6 [ 12 ] ; real_T P_7 ; real_T P_8
; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T
P_14 [ 24 ] ; real_T P_15 [ 12 ] ; real_T P_16 ; real_T P_17 ; real_T P_18 ;
real_T P_19 ; real_T P_20 [ 4 ] ; real_T P_21 [ 2 ] ; real_T P_22 [ 2 ] ;
real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T
P_28 ; real_T P_29 ; real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ;
real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T
P_39 ; real_T P_40 ; real_T P_41 ; real_T P_42 [ 13 ] ; uint32_T P_43 [ 4 ] ;
uint32_T P_44 [ 3 ] ; uint32_T P_45 [ 2 ] ; uint32_T P_46 [ 2 ] ; uint32_T
P_47 [ 2 ] ; uint32_T P_48 [ 3 ] ; boolean_T P_49 [ 10 ] ; uint8_T P_50 ;
uint8_T P_51 ; uint8_T P_52 ; uint8_T P_53 ; uint8_T P_54 ; uint8_T P_55 ;
uint8_T P_56 ; uint8_T P_57 ; uint8_T P_58 ; char_T pad_P_58 [ 5 ] ; } ;
extern P_dcsdemo_T dcsdemo_rtDefaultP ; extern const ConstP_dcsdemo_T
dcsdemo_rtConstP ;
#endif
