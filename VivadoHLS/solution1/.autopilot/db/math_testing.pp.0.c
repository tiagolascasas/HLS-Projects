# 1 "VivadoHLS/math_testing.c"
# 1 "VivadoHLS/math_testing.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1






# 1 "D:/Xilinx/Vivado/2019.1/common/technology/autopilot\\etc/autopilot_ssdm_op.h" 1
# 305 "D:/Xilinx/Vivado/2019.1/common/technology/autopilot\\etc/autopilot_ssdm_op.h"
    void _ssdm_op_IfRead() __attribute__ ((nothrow));
    void _ssdm_op_IfWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanWrite() __attribute__ ((nothrow));


    void _ssdm_StreamRead() __attribute__ ((nothrow));
    void _ssdm_StreamWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanWrite() __attribute__ ((nothrow));




    void _ssdm_op_MemShiftRead() __attribute__ ((nothrow));

    void _ssdm_op_Wait() __attribute__ ((nothrow));
    void _ssdm_op_Poll() __attribute__ ((nothrow));

    void _ssdm_op_Return() __attribute__ ((nothrow));


    void _ssdm_op_SpecSynModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecTopModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDecl() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDef() __attribute__ ((nothrow));
    void _ssdm_op_SpecPort() __attribute__ ((nothrow));
    void _ssdm_op_SpecConnection() __attribute__ ((nothrow));
    void _ssdm_op_SpecChannel() __attribute__ ((nothrow));
    void _ssdm_op_SpecSensitive() __attribute__ ((nothrow));
    void _ssdm_op_SpecModuleInst() __attribute__ ((nothrow));
    void _ssdm_op_SpecPortMap() __attribute__ ((nothrow));

    void _ssdm_op_SpecReset() __attribute__ ((nothrow));

    void _ssdm_op_SpecPlatform() __attribute__ ((nothrow));
    void _ssdm_op_SpecClockDomain() __attribute__ ((nothrow));
    void _ssdm_op_SpecPowerDomain() __attribute__ ((nothrow));

    int _ssdm_op_SpecRegionBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecRegionEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopName() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopTripCount() __attribute__ ((nothrow));

    int _ssdm_op_SpecStateBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecStateEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecInterface() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipeline() __attribute__ ((nothrow));
    void _ssdm_op_SpecDataflowPipeline() __attribute__ ((nothrow));


    void _ssdm_op_SpecLatency() __attribute__ ((nothrow));
    void _ssdm_op_SpecParallel() __attribute__ ((nothrow));
    void _ssdm_op_SpecProtocol() __attribute__ ((nothrow));
    void _ssdm_op_SpecOccurrence() __attribute__ ((nothrow));

    void _ssdm_op_SpecResource() __attribute__ ((nothrow));
    void _ssdm_op_SpecResourceLimit() __attribute__ ((nothrow));
    void _ssdm_op_SpecCHCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecFUCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIFCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIPCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecKeepValue() __attribute__ ((nothrow));
    void _ssdm_op_SpecMemCore() __attribute__ ((nothrow));

    void _ssdm_op_SpecExt() __attribute__ ((nothrow));




    void _ssdm_SpecArrayDimSize() __attribute__ ((nothrow));

    void _ssdm_RegionBegin() __attribute__ ((nothrow));
    void _ssdm_RegionEnd() __attribute__ ((nothrow));

    void _ssdm_Unroll() __attribute__ ((nothrow));
    void _ssdm_UnrollRegion() __attribute__ ((nothrow));

    void _ssdm_InlineAll() __attribute__ ((nothrow));
    void _ssdm_InlineLoop() __attribute__ ((nothrow));
    void _ssdm_Inline() __attribute__ ((nothrow));
    void _ssdm_InlineSelf() __attribute__ ((nothrow));
    void _ssdm_InlineRegion() __attribute__ ((nothrow));

    void _ssdm_SpecArrayMap() __attribute__ ((nothrow));
    void _ssdm_SpecArrayPartition() __attribute__ ((nothrow));
    void _ssdm_SpecArrayReshape() __attribute__ ((nothrow));

    void _ssdm_SpecStream() __attribute__ ((nothrow));

    void _ssdm_op_SpecStable() __attribute__ ((nothrow));
    void _ssdm_op_SpecStableContent() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipoDepth() __attribute__ ((nothrow));

    void _ssdm_SpecExpr() __attribute__ ((nothrow));
    void _ssdm_SpecExprBalance() __attribute__ ((nothrow));

    void _ssdm_SpecDependence() __attribute__ ((nothrow));

    void _ssdm_SpecLoopMerge() __attribute__ ((nothrow));
    void _ssdm_SpecLoopFlatten() __attribute__ ((nothrow));
    void _ssdm_SpecLoopRewind() __attribute__ ((nothrow));

    void _ssdm_SpecFuncInstantiation() __attribute__ ((nothrow));
    void _ssdm_SpecFuncBuffer() __attribute__ ((nothrow));
    void _ssdm_SpecFuncExtract() __attribute__ ((nothrow));
    void _ssdm_SpecConstant() __attribute__ ((nothrow));

    void _ssdm_DataPack() __attribute__ ((nothrow));
    void _ssdm_SpecDataPack() __attribute__ ((nothrow));

    void _ssdm_op_SpecBitsMap() __attribute__ ((nothrow));
    void _ssdm_op_SpecLicense() __attribute__ ((nothrow));
