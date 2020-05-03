// if manual temporal partitioning is used
#define TP

#ifdef TP
#define TP1
#define TP2
#define TP3
#define TP4
#endif


#include "XPP.h"


#define N 8
#define M N*N

int InIm[N][N];
int TempBlock[N][N];
int CosTrans[N][N];
int OutIm[N][N];

const int CosBlock[8][8] = {88, 122, 115, 103, 88, 69, 47, 24,
			    88, 103, 47, -24, -88, -122, -115, -69,
			    88, 69, -47, -122, -88, 24, 115, 103,
			    88, 24, -115, -69, 88, 103, -47, -122,
			    88, -24, -115, 69, 88, -103, -47, 122,
			    88, -69, -47, 122, -88, -24, 115, -103,
			    88, -103, 47, 24, -88, 122, -115, 69,
			    88, -122, 115, -103, 88, -69, 47, -24};

main() {
  int i, j, k, tmp, temp;

  /* read data stream (M length) from port 1 */
  for(i=0;i<N; i++) {
    for(j=0;j<N; j++) {
      XPP_getstream(1, 0, &tmp);
      InIm[i][j] = tmp;
    }
  }
  
#ifdef TP1 
  XPP_next_conf();
#endif
 
  
  /* this matrix transpose can be stored in a constant array */
  for(i=0; i<N;i++)
    for(j=0;j<N;j++)
      CosTrans[j][i] = CosBlock[i][j];
  
#ifdef TP2 
  XPP_next_conf();
#endif
  
  for(i=0; i<N;i++)
    for(j=0;j<N;j++) {
      temp = 0;
      for(k=0;k<N;k++)
	temp += InIm[i][k] * CosTrans[k][j];
      TempBlock[i][j] = temp;
    }
  
#ifdef TP3 
  XPP_next_conf();
#endif
  
  for(i=0; i<N;i++)
    for(j=0;j<N;j++) {
      temp = 0;
      for(k=0;k<N;k++)
	temp += TempBlock[k][j] * CosBlock[i][k];
      OutIm[i][j] = temp;
    }

#ifdef TP4 
  XPP_next_conf();
#endif
 
  /* write data stream to port 4 */
  for(i=0;i<N; i++) {
    for(j=0;j<N; j++) {
      XPP_putstream(4, 0, OutIm[i][j]);
    }
  }

}







