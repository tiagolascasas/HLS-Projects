.gccDSP_compiled

.global TBL21_SIH
.data_X

TBL21_SIH:
.int    -1
.int    -1
.int    0
.int    0
.global TBL21_IH2
TBL21_IH2:
.int    2
.int    1
.int    2
.int    1
.global TBL14_QQ2
TBL14_QQ2:
.int    0
.int    202
.int    926
.text

.global block2h
.begin  block2h
block2h:
	mov.d   d3,d5
	mov.a   a4,a5
	movl.a  #TBL21_SIH,a4
	movs.a  #2,a2
	movd2a  d2,a6
	asl.a   a6,a2,a3
	inc     a4,a3,a4
	ld.d    (a4),d2
	movl.a  #TBL21_IH2,a4
	inc     a4,a3,a3
	ld.d    (a3),d3
	movl.a  #TBL14_QQ2,a3
	movd2a  d3,a6
	asl.a   a6,a2,a2
	inc     a3,a2,a2
	ld.d    (a2),d3
	movs.d  #3,d4
	asl.d   d3,d4,d3
	bnez.d  d2,L2
	mov.d   d3,d2
	jmp     L3
L2:
	sub.d   d0,d3,d2
L3:
	mult.d  d5,d2,d2
	movs.d  #15,d3
	asr.d   d2,d3,d2
	st.d    (a5),d2
	movs.d  #1,d2
	rts     
.end    block2h

.global TBL14_WH
.data_X

TBL14_WH:
.int    0
.int    -214
.int    798
.global TBL15_ILB
TBL15_ILB:
.int    2048
.int    2093
.int    2139
.int    2186
.int    2233
.int    2282
.int    2332
.int    2383
.int    2435
.int    2489
.int    2543
.int    2599
.int    2656
.int    2714
.int    2774
.int    2834
.int    2896
.int    2960
.int    3025
.int    3091
.int    3158
.int    3228
.int    3298
.int    3371
.int    3444
.int    3520
.int    3597
.int    3676
.int    3756
.int    3838
.int    3922
.int    4008
.text

.global block3h
.begin  block3h
block3h:
	mov.d   d2,d4
	mov.d   d3,d2
	mov.a   a4,a2
	movs.d  #1,d3
	sne.d   d2,d3,d1
	bnez.d  d1,L5
	mov.d   d0,d5
	movl.a  #B3H_NBH,a1
	st.d    (a1),d5
	mov.d   d0,d5
	movl.a  #B3H_NBPH,a1
	st.d    (a1),d5
	movs.d  #32,d5
	st.d    (a2),d5
	movs.d  #32,d5
	movl.a  #B3H_DEPH,a1
	st.d    (a1),d5
	movs.d  #-1,d2
	jmp     L4
L5:
	movl.a  #B3H_NBPH,a1
	ld.d    (a1),d5
	movl.a  #B3H_NBH,a1
	st.d    (a1),d5
	movl.a  #B3H_DEPH,a1
	ld.d    (a1),d5
	st.d    (a2),d5
	movl.a  #TBL21_IH2,a3
	movs.a  #2,a2
	movd2a  d4,a5
	asl.a   a5,a2,a4
	inc     a3,a4,a3
	ld.d    (a3),d2
	movl.a  #TBL14_WH,a3
	movd2a  d2,a5
	asl.a   a5,a2,a2
	inc     a3,a2,a2
	ld.d    (a2),d2
	movl.a  #B3H_NBH,a1
	ld.d    (a1),d3
	movl.d  #32512,d4
	mult.d  d3,d4,d3
	movs.d  #15,d4
	asr.d   d3,d4,d3
	add.d   d3,d2,d3
	movl.a  #B3H_NBPH,a1
	st.d    (a1),d3
	slt.d   d3,d0,d1
	beqz.d  d1,L7
	mov.d   d0,d3
	jmp     L8
L7:
	movl.d  #22528,d2
	sgt.d   d3,d2,d1
	beqz.d  d1,L8
	mov.d   d2,d3
L8:
	movs.d  #6,d2
	asr.d   d3,d2,d4
	movs.d  #31,d2
	and.d   d4,d2,d4
	movs.d  #11,d2
	asr.d   d3,d2,d3
	sne.d   d3,d2,d1
	bnez.d  d1,L10
	movl.a  #TBL15_ILB,a2
	movs.a  #2,a3
	movd2a  d4,a5
	asl.a   a5,a3,a3
	inc     a2,a3,a2
	ld.d    (a2),d2
	movs.d  #1,d3
	asl.d   d2,d3,d3
	jmp     L11