# 8 "<command line>" 2
# 1 "<built-in>" 2
# 1 "VivadoHLS/math_testing.c" 2
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 1 3
# 10 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
# 10 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3


# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 10 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/_mingw_mac.h" 1 3
# 10 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3
# 277 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 1 3
# 13 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 3
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3
# 674 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/sdks/_mingw_directx.h" 1 3
# 674 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3

# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include/sdks/_mingw_ddk.h" 1 3
# 675 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3
# 13 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 2 3


#pragma pack(push,_CRT_PACKING)








 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 102 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\vadefs.h" 3
#pragma pack(pop)
# 277 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 2 3


#pragma pack(push,_CRT_PACKING)
# 370 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef unsigned long long size_t;
# 380 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long ssize_t;
# 392 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long intptr_t;
# 405 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 418 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
__extension__ typedef long long ptrdiff_t;
# 428 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;
# 456 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;







typedef __time64_t time_t;
# 607 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {
  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;
} threadlocinfo;







const char *__mingw_get_crt_info (void);





#pragma pack(pop)
# 12 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 2 3


struct _exception;

#pragma pack(push,_CRT_PACKING)
# 79 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
 extern double * __imp__HUGE;
# 91 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  struct _exception {
    int type;
    const char *name;
    double arg1;
    double arg2;
    double retval;
  };

  void __mingw_raise_matherr (int typ, const char *name, double a1, double a2,
         double rslt);
  void __mingw_setusermatherr (int ( *)(struct _exception *));
  __attribute__ ((__dllimport__)) void __setusermatherr(int ( *)(struct _exception *));



  double sin(double _X);
  double cos(double _X);
  double tan(double _X);
  double sinh(double _X);
  double cosh(double _X);
  double tanh(double _X);
  double asin(double _X);
  double acos(double _X);
  double atan(double _X);
  double atan2(double _Y,double _X);
  double exp(double _X);
  double log(double _X);
  double log10(double _X);
  double pow(double _X,double _Y);
  double sqrt(double _X);
  double ceil(double _X);
  double floor(double _X);
  double fabs(double _X);
# 135 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  double ldexp(double _X,int _Y);
  double frexp(double _X,int *_Y);
  double modf(double _X,double *_Y);
  double fmod(double _X,double _Y);

  void sincos (double __x, double *p_sin, double *p_cos);
  void sincosl (long double __x, long double *p_sin, long double *p_cos);
  void sincosf (float __x, float *p_sin, float *p_cos);



  int abs(int _X);
  long labs(long _X);



  double atof(const char *_String);
  double _atof_l(const char *_String,_locale_t _Locale);
# 162 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  struct _complex {
    double x;
    double y;
  };


  __attribute__ ((__dllimport__)) double _cabs(struct _complex _ComplexA);
  double _hypot(double _X,double _Y);
  __attribute__ ((__dllimport__)) double _j0(double _X);
  __attribute__ ((__dllimport__)) double _j1(double _X);
  __attribute__ ((__dllimport__)) double _jn(int _X,double _Y);
  __attribute__ ((__dllimport__)) double _y0(double _X);
  __attribute__ ((__dllimport__)) double _y1(double _X);
  __attribute__ ((__dllimport__)) double _yn(int _X,double _Y);


  __attribute__ ((__dllimport__)) int _matherr (struct _exception *);
# 189 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  __attribute__ ((__dllimport__)) double _chgsign (double _X);
  __attribute__ ((__dllimport__)) double _copysign (double _Number,double _Sign);
  __attribute__ ((__dllimport__)) double _logb (double);
  __attribute__ ((__dllimport__)) double _nextafter (double, double);
  __attribute__ ((__dllimport__)) double _scalb (double, long);
  __attribute__ ((__dllimport__)) int _finite (double);
  __attribute__ ((__dllimport__)) int _fpclass (double);
  __attribute__ ((__dllimport__)) int _isnan (double);






