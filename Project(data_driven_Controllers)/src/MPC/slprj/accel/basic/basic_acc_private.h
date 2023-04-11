#ifndef RTW_HEADER_basic_acc_private_h_
#define RTW_HEADER_basic_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "basic_acc.h"
#include "basic_acc_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T basic_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T *
tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * *
uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay , int_T *
maxNewBufSzPtr ) ; real_T basic_acc_rt_TDelayInterpolate ( real_T tMinusDelay
, real_T tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T
oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; extern uint32_T plook_lincpa ( real_T u ,
const real_T bp [ ] , uint32_T maxIndex , real_T * fraction , uint32_T *
prevIndex ) ; extern uint32_T linsearch_u32d ( real_T u , const real_T bp [ ]
, uint32_T startIndex ) ;
#endif