L10:
	movl.a  #TBL15_ILB,a2
	movs.a  #2,a3
	movd2a  d4,a5
	asl.a   a5,a3,a3
	inc     a2,a3,a2
	movs.d  #10,d2
	sub.d   d2,d3,d2
	ld.d    (a2),d3
	asr.d   d3,d2,d3
L11:
	movs.d  #2,d2
	asl.d   d3,d2,d2
	movl.a  #B3H_DEPH,a1
	st.d    (a1),d2
	movs.d  #1,d2
L4:
	rts     
.end    block3h

.global B4H_DHi
.data_X

B4H_DHi:
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.global B4H_BPHi
B4H_BPHi:
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.global B4H_BHi
B4H_BHi:
.int    0
.int    0
.int    0
.int    0
.int    0
.int    0
.text

.global block4h
.begin  block4h
block4h:
	dec     a31,a0,a31
	st.d    (a31),d8
	dec     a31,a0,a31
	st.d    (a31),d9
	dec     a31,a0,a31
	st.d    (a31),d10
	dec     a31,a0,a31
	st.d    (a31),d11
	mov.d   d2,d5
	mov.d   d3,d2
	mov.a   a4,a5
	movs.d  #1,d3
	sne.d   d2,d3,d1
	bnez.d  d1,L13
	movl.a  #B4H_BHi,a4
	movl.a  #B4H_BPHi,a3
	movl.a  #B4H_DHi,a2
	mov.d   d0,d4
	movs.d  #1,d3
	movs.d  #5,d2
L17:
	mov.d   d0,d11
	st.d    (a4),d11
	inc     a4,a0,a4
	mov.d   d0,d11
	st.d    (a3),d11
	inc     a3,a0,a3
	mov.d   d0,d11
	st.d    (a2),d11
	inc     a2,a0,a2
	add.d   d4,d3,d4
	sgt.d   d4,d2,d1
	beqz.d  d1,L17
	mov.d   d0,d11
	movl.a  #B4H_PH,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_PH1,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_PH2,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_YH,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_RH1,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_RH2,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_APH2,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_AH2,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_APH1,a1
	st.d    (a1),d11
	mov.d   d0,d11
	movl.a  #B4H_AH1,a1
	st.d    (a1),d11
	movs.d  #-1,d2
	jmp     L12
L13:
	movl.a  #B4H_BHi,a4
	movl.a  #B4H_BPHi,a3
	mov.d   d0,d4
	movs.d  #1,d3
	movs.d  #5,d2
L22:
	ld.d    (a3),d11
	st.d    (a4),d11
	inc     a3,a0,a3
	inc     a4,a0,a4
	add.d   d4,d3,d4
	sgt.d   d4,d2,d1
	beqz.d  d1,L22
	movl.a  #B4H_DHi,a2
	movs.a  #20,a3
	inc     a2,a3,a3
	mov.a   a3,a2
	dec     a2,a0,a2
	mov.d   d0,d4
	movs.d  #1,d3
	movs.d  #4,d2
L26:
	ld.d    (a2),d11
	st.d    (a3),d11
	dec     a2,a0,a2
	dec     a3,a0,a3
	add.d   d4,d3,d4
	sgt.d   d4,d2,d1
	beqz.d  d1,L26
	movl.a  #B4H_PH1,a1
	ld.d    (a1),d11
	movl.a  #B4H_PH2,a1
	st.d    (a1),d11
	movl.a  #B4H_PH,a1
	ld.d    (a1),d11
	movl.a  #B4H_PH1,a1
	st.d    (a1),d11
	movl.a  #B4H_RH1,a1
	ld.d    (a1),d11
	movl.a  #B4H_RH2,a1
	st.d    (a1),d11
	movl.a  #B4H_YH,a1
	ld.d    (a1),d11
	movl.a  #B4H_RH1,a1
	st.d    (a1),d11
	movl.a  #B4H_APH2,a1
	ld.d    (a1),d11
	movl.a  #B4H_AH2,a1
	st.d    (a1),d11
	movl.a  #B4H_APH1,a1
	ld.d    (a1),d11
	movl.a  #B4H_AH1,a1
	st.d    (a1),d11
	movl.a  #B4H_SZH,a1
	ld.d    (a1),d2
	add.d   d5,d2,d2
	movl.a  #B4H_PH,a1
	st.d    (a1),d2
	ld.d    (a5),d2
	add.d   d5,d2,d2
	movl.a  #B4H_YH,a1
	st.d    (a1),d2
	bnez.d  d5,L27
	mov.d   d0,d6
	jmp     L28