__attribute__ ((__dllimport__)) double j0 (double) ;
__attribute__ ((__dllimport__)) double j1 (double) ;
__attribute__ ((__dllimport__)) double jn (int, double) ;
__attribute__ ((__dllimport__)) double y0 (double) ;
__attribute__ ((__dllimport__)) double y1 (double) ;
__attribute__ ((__dllimport__)) double yn (int, double) ;

__attribute__ ((__dllimport__)) double chgsign (double);
# 219 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  __attribute__ ((__dllimport__)) int finite (double);
  __attribute__ ((__dllimport__)) int fpclass (double);
# 264 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
typedef float float_t;
typedef double double_t;
# 299 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __fpclassifyl (long double);
  extern int __fpclassifyf (float);
  extern int __fpclassify (double);
# 335 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __isnan (double);
  extern int __isnanf (float);
  extern int __isnanl (long double);
# 376 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern int __signbit (double);
  extern int __signbitf (float);
  extern int __signbitl (long double);
# 404 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern float sinf(float _X);
  extern long double sinl(long double);

  extern float cosf(float _X);
  extern long double cosl(long double);

  extern float tanf(float _X);
  extern long double tanl(long double);
  extern float asinf(float _X);
  extern long double asinl(long double);

  extern float acosf (float);
  extern long double acosl (long double);

  extern float atanf (float);
  extern long double atanl (long double);

  extern float atan2f (float, float);
  extern long double atan2l (long double, long double);


  extern float sinhf(float _X);



  extern long double sinhl(long double);

  extern float coshf(float _X);



  extern long double coshl(long double);

  extern float tanhf(float _X);



  extern long double tanhl(long double);



  extern double acosh (double);
  extern float acoshf (float);
  extern long double acoshl (long double);


  extern double asinh (double);
  extern float asinhf (float);
  extern long double asinhl (long double);


  extern double atanh (double);
  extern float atanhf (float);
  extern long double atanhl (long double);



  extern float expf(float _X);



  extern long double expl(long double);


  extern double exp2(double);
  extern float exp2f(float);
  extern long double exp2l(long double);



  extern double expm1(double);
  extern float expm1f(float);
  extern long double expm1l(long double);


  extern float frexpf(float _X,int *_Y);



  extern long double frexpl(long double,int *);




  extern int ilogb (double);
  extern int ilogbf (float);
  extern int ilogbl (long double);


  extern float ldexpf(float _X,int _Y);



  extern long double ldexpl (long double, int);


  extern float logf (float);
  extern long double logl(long double);


  extern float log10f (float);
  extern long double log10l(long double);


  extern double log1p(double);
  extern float log1pf(float);
  extern long double log1pl(long double);


  extern double log2 (double);
  extern float log2f (float);
  extern long double log2l (long double);


  extern double logb (double);
  extern float logbf (float);
  extern long double logbl (long double);
# 553 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern float modff (float, float*);
  extern long double modfl (long double, long double*);


  extern double scalbn (double, int);
  extern float scalbnf (float, int);
  extern long double scalbnl (long double, int);

  extern double scalbln (double, long);
  extern float scalblnf (float, long);
  extern long double scalblnl (long double, long);



  extern double cbrt (double);
  extern float cbrtf (float);
  extern long double cbrtl (long double);


  extern float fabsf (float x);
# 583 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern long double fabsl (long double);
# 595 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double hypot (double, double) ;
  extern float hypotf (float x, float y);



  extern long double hypotl (long double, long double);


  extern float powf(float _X,float _Y);



  extern long double powl (long double, long double);


  extern float sqrtf (float);
  extern long double sqrtl(long double);


  extern double erf (double);
  extern float erff (float);
  extern long double erfl (long double);


  extern double erfc (double);
  extern float erfcf (float);
  extern long double erfcl (long double);


  extern double lgamma (double);
  extern float lgammaf (float);
  extern long double lgammal (long double);


  extern double tgamma (double);
  extern float tgammaf (float);
  extern long double tgammal (long double);


  extern float ceilf (float);
  extern long double ceill (long double);


  extern float floorf (float);
  extern long double floorl (long double);


  extern double nearbyint ( double);
  extern float nearbyintf (float);
  extern long double nearbyintl (long double);



extern double rint (double);
extern float rintf (float);
extern long double rintl (long double);


extern long lrint (double);
extern long lrintf (float);
extern long lrintl (long double);

