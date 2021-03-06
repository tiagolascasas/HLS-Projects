/**
	K-Means + k-NN
	
	Version by Jo�o MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#ifndef DATAPROPERTIES_H
#define DATAPROPERTIES_H

/* BEGIN: parameters according to the use case. */
#define NUM_FEATURES 20 // number of features used
#define K 3  // value of k in kNN
#define NUM_CLASSES 8  // number of classes considered 
#define NUM_KNOWN_POINTS 100 

#define MAX_VALUE_OF_FEATURE 1
#define KMEANS_ERROR_TOLERANCE  0.0001  //error tolerance for kmeans

#define ftype double  // type used for features 
#define dtype double // type used for distance calculation
#define ctype char // type used for class ID


#if dtype == double
	#define MAXDISTANCE DBL_MAX
#else
	#define MAXDISTANCE FLT_MAX
#endif

typedef struct {
	ftype features[NUM_FEATURES];
	ctype classifID; // = "null";
} point;

/* END: parameters according to the use case. */


typedef struct {
	point x;
	dtype distance; // = MAXDISTANCE;
} bestpoint;

#endif


