/*
  This is the 8x8 DCT (Discrete Cosine Transform) algorithm.

  Source: ftp://ftp.ti.com/pub/tms320bbs/c62xfiles/dct.asm

  DSP IMPLEMENTATION
  Cycles = 48 + 160 * num_fdcts
  for num_fdcts >= 1
  208 cycles or 1.04 µs for one 8x8
  Block of Data


  MAIN differences:
  - pointer-free version
  - added two auxiliar arrays:
  dct_io_ptr -> |ROW| -> dct_io_tmp -> |COL| -> dct_o

  An improvement can be done in order to use always the array dct_io_tmp of size 64 
  and so mapped to internal memories (faster accesses).
  However, such improvement needs that the image are traversed with an outer loop
  which is not so good since the DCT does not fit entirely in a realistic XPP.

	Modifications by João MP Cardoso, 2002
*/

#include "stdio.h"
#include "math.h"

#define NUM_DCTS 4 // 5400 NTSC: 720x480 => 90 x 60 blocks of 8x8; if 1 then 8x8 DCT

#define N 8 // fixed
#define M N*N

#define SIZE NUM_DCTS*M
                                             
short    dct_io_ptr[SIZE];  
short    dct_o[SIZE]; 


void fdct(short dct_io_ptr[SIZE], short dct_o[SIZE], int num_fdcts)  {
  	int tmp;
	short    dct_io_tmp[SIZE];  
               
	/* -------------------------------------------------------- /    
    /  Set up the cosine coefficients c0..c7.                  /    
    / -------------------------------------------------------- */    
  	const unsigned short c1 = 0x2C62, c3 = 0x25A0;                    
  	const unsigned short c5 = 0x1924, c7 = 0x08D4;                    
  	const unsigned short c0 = 0xB505, c2 = 0x29CF;                    
  	const unsigned short c6 = 0x1151;                                 
                                                                           
  	/* -------------------------------------------------------- /    
     /  Intermediate calculations.                              /    
     / -------------------------------------------------------- */    
  	short f0, f1, f2, f3,f4, f5, f6, f7;       // Spatial domain samples.       
  	int   g0, g1, h0, h1,p0, p1;               // Even-half intermediate.     
  	short r0, r1;               // Even-half intermediate.     
  	int   P0, P1, R0, R1;       // Even-half intermediate.         
  	short g2, g3, h2, h3;       // Odd-half intermediate.           
  	short q0a,s0a,q0, q1,s0, s1;               // Odd-half intermediate.          
  	short Q0, Q1, S0, S1;       // Odd-half intermediate.       
  	int   F0, F1, F2, F3, F4, F5, F6, F7;       // Freq. domain results. 
  	int   F0r,F1r,F2r,F3r,F4r,F5r,F6r,F7r;      // Rounded, truncated results.   
  
  	/* -------------------------------------------------------- /    
     /  Input and output pointers, loop control.                /    
     / -------------------------------------------------------- */    
  	unsigned i, j, i_1;                                                  
    
                                                 
  	/* -------------------------------------------------------- /    
    /  Outer vertical loop -- Process each 8x8 block.          /    
    / -------------------------------------------------------- */    
  	//dct_io_ptr = dct_data;    
  	i_1 = 0;
  	for (i = 0; i < num_fdcts; i++) {                                                                 
    	/* ---------------------------------------------------- /    
       	/  Perform Vert 1-D FDCT on columns within each block. /    
       	/ ---------------------------------------------------- */    
    	for (j = 0; j < N; j++) {                                                             
      		/* ------------------------------------------------ /    
	 		/  Load the spatial-domain samples.                /    
	 		/ ------------------------------------------------ */    
      f0 = dct_io_ptr[ 0+i_1];                                      
      f1 = dct_io_ptr[ 8+i_1];                                      
      f2 = dct_io_ptr[16+i_1];                                      
      f3 = dct_io_ptr[24+i_1];                                      
      f4 = dct_io_ptr[32+i_1];                                      
      f5 = dct_io_ptr[40+i_1];                                      
      f6 = dct_io_ptr[48+i_1];                                      
      f7 = dct_io_ptr[56+i_1];                                      
                                                                           
      /* ------------------------------------------------ /    
	 /  Stage 1:  Separate into even and odd halves.    /    
	 / ------------------------------------------------ */    
      g0 = f0 + f7;               h2 = f0 - f7;                 
      g1 = f1 + f6;               h3 = f1 - f6;                 
      h1 = f2 + f5;               g3 = f2 - f5;                 
      h0 = f3 + f4;               g2 = f3 - f4;                 
      
      /* ------------------------------------------------ /    
	 /  Stage 2                                         /    
	 / ------------------------------------------------ */    
      p0 = g0 + h0;               r0 = g0 - h0;                 
      p1 = g1 + h1;               r1 = g1 - h1;                 
      q1 = g2;                    s1 = h2;                      
      
      s0a= h3 + g3;               q0a= h3 - g3;                   
      s0 = (s0a * c0 + 0x7FFF) >> 16;                           
      q0 = (q0a * c0 + 0x7FFF) >> 16;                           
                                                                           
      /* ------------------------------------------------ /    
	 /  Stage 3                                         /    
	 / ------------------------------------------------ */    
      P0 = p0 + p1;             P1 = p0 - p1;                 
      R1 = c6 * r1 + c2 * r0;     R0 = c6 * r0 - c2 * r1;       
      
      Q1 = q1 + q0;               Q0 = q1 - q0;                 
      S1 = s1 + s0;               S0 = s1 - s0;                 
      
      /* ------------------------------------------------ /    
	 /  Stage 4                                         /    
	 / ------------------------------------------------ */    
      F0 = P0;                    F4 = P1;                      
      F2 = R1;                    F6 = R0;                      
      
      F1 = c7 * Q1 + c1 * S1;     F7 = c7 * S1 - c1 * Q1;       
      F5 = c3 * Q0 + c5 * S0;     F3 = c3 * S0 - c5 * Q0;       
      
      /* ------------------------------------------------ /    
	 /  Store the frequency domain results.             /    
	 / ------------------------------------------------ */    
      dct_io_tmp[ 0+i_1] = F0;                                      
      dct_io_tmp[ 8+i_1] = F1 >> 13;                                
      dct_io_tmp[16+i_1] = F2 >> 13;                                
      dct_io_tmp[24+i_1] = F3 >> 13;                                
      dct_io_tmp[32+i_1] = F4;                                      
      dct_io_tmp[40+i_1] = F5 >> 13;                                
      dct_io_tmp[48+i_1] = F6 >> 13;                                
      dct_io_tmp[56+i_1] = F7 >> 13;                                
      
      //dct_io_ptr++; 
      i_1++;                                            
    }                                                             
    /* ---------------------------------------------------- /    
       /  Update pointer to next 8x8 FDCT block.              /    
       / ---------------------------------------------------- */    
    //dct_io_ptr += 56;         
    i_1 += 56;                                    
  }                                                               
  
                                                                 
  /* -------------------------------------------------------- /    
     /  Perform Horizontal 1-D FDCT on each 8x8 block.          /    
     / -------------------------------------------------------- */    
  //dct_io_ptr = dct_data;    
  i_1 = 0;
  for (i = 0; i < N*num_fdcts; i++) {                                                                                         
    // ---------------------------------------------------- /    
    //  Load the spatial-domain samples.                    /    
    // ---------------------------------------------------- /  
    f0 = dct_io_tmp[0+i_1];                                           
    f1 = dct_io_tmp[1+i_1];                                           
    f2 = dct_io_tmp[2+i_1];                                           
    f3 = dct_io_tmp[3+i_1];                                           
    f4 = dct_io_tmp[4+i_1];                                           
    f5 = dct_io_tmp[5+i_1];                                           
    f6 = dct_io_tmp[6+i_1];                                           
    f7 = dct_io_tmp[7+i_1];                                           
                                                                           
    // ---------------------------------------------------- /    
    //  Stage 1:  Separate into even and odd halves.        /    
    // ---------------------------------------------------- /    
    g0 = f0 + f7;               h2 = f0 - f7;                     
    g1 = f1 + f6;               h3 = f1 - f6;                     
    h1 = f2 + f5;               g3 = f2 - f5;                     
    h0 = f3 + f4;               g2 = f3 - f4;                     
    
    // ---------------------------------------------------- /    
    //  Stage 2                                             /    
    // ---------------------------------------------------- /    
    p0 = g0 + h0;               r0 = g0 - h0;                     
    p1 = g1 + h1;               r1 = g1 - h1;                     
    q1 = g2;                    s1 = h2;                          
    
    s0a= h3 + g3;               q0a= h3 - g3;                     
    q0 = (q0a * c0 + 0x7FFF) >> 16;                               
    s0 = (s0a * c0 + 0x7FFF) >> 16;                               
    
    // ---------------------------------------------------- /    
    //  Stage 3                                             /    
    // ---------------------------------------------------- /    
    P0 = p0 + p1;               P1 = p0 - p1;                     
    R1 = c6 * r1 + c2 * r0;     R0 = c6 * r0 - c2 * r1;           
    
    Q1 = q1 + q0;               Q0 = q1 - q0;                     
    S1 = s1 + s0;               S0 = s1 - s0;                     
    
    // ---------------------------------------------------- /    
    //  Stage 4                                             /    
    // ---------------------------------------------------- /    
    F0 = P0;                    F4 = P1;                          
    F2 = R1;                    F6 = R0;                          
    
    F1 = c7 * Q1 + c1 * S1;     F7 = c7 * S1 - c1 * Q1;           
    F5 = c3 * Q0 + c5 * S0;     F3 = c3 * S0 - c5 * Q0;           
    
    // ---------------------------------------------------- /    
    //  Round and truncate values.                          /    
    //                                                      /    
    //  Note: F0 and F4 have different rounding since no    /    
    //  MPYs have been applied to either term.  Also, F0's  /    
    //  rounding is slightly different to offset the        /    
    //  truncation effects from the horizontal pass (which  /    
    //  does not round).                                    /    
    // ---------------------------------------------------- /    
    F0r = (F0 + 0x0006) >>  3;                                    
    F1r = (F1 + 0x7FFF) >> 16;                                    
    F2r = (F2 + 0x7FFF) >> 16;                                    
    F3r = (F3 + 0x7FFF) >> 16;                                    
    F4r = (F4 + 0x0004) >>  3;                                    
    F5r = (F5 + 0x7FFF) >> 16;                                    
    F6r = (F6 + 0x7FFF) >> 16;                                    
    F7r = (F7 + 0x7FFF) >> 16;                                    
    
    // ---------------------------------------------------- /    
    //  Store the results                                   /    
    // ---------------------------------------------------- /    
    dct_o[0+i_1] = F0r;                                          
    dct_o[1+i_1] = F1r;                                          
    dct_o[2+i_1] = F2r;                                          
    dct_o[3+i_1] = F3r;                                          
    dct_o[4+i_1] = F4r;                                          
    dct_o[5+i_1] = F5r;                                          
    dct_o[6+i_1] = F6r;                                          
    dct_o[7+i_1] = F7r;                                          
    
    // ---------------------------------------------------- /    
    //  Update pointer to next FDCT row.                    /    
    // ---------------------------------------------------- /    
    //dct_io_ptr += 8;
    i_1 += 8;
  }                                                                   
}


main() {
  	int i;

	/* input data */
  	for (i = 0; i < NUM_DCTS*M; i++) {
    	dct_io_ptr[i] = i;    
  	}


  	fdct(dct_io_ptr, dct_o, NUM_DCTS);  
                   

  	/* write data stream to output */
  	// for now just calculate a checksum
  	long checksum = 0;
	for (i = 0; i < NUM_DCTS*M; i++) {
      	checksum += abs(dct_o[i]);
  	}
	printf("checksum = %ld\n",checksum);
  	if(checksum == 4844)
		printf("RIGHT!\n");
	else
		printf("WRONG!\n");
}




