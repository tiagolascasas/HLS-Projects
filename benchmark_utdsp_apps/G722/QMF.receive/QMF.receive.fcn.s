.gccDSP_compiled

.global XD
.data_X

XD:
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.global XS
XS:
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.global QMFT_Heven
QMFT_Heven:
.int    3
.int    -11
.int    12
.int    32
.int    -210
.int    951
.int    3876
.int    -805
.int    362
.int    -156
.int    53
.int    -11
.int    0
.int    0
.int    0
.int    0
.global QMFT_Hodd
QMFT_Hodd:
.int    -11
.int    53
.int    -156
.int    362
.int    -805
.int    3867
.int    951
.int    -210
.int    32
.int    12
.int    -11
.int    3
.int    0
.int    0
.int    0
.int    0
.text

.global main
.begin  main
main:
	dec     a31,a0,a31
	st.d    (a31),d8
	mov.d   d0,d5
	movl.a  #index,a1
	st.d    (a1),d5
L2:
	movl.a  #mlow,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     input_dsp
	mov.d   d2,d8
	movl.a  #mhigh,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     input_dsp
	bnez.d  d8,L4
	beqz.d  d2,L3
L4:
	movl.a  #index,a2
	movl.a  #mlow,a1
	ld.d    (a1),d3
	movl.a  #mhigh,a1
	ld.d    (a1),d4
	movl.a  #result1,a5
	movl.a  #result2,a6
	jsr     ReceiveQMF
	movl.a  #result1,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     output_dsp
	movl.a  #result2,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     output_dsp
	jmp     L2
L3:
	ld.d    (a31),d8
	inc     a31,a0,a31
	rts     
.end    main

.global input_dsp
.begin  input_dsp
input_dsp:
	trap    #5
	rts     
.end    input_dsp

.global output_dsp
.begin  output_dsp
output_dsp:
	trap    #6
	rts     
.end    output_dsp

.global abs
.begin  abs
abs:
	trap    #7
	rts     
.end    abs

.global fabs
.begin  fabs
fabs:
	trap    #8
	rts     
.end    fabs

.global fmod
.begin  fmod
fmod:
	trap    #9
	rts     
.end    fmod

.global asin
.begin  asin
asin:
	trap    #10
	rts     
.end    asin

.global acos
.begin  acos
acos:
	trap    #11
	rts     
.end    acos

.global ceil
.begin  ceil
ceil:
	trap    #12
	rts     
.end    ceil

.global cos
.begin  cos
cos:
	trap    #13
	rts     
.end    cos

.global exp
.begin  exp
exp:
	trap    #14
	rts     
.end    exp

.global floor
.begin  floor
floor:
	trap    #15
	rts     
.end    floor

.global log
.begin  log
log:
	trap    #16
	rts     
.end    ln

.global log10
.begin  log10
log10:
	trap    #17
	rts     
.end    log

.global sin
.begin  sin
sin:
	trap    #18
	rts     
.end    sin

.global sqrt
.begin  sqrt
sqrt:
	trap    #19
	rts     
.end    sqrt

.global pow
.begin  pow
pow:
	trap    #20
	rts     
.end    pow

.global tan
.begin  tan
tan:
	trap    #21
	rts     
.end    tan

.global atan
.begin  atan
atan:
	trap    #22
	rts     
.end    atan

.global ReceiveQMF
.begin  ReceiveQMF
ReceiveQMF:
	dec     a31,a0,a31
	st.d    (a31),d8
	dec     a31,a0,a31
	st.d    (a31),d9
	dec     a31,a0,a31
	st.d    (a31),d10
	dec     a31,a0,a31
	st.d    (a31),d11
	dec     a31,a0,a31
	st.a    (a31),a8
	dec     a31,a0,a31
	st.a    (a31),a9
	dec     a31,a0,a31
	st.a    (a31),a10
	dec     a31,a0,a31
	st.a    (a31),a11
	dec     a31,a0,a31
	st.a    (a31),a12
	mov.a   a2,a4
	mov.d   d3,d2
	mov.d   d4,d3
	mov.a   a5,a11
	mov.a   a6,a12
	movl.a  #XD,a7
	movl.a  #XS,a6
	movs.a  #60,a2
	inc     a7,a2,a9
	inc     a6,a2,a8
	movl.a  #QMFT_Heven,a5
	movl.a  #QMFT_Hodd,a10
	ld.d    (a4),d4
	movs.d  #2,d5
	asl.d   d4,d5,d4
	movd2a  d4,a29
	inc     a7,a29,a3
	movd2a  d4,a29
	inc     a6,a29,a2
	sub.d   d2,d3,d4
	st.d    (a3),d4
	add.d   d2,d3,d2
	st.d    (a2),d2
	ld.d    (a4),d2
	movs.d  #-1,d3
	add.d   d2,d3,d2
	st.d    (a4),d2
	slt.d   d2,d0,d1
	beqz.d  d1,L6
	movs.d  #15,d11
	st.d    (a4),d11