L27:
	movs.d  #128,d6
L28:
	movs.d  #15,d2
	asr.d   d5,d2,d9
	movl.a  #B4H_DHi,a2
	ld.d    (a2),d3
	inc     a2,a0,a2
	movl.a  #B4H_BHi,a4
	ld.d    (a4),d7
	inc     a4,a0,a4
	movl.a  #B4H_BPHi,a3
	mov.d   d0,d4
	movs.d  #15,d8
	movl.d  #32640,d10
L34:
	asr.d   d3,d8,d2
	sne.d   d9,d2,d1
	bnez.d  d1,L32
	mov.d   d6,d5
	jmp     L33
L32:
	sub.d   d0,d6,d5
L33:
	mult.d  d7,d10,d2
	asr.d   d2,d8,d3
	add.d   d5,d3,d2
	st.d    (a3),d2
	inc     a3,a0,a3
	ld.d    (a2),d3
	inc     a2,a0,a2
	ld.d    (a4),d7
	inc     a4,a0,a4
	movs.d  #1,d2
	add.d   d4,d2,d4
	movs.d  #4,d2
	sgt.d   d4,d2,d1
	beqz.d  d1,L34
	movs.d  #15,d2
	asr.d   d3,d2,d2
	sne.d   d9,d2,d1
	bnez.d  d1,L35
	mov.d   d6,d5
	jmp     L36
L35:
	sub.d   d0,d6,d5
L36:
	movl.d  #32640,d2
	mult.d  d7,d2,d3
	movs.d  #15,d2
	asr.d   d3,d2,d3
	add.d   d5,d3,d3
	st.d    (a3),d3
	movl.a  #B4H_PH,a1
	ld.d    (a1),d3
	asr.d   d3,d2,d9
	movl.a  #B4H_PH1,a1
	ld.d    (a1),d3
	asr.d   d3,d2,d6
	movl.a  #B4H_PH2,a1
	ld.d    (a1),d3
	asr.d   d3,d2,d2
	sne.d   d9,d2,d1
	bnez.d  d1,L37
	movs.d  #128,d3
	jmp     L38
L37:
	movs.d  #-128,d3
L38:
	add.d   d5,d3,d2
	movl.a  #B4H_AH2,a1
	ld.d    (a1),d3
	movl.d  #32512,d4
	mult.d  d3,d4,d3
	movs.d  #15,d4
	asr.d   d3,d4,d3
	add.d   d2,d3,d2
	movl.a  #B4H_APH2,a1
	st.d    (a1),d2
	movl.d  #12288,d3
	sgt.d   d2,d3,d1
	beqz.d  d1,L39
	movl.a  #B4H_APH2,a1
	st.d    (a1),d3
	jmp     L40
L39:
	movl.a  #B4H_APH2,a1
	ld.d    (a1),d2
	movl.d  #-12288,d3
	slt.d   d2,d3,d1
	beqz.d  d1,L40
	movl.a  #B4H_APH2,a1
	st.d    (a1),d3
L40:
	sne.d   d9,d6,d1
	bnez.d  d1,L42
	movs.d  #192,d6
	jmp     L43
L42:
	movs.d  #-192,d6
L43:
	movl.a  #B4H_AH1,a1
	ld.d    (a1),d2
	movl.d  #32640,d3
	mult.d  d2,d3,d5
	movs.d  #15,d2
	asr.d   d5,d2,d5
	add.d   d6,d5,d2
	movl.a  #B4H_APH1,a1
	st.d    (a1),d2
	movl.d  #15360,d3
	movl.a  #B4H_APH2,a1
	ld.d    (a1),d4
	sub.d   d3,d4,d3
	sgt.d   d2,d3,d1
	beqz.d  d1,L44
	movl.a  #B4H_APH1,a1
	st.d    (a1),d3
	jmp     L45
L44:
	sub.d   d0,d3,d3
	movl.a  #B4H_APH1,a1
	ld.d    (a1),d2
	slt.d   d2,d3,d1
	beqz.d  d1,L45
	movl.a  #B4H_APH1,a1
	st.d    (a1),d3
L45:
	movl.a  #B4H_BHi,a2
	movs.a  #20,a3
	inc     a2,a3,a4
	movl.a  #B4H_DHi,a2
	inc     a2,a3,a2
	mov.d   d0,d8
	ld.d    (a4),d7
	dec     a4,a0,a4
	ld.d    (a2),d3
	dec     a2,a0,a2
	mov.d   d0,d4
	movs.d  #14,d9
	movs.d  #1,d6
	movs.d  #4,d5