__extension__ long long llrint (double);
__extension__ long long llrintf (float);
__extension__ long long llrintl (long double);
# 739 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double round (double);
  extern float roundf (float);
  extern long double roundl (long double);


  extern long lround (double);
  extern long lroundf (float);
  extern long lroundl (long double);
  __extension__ long long llround (double);
  __extension__ long long llroundf (float);
  __extension__ long long llroundl (long double);



  extern double trunc (double);
  extern float truncf (float);
  extern long double truncl (long double);


  extern float fmodf (float, float);
  extern long double fmodl (long double, long double);


  extern double remainder (double, double);
  extern float remainderf (float, float);
  extern long double remainderl (long double, long double);


  extern double remquo(double, double, int *);
  extern float remquof(float, float, int *);
  extern long double remquol(long double, long double, int *);


  extern double copysign (double, double);
  extern float copysignf (float, float);
  extern long double copysignl (long double, long double);


  extern double nan(const char *tagp);
  extern float nanf(const char *tagp);
  extern long double nanl(const char *tagp);
# 788 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
  extern double nextafter (double, double);
  extern float nextafterf (float, float);
  extern long double nextafterl (long double, long double);


  extern double nexttoward (double, long double);
  extern float nexttowardf (float, long double);
  extern long double nexttowardl (long double, long double);



  extern double fdim (double x, double y);
  extern float fdimf (float x, float y);
  extern long double fdiml (long double x, long double y);







  extern double fmax (double, double);
  extern float fmaxf (float, float);
  extern long double fmaxl (long double, long double);


  extern double fmin (double, double);
  extern float fminf (float, float);
  extern long double fminl (long double, long double);



  extern double fma (double, double, double);
  extern float fmaf (float, float, float);
  extern long double fmal (long double, long double, long double);
# 871 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
   __attribute__ ((__dllimport__)) float _copysignf (float _Number,float _Sign);
   __attribute__ ((__dllimport__)) float _chgsignf (float _X);
   __attribute__ ((__dllimport__)) float _logbf(float _X);
   __attribute__ ((__dllimport__)) float _nextafterf(float _X,float _Y);
   __attribute__ ((__dllimport__)) int _finitef(float _X);
   __attribute__ ((__dllimport__)) int _isnanf(float _X);
   __attribute__ ((__dllimport__)) int _fpclassf(float _X);



   extern long double _chgsignl (long double);
# 898 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\math.h" 3
#pragma pack(pop)
# 2 "VivadoHLS/math_testing.c" 2
# 1 "VivadoHLS/fast_math.h" 1

# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdint.h" 1 3 4
# 33 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdint.h" 3 4
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdint.h" 1 3 4
# 28 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdint.h" 3 4
# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\_mingw.h" 1 3 4
# 28 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdint.h" 2 3 4




# 1 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stddef.h" 1 3 4
# 31 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stddef.h" 3 4
typedef __typeof__(((int*)0)-((int*)0)) ptrdiff_t;



typedef __typeof__(sizeof(int)) size_t;




typedef unsigned short wchar_t;
# 32 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/../../../x86_64-w64-mingw32/include\\stdint.h" 2 3 4



typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 33 "D:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdint.h" 2 3 4
# 3 "VivadoHLS/fast_math.h" 2

static inline float fast_fabs32(float number) {
    unsigned int p2 = * (unsigned int *) &number;
    p2 = p2 & 0X7FFFFFFF;
    return * (float *) &p2;
}

static inline float fast_symmetrical32(float number) {
    unsigned int p2 = * (unsigned int *) &number;
    p2 = p2 ^ (1 << 31);
    return * (float *) &p2;
}

static inline float fast_inv_sqrt32(float number) {
 uint32_t i;
 float x2, y;
 x2 = number * 0.5F;
 y = number;
 i = * (uint32_t *) &y;
 i = 0x5f375a86 - (i >> 1);
 y = *(float *) &i;
 y = y * (1.5F - (x2 * y * y));
 return y;
}

static inline double fast_inv_sqrt64(double number) {
 uint64_t i;
 double x2, y;
 x2 = number * 0.5;
 y = number;
 i = * (uint64_t *) &y;
 i = 0x5fe6eb50c7b537a9 - (i >> 1);
 y = * (double *) &i;
 y = y * (1.5 - (x2 * y * y));
 return y;
}
# 3 "VivadoHLS/math_testing.c" 2



void make_positive(float a[1024]) {_ssdm_SpecArrayDimSize(a, 1024);
 for (int i = 0; i < 1024; i++) {

  a[i] = fast_fabs32(a[i]);



 }
}

void make_symmetrical(float a[1024]) {_ssdm_SpecArrayDimSize(a, 1024);
 for (int i = 0; i < 1024; i++) {

  a[i] = fast_symmetrical32(a[i]);



 }
}