L6:
	mov.d   d0,d3
	mov.d   d0,d7
	mov.a   a10,a4
	ld.d    (a3),d8
	inc     a3,a0,a3
	ld.d    (a2),d9
	inc     a2,a0,a2
	ld.d    (a5),d5
	inc     a5,a0,a5
	ld.d    (a4),d6
	inc     a4,a0,a4
	sgt.a   a3,a9,a1
	beqz.a  a1,L7
	mov.a   a7,a3
L7:
	sgt.a   a2,a8,a1
	beqz.a  a1,L8
	mov.a   a6,a2
L8:
	mov.d   d0,d2
	movs.d  #1,d10
	movs.d  #10,d4
L14:
	madd    d8,d5,d3,d3
	madd    d9,d6,d7,d7
	ld.d    (a3),d8
	inc     a3,a0,a3
	ld.d    (a2),d9
	inc     a2,a0,a2
	ld.d    (a5),d5
	inc     a5,a0,a5
	ld.d    (a4),d6
	inc     a4,a0,a4
	sgt.a   a3,a9,a1
	beqz.a  a1,L12
	mov.a   a7,a3
L12:
	sgt.a   a2,a8,a1
	beqz.a  a1,L11
	mov.a   a6,a2
L11:
	add.d   d2,d10,d2
	sgt.d   d2,d4,d1
	beqz.d  d1,L14
	madd    d8,d5,d3,d3
	madd    d9,d6,d7,d7
	movs.d  #8,d2
	asr.d   d3,d2,d3
	movl.d  #16383,d2
	sgt.d   d3,d2,d1
	beqz.d  d1,L15
	mov.d   d2,d3
L15:
	movl.d  #-16384,d2
	slt.d   d3,d2,d1
	beqz.d  d1,L16
	mov.d   d2,d3
L16:
	movs.d  #8,d2
	asr.d   d7,d2,d2
	movl.d  #16383,d4
	sgt.d   d2,d4,d1
	beqz.d  d1,L17
	mov.d   d4,d2
L17:
	movl.d  #-16384,d4
	slt.d   d2,d4,d1
	beqz.d  d1,L18
	mov.d   d4,d2
L18:
	st.d    (a11),d3
	st.d    (a12),d2
	movs.d  #1,d2
	ld.a    (a31),a12
	inc     a31,a0,a31
	ld.a    (a31),a11
	inc     a31,a0,a31
	ld.a    (a31),a10
	inc     a31,a0,a31
	ld.a    (a31),a9
	inc     a31,a0,a31
	ld.a    (a31),a8
	inc     a31,a0,a31
	ld.d    (a31),d11
	inc     a31,a0,a31
	ld.d    (a31),d10
	inc     a31,a0,a31
	ld.d    (a31),d9
	inc     a31,a0,a31
	ld.d    (a31),d8
	inc     a31,a0,a31
	rts     
.end    ReceiveQMF

.global a11
.common a11,1
.global a10
.common a10,1
.global a9
.common a9,1
.global a8
.common a8,1
.global a7
.common a7,1
.global a6
.common a6,1
.global a5
.common a5,1
.global a4
.common a4,1
.global a3
.common a3,1
.global a2
.common a2,1
.global a1
.common a1,1
.global result2
.common result2,1
.global result1
.common result1,1
.global index
.common index,1
.global mhigh
.common mhigh,1
.global mlow
.common mlow,1

