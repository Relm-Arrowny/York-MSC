#include "basic_acc.h"
#include "basic_acc_private.h"
P_basic_T basic_rtDefaultP = { 0.0 , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , 0.0 , { 456.93390421902842 , -
10.660988676539786 , 456.93396496125348 , - 10.661059745714795 ,
456.93418949055035 , - 10.661272254561686 , 456.93462647027229 , -
10.661505622834838 , 456.93412636389792 , - 10.661293011585109 ,
456.93403871115788 , - 10.661240777931347 } , { 0.0 , 1.0 , 2.0 , 3.0 , 4.0 ,
5.0 } , { 0.0 , 0.0 } , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , { -
0.00465967796976128 , - 0.13901474253174739 , - 0.00024760652766104348 , -
0.011765298895308663 , - 0.0073189101536664872 , - 0.14627868030487648 , -
0.000161760546300919 , - 0.0032516314560153072 , - 0.0066291482599849152 , -
0.14630808933919126 , - 0.00016118472101558242 , - 0.0038345342062247097 , -
0.0037966583059328425 , - 0.14629736805149465 , - 2.6554622454359713E-5 , -
0.0011715984885301491 , - 0.0036449900294150219 , - 0.14629014479600161 , -
1.9414076941247604E-5 , - 0.00088285815293864323 , - 0.0036012015675636381 ,
- 0.14629807353544089 , - 4.0388685927668275E-5 , - 0.0017606729142779515 } ,
{ 0.0010440082316700015 , 0.04357728085276702 , 4.3521836966956752E-5 ,
0.00081417753798636761 , 4.0335214054713373E-5 , 0.00082825668373895974 ,
5.9765883422834636E-5 , 0.0023383925782982833 , 6.3413671986092338E-5 ,
0.0025976710594552838 , 7.9725326226237132E-5 , 0.0032949322939413244 } , 8.3
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , { 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 } ,
{ 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 2.0 } , { false , false , false , false ,
false , false , false , false , false , false } , 0U , 0U , 0U , 5U , 5U , 1U
, 0U , 1U , 0U , { 'a' , 'a' , 'a' , 'a' , 'a' } } ; const ConstP_basic_T
basic_rtConstP = { { 12.0 , 12.0 } , { 0.99536825150384012 , -
0.13787884172497267 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , - 0.00024558331451536846 , 0.98832069118679344 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.00061847243309431606 ,
0.025813036189563789 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0014539675835091941 , 0.060686986108361672 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 } , { 10.0 ,
6.0 } , { - 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 1.0 , - 1.0 , 0.0 , 0.0 , 0.0 , 0.0
, - 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 1.0 , - 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , - 1.0
, 1.0 , 0.0 , 0.0 , 0.0 , 1.0 , - 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , - 1.0 , 1.0 ,
0.0 , 0.0 , 0.0 , 1.0 , - 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , - 1.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 }
, { 12.0 , 1.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 1.0 , 0.0 } , { 12.0 , 1.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , { 1.0 , 12.0 } , { 456.93390421902842 ,
- 10.660988676539786 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
1.0 } , { 1.0 , 1.0 } , 0.0 , { 6.0 , 6.0 } , { 0.026276166366672182 , -
0.0041441159306916664 , 0.0053062784949318431 , 0.0047574817648720069 ,
0.018364116617894166 , 0.0 , - 0.0041441159306916664 , 0.025790510356870716 ,
- 0.0046350533998675 , 0.0048099822007751092 , 0.018565534100717457 , 0.0 ,
0.0053062784949318431 , - 0.0046350533998675 , 0.025294233992990467 , -
0.0051367468654014981 , 0.018769905286926319 , 0.0 , 0.0047574817648720069 ,
0.0048099822007751092 , - 0.0051367468654014981 , 0.024787064295462347 ,
0.0089772748877345876 , 0.0 , 0.018364116617894166 , 0.018565534100717457 ,
0.018769905286926319 , 0.0089772748877345876 , 0.11636840562189657 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 100000.0 } , { 6.0 , 6.0 } , {
49.220686583422619 , 15.810666325058316 , - 2.6523780856500156 , -
9.7659127303093562 , - 9.10875867909883 , 0.0 , 15.810666325058316 ,
54.688060229899044 , 15.40362579715004 , - 5.6491187831230611 , -
13.26883241328798 , 0.0 , - 2.6523780856500156 , 15.40362579715004 ,
54.328207089372761 , 13.05565504967765 , - 11.80911139827389 , 0.0 , -
9.7659127303093562 , - 5.6491187831230611 , 13.05565504967765 ,
47.217200180546172 , - 3.3059998069797554 , 0.0 , - 9.10875867909883 , -
13.26883241328798 , - 11.80911139827389 , - 3.3059998069797554 ,
14.3075951749051 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 9.9999999999999974E-6
} , { 20.0 , 1.0 } , { 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 ,
1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 , 1.0 } , { 20.0 ,
5.0 } , { - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , -
0.017383812826191281 , - 0.041982510838537324 , - 0.066307974375944378 , -
0.090364162429936612 , - 0.11415497494556737 , - 0.13768425370441895 , -
0.16095578319439591 , - 0.18397329146650732 , - 0.20674045097883365 , -
0.22926087942786949 , - 0.25153814056743129 , - 0.27357574501531545 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , -
0.017383812826191281 , - 0.041982510838537324 , - 0.066307974375944378 , -
0.090364162429936612 , - 0.11415497494556737 , - 0.13768425370441895 , -
0.16095578319439591 , - 0.18397329146650732 , - 0.20674045097883365 , -
0.22926087942786949 , - 0.25153814056743129 , - 0.0 , - 0.0 , - 0.0 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.017383812826191281 , -
0.041982510838537324 , - 0.066307974375944378 , - 0.090364162429936612 , -
0.11415497494556737 , - 0.13768425370441895 , - 0.16095578319439591 , -
0.18397329146650732 , - 0.20674045097883365 , - 0.22926087942786949 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0
, - 0.017383812826191281 , - 0.041982510838537324 , - 0.066307974375944378 ,
- 0.090364162429936612 , - 0.11415497494556737 , - 0.13768425370441895 , -
0.16095578319439591 , - 0.18397329146650732 , - 0.20674045097883365 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0
, - 0.0 , - 0.017383812826191281 , - 0.041982510838537324 , -
0.066307974375944378 , - 0.090364162429936612 , - 0.11415497494556737 , -
0.13768425370441895 , - 0.16095578319439591 , - 0.18397329146650732 } , { 1.0
, 5.0 } , { 0.33978569494967392 , 0.2992257676359954 , 0.25883891030819128 ,
0.21924029279861168 , 0.18104523651516913 } , { 20.0 , 5.0 } , { - 0.0 , -
0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0
, - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , -
0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0
, - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , -
0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 ,
- 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0
, - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , -
0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 , - 0.0 ,
- 0.0 , - 0.0 } , { 21.0 , 5.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , { 12.0 , 5.0 } , {
792.07442717360209 , - 18.551556626887258 , 0.011121155917958895 ,
0.03732719978848089 , 0.037726511938354815 , 0.038131660906761879 ,
0.03854273502106171 , 0.038959823949488631 , 0.0393830187215128 ,
0.0398124117485108 , 0.040248096844749781 , 1.7739219797709489 ,
669.59981640398689 , - 15.684171981970321 , 0.009371351621021394 ,
0.031453836309591789 , 0.0317898588327606 , 0.0321307921765768 ,
0.032476710654225818 , 0.03282768970702054 , 0.033183805921531882 ,
0.033545137046979756 , 0.0339117620128878 , 1.5003462347556336 ,
557.07345701414624 , - 13.049393623777009 , 0.0077716167310435689 ,
0.026084269842434268 , 0.026362549991019248 , 0.026644896351034474 ,
0.026931370453555939 , 0.027222034763744192 , 0.027516952695028244 ,
0.027816188623505274 , 0.028119807902558629 , 1.2488080941882023 ,
454.58765929460691 , - 10.649440467668239 , 0.006321756977040508 ,
0.021217833702627007 , 0.02144388895951161 , 0.021673246728607164 ,
0.021905956983640291 , 0.022142070456972349 , 0.022381638651119293 ,
0.0226247138504466 , 0.022871349133041594 , 1.0195472147603328 ,
362.23616930108642 , - 8.4865646945128 , 0.0050216077396947039 ,
0.016853960822239313 , 0.01703328011091481 , 0.017215218661871028 ,
0.017399816109212433 , 0.017587112688714962 , 0.017777149246962297 ,
0.017969967250621183 , 0.018165608795857276 , 0.81280676378149908 } , { 12.0
, 1.0 } , { 1.9147263499286296E-5 , 0.00080315230885241132 ,
5.9518007200111768E-16 , - 2.2291497317064477E-17 , 2.7053545915917594E-17 ,
- 1.3334904962267475E-16 , - 2.4896718973356291E-16 , - 6.33969907804103E-16
, 1.0121878361126146E-16 , - 3.8941774908081889E-17 , 6.5809681213274067E-18
, 0.61797162878121037 } , { 6.0 , 6.0 } , { 6.1690600617077491 ,
0.99474968840127675 , - 1.15821523010828 , - 1.7416696675875678 , -
2.4081075236876774 , 0.0 , 0.0 , 6.3073062488540739 , 0.98256003301625072 , -
1.2786859623074815 , - 3.50791763078643 , 0.0 , 0.0 , 0.0 ,
6.5027304528737249 , 1.5151814770359271 , - 3.1220071810117074 , 0.0 , 0.0 ,
0.0 , 0.0 , 6.8156654695921661 , - 0.87401623964041553 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 3.7825381921277543 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.003162277660168379 } , { 12.0 , 1.0 } , { 1.5269657784367413E-5 ,
0.00064138395740576842 , 0.0066386857486767075 , - 4.8412747660214191E-17 , -
2.8585878656218665E-17 , 2.0358493698260471E-17 , - 1.2176961682552807E-16 ,
- 2.5381371118618973E-16 , - 6.3886539808983338E-16 , - 5.003336373823474E-18
, - 4.0604398513151329E-17 , 0.61797162878121015 } , { 5.0 , 5.0 } , { 1.0 ,
1.0 , 1.0 , 1.0 , 1.0 , 0.0 , 1.0 , 1.0 , 1.0 , 1.0 , 0.0 , 0.0 , 1.0 , 1.0 ,
1.0 , 0.0 , 0.0 , 0.0 , 1.0 , 1.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 } , { 10.0 ,
1.0 } , { 100.0 , 100.0 , 100.0 , 100.0 , 100.0 , 100.0 , 100.0 , 100.0 ,
100.0 , 100.0 } , { 10.0 , 1.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0
, 0.0 , 0.0 , 0.0 } , { 10.0 , 21.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 } , { 10.0 , 12.0 } , {
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 } , { 1.0 , 1.0 } , 1.0 , { 505.0 , 1.0 } , { 0.0 , 1.0 , 2.0
, 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 , 11.0 , 12.0 , 13.0 , 14.0
, 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0 , 21.0 , 22.0 , 23.0 , 24.0 , 25.0
, 26.0 , 27.0 , 28.0 , 29.0 , 30.0 , 31.0 , 32.0 , 33.0 , 34.0 , 35.0 , 36.0
, 37.0 , 38.0 , 39.0 , 40.0 , 41.0 , 42.0 , 43.0 , 44.0 , 45.0 , 46.0 , 47.0
, 48.0 , 49.0 , 50.0 , 51.0 , 52.0 , 53.0 , 54.0 , 55.0 , 56.0 , 57.0 , 58.0
, 59.0 , 60.0 , 61.0 , 62.0 , 63.0 , 64.0 , 65.0 , 66.0 , 67.0 , 68.0 , 69.0
, 70.0 , 71.0 , 72.0 , 73.0 , 74.0 , 75.0 , 76.0 , 77.0 , 78.0 , 79.0 , 80.0
, 81.0 , 82.0 , 83.0 , 84.0 , 85.0 , 86.0 , 87.0 , 88.0 , 89.0 , 90.0 , 91.0
, 92.0 , 93.0 , 94.0 , 95.0 , 96.0 , 97.0 , 98.0 , 99.0 , 100.0 , 0.0 , 1.0 ,
2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 , 11.0 , 12.0 , 13.0 ,
14.0 , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0 , 21.0 , 22.0 , 23.0 , 24.0 ,
25.0 , 26.0 , 27.0 , 28.0 , 29.0 , 30.0 , 31.0 , 32.0 , 33.0 , 34.0 , 35.0 ,
36.0 , 37.0 , 38.0 , 39.0 , 40.0 , 41.0 , 42.0 , 43.0 , 44.0 , 45.0 , 46.0 ,
47.0 , 48.0 , 49.0 , 50.0 , 51.0 , 52.0 , 53.0 , 54.0 , 55.0 , 56.0 , 57.0 ,
58.0 , 59.0 , 60.0 , 61.0 , 62.0 , 63.0 , 64.0 , 65.0 , 66.0 , 67.0 , 68.0 ,
69.0 , 70.0 , 71.0 , 72.0 , 73.0 , 74.0 , 75.0 , 76.0 , 77.0 , 78.0 , 79.0 ,
80.0 , 81.0 , 82.0 , 83.0 , 84.0 , 85.0 , 86.0 , 87.0 , 88.0 , 89.0 , 90.0 ,
91.0 , 92.0 , 93.0 , 94.0 , 95.0 , 96.0 , 97.0 , 98.0 , 99.0 , 100.0 , 0.0 ,
1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 , 11.0 , 12.0 ,
13.0 , 14.0 , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0 , 21.0 , 22.0 , 23.0 ,
24.0 , 25.0 , 26.0 , 27.0 , 28.0 , 29.0 , 30.0 , 31.0 , 32.0 , 33.0 , 34.0 ,
35.0 , 36.0 , 37.0 , 38.0 , 39.0 , 40.0 , 41.0 , 42.0 , 43.0 , 44.0 , 45.0 ,
46.0 , 47.0 , 48.0 , 49.0 , 50.0 , 51.0 , 52.0 , 53.0 , 54.0 , 55.0 , 56.0 ,
57.0 , 58.0 , 59.0 , 60.0 , 61.0 , 62.0 , 63.0 , 64.0 , 65.0 , 66.0 , 67.0 ,
68.0 , 69.0 , 70.0 , 71.0 , 72.0 , 73.0 , 74.0 , 75.0 , 76.0 , 77.0 , 78.0 ,
79.0 , 80.0 , 81.0 , 82.0 , 83.0 , 84.0 , 85.0 , 86.0 , 87.0 , 88.0 , 89.0 ,
90.0 , 91.0 , 92.0 , 93.0 , 94.0 , 95.0 , 96.0 , 97.0 , 98.0 , 99.0 , 100.0 ,
0.0 , 1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 , 11.0 ,
12.0 , 13.0 , 14.0 , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0 , 21.0 , 22.0 ,
23.0 , 24.0 , 25.0 , 26.0 , 27.0 , 28.0 , 29.0 , 30.0 , 31.0 , 32.0 , 33.0 ,
34.0 , 35.0 , 36.0 , 37.0 , 38.0 , 39.0 , 40.0 , 41.0 , 42.0 , 43.0 , 44.0 ,
45.0 , 46.0 , 47.0 , 48.0 , 49.0 , 50.0 , 51.0 , 52.0 , 53.0 , 54.0 , 55.0 ,
56.0 , 57.0 , 58.0 , 59.0 , 60.0 , 61.0 , 62.0 , 63.0 , 64.0 , 65.0 , 66.0 ,
67.0 , 68.0 , 69.0 , 70.0 , 71.0 , 72.0 , 73.0 , 74.0 , 75.0 , 76.0 , 77.0 ,
78.0 , 79.0 , 80.0 , 81.0 , 82.0 , 83.0 , 84.0 , 85.0 , 86.0 , 87.0 , 88.0 ,
89.0 , 90.0 , 91.0 , 92.0 , 93.0 , 94.0 , 95.0 , 96.0 , 97.0 , 98.0 , 99.0 ,
100.0 , 0.0 , 1.0 , 2.0 , 3.0 , 4.0 , 5.0 , 6.0 , 7.0 , 8.0 , 9.0 , 10.0 ,
11.0 , 12.0 , 13.0 , 14.0 , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0 , 21.0 ,
22.0 , 23.0 , 24.0 , 25.0 , 26.0 , 27.0 , 28.0 , 29.0 , 30.0 , 31.0 , 32.0 ,
33.0 , 34.0 , 35.0 , 36.0 , 37.0 , 38.0 , 39.0 , 40.0 , 41.0 , 42.0 , 43.0 ,
44.0 , 45.0 , 46.0 , 47.0 , 48.0 , 49.0 , 50.0 , 51.0 , 52.0 , 53.0 , 54.0 ,
55.0 , 56.0 , 57.0 , 58.0 , 59.0 , 60.0 , 61.0 , 62.0 , 63.0 , 64.0 , 65.0 ,
66.0 , 67.0 , 68.0 , 69.0 , 70.0 , 71.0 , 72.0 , 73.0 , 74.0 , 75.0 , 76.0 ,
77.0 , 78.0 , 79.0 , 80.0 , 81.0 , 82.0 , 83.0 , 84.0 , 85.0 , 86.0 , 87.0 ,
88.0 , 89.0 , 90.0 , 91.0 , 92.0 , 93.0 , 94.0 , 95.0 , 96.0 , 97.0 , 98.0 ,
99.0 , 100.0 } , { 20.0 , 1.0 } , { 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 ,
0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 }
, { 10.0 , 1.0 } , { 81 , 82 , 83 , 84 , 85 , 86 , 87 , 88 , 89 , 90 } , {
5.0 , 1.0 } , { 101 , 101 , 101 , 101 , 101 } , { 'a' , 'a' , 'a' , 'a' } , {
1.0 , 1.0 } , 6 , { 'a' , 'a' , 'a' , 'a' } , { 1.0 , 1.0 } , 0 , { 'a' , 'a'
, 'a' , 'a' } , { 1.0 , 1.0 } , 5 , { 'a' , 'a' , 'a' , 'a' } , { 1.0 , 1.0 }
, 101 , { 'a' , 'a' , 'a' , 'a' } , { 1.0 , 1.0 } , 1 , { 'a' , 'a' , 'a' ,
'a' } , { 1.0 , 1.0 } , 12 , { 'a' , 'a' , 'a' , 'a' } , { 1.0 , 1.0 } , 20 ,
{ 'a' , 'a' , 'a' , 'a' } , { 1.0 , 1.0 } , false , { 'a' , 'a' , 'a' , 'a' ,
'a' , 'a' , 'a' } , { 1.0 , 1.0 } , true , { 'a' , 'a' , 'a' , 'a' , 'a' ,
'a' , 'a' } } ;