L50:
	mult.d  d3,d7,d2
	asr.d   d2,d9,d2
	add.d   d8,d2,d8
	ld.d    (a4),d7
	dec     a4,a0,a4
	ld.d    (a2),d3
	dec     a2,a0,a2
	add.d   d4,d6,d4
	sgt.d   d4,d5,d1
	beqz.d  d1,L50
	mult.d  d3,d7,d3
	movs.d  #14,d2
	asr.d   d3,d2,d3
	add.d   d8,d3,d8
	movl.a  #B4H_SZH,a1
	st.d    (a1),d8
	movl.a  #B4H_RH1,a1
	ld.d    (a1),d3
	movl.a  #B4H_AH1,a1
	ld.d    (a1),d4
	mult.d  d3,d4,d6
	asr.d   d6,d2,d6
	movl.a  #B4H_RH2,a1
	ld.d    (a1),d3
	movl.a  #B4H_AH2,a1
	ld.d    (a1),d4
	mult.d  d3,d4,d5
	asr.d   d5,d2,d5
	add.d   d6,d5,d2
	add.d   d2,d8,d2
	st.d    (a5),d2
	movs.d  #1,d2
L12:
	ld.d    (a31),d11
	inc     a31,a0,a31
	ld.d    (a31),d10
	inc     a31,a0,a31
	ld.d    (a31),d9
	inc     a31,a0,a31
	ld.d    (a31),d8
	inc     a31,a0,a31
	rts     
.end    block4h

.global block5h
.begin  block5h
block5h:
	mov.a   a3,a2
	movl.d  #16383,d3
	sgt.d   d2,d3,d1
	beqz.d  d1,L57
	st.d    (a2),d3
	jmp     L58
L57:
	movl.d  #-16384,d3
	slt.d   d2,d3,d1
	beqz.d  d1,L59
	st.d    (a2),d3
	jmp     L58
L59:
	st.d    (a2),d2
L58:
	movs.d  #1,d2
	rts     
.end    block5h

.global main
.begin  main
main:
	dec     a31,a0,a31
	st.d    (a31),d8
	mov.d   d0,d5
	movl.a  #IH,a1
	st.d    (a1),d5
	mov.d   d0,d5
	movl.a  #DETH,a1
	st.d    (a1),d5
	mov.d   d0,d5
	movl.a  #DH,a1
	st.d    (a1),d5
	mov.d   d0,d5
	movl.a  #YH,a1
	st.d    (a1),d5
	mov.d   d0,d5
	movl.a  #RH,a1
	st.d    (a1),d5
	mov.d   d0,d8
L62:
	movl.a  #IH,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     input_dsp
	beqz.d  d2,L63
	movl.a  #IH,a1
	ld.d    (a1),d2
	movl.a  #DETH,a1
	ld.d    (a1),d3
	movl.a  #DH,a4
	jsr     block2h
	movl.a  #IH,a1
	ld.d    (a1),d2
	mov.d   d8,d3
	movl.a  #DETH,a4
	jsr     block3h
	movl.a  #DH,a1
	ld.d    (a1),d2
	mov.d   d8,d3
	movl.a  #YH,a4
	jsr     block4h
	movl.a  #YH,a1
	ld.d    (a1),d2
	movl.a  #RH,a3
	jsr     block5h
	movl.a  #RH,a2
	movs.d  #1,d3
	movs.d  #1,d4
	jsr     output_dsp
	jmp     L62
L63:
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

.global RH
.common RH,1
.global YH
.common YH,1
.global DH
.common DH,1
.global DETH
.common DETH,1
.global IH
.common IH,1
.global B4H_SZH
.common B4H_SZH,1
.global B4H_AH2
.common B4H_AH2,1
.global B4H_AH1
.common B4H_AH1,1
.global B4H_APH2
.common B4H_APH2,1
.global B4H_APH1
.common B4H_APH1,1
.global B4H_RH2
.common B4H_RH2,1
.global B4H_RH1
.common B4H_RH1,1
.global B4H_YH
.common B4H_YH,1
.global B4H_PH2
.common B4H_PH2,1
.global B4H_PH1
.common B4H_PH1,1
.global B4H_PH
.common B4H_PH,1
.global B3H_DEPH
.common B3H_DEPH,1
.global B3H_NBPH
.common B3H_NBPH,1
.global B3H_NBH
.common B3H_NBH,1

