/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	April 2020
	FEUP, Porto, Portugal
*/

#ifndef DATAPROPERTIES_H
#define DATAPROPERTIES_H

/* BEGIN: parameters according to the use case. */
#ifndef NUM_FEATURES
#define NUM_FEATURES 200 //5 // number of features used
#endif

#ifndef K
#define K 3  // value of k in kNN
#endif

#ifndef NUM_CLASSES
#define NUM_CLASSES 8  // number of classes considered 
#endif

#ifndef NUM_KNOWN_POINTS
#define NUM_KNOWN_POINTS 1000000 //8 //instances of the model used after training
#endif

#define MAX_VALUE_OF_FEATURE 1

#define ftype double  // type used for features 
#define dtype double // type used for distance calculation
#define ctype char // type used for class ID, an integer


#if dtype == double
	#define MAXDISTANCE DBL_MAX
#else
	#define MAXDISTANCE FLT_MAX
#endif


/* END: parameters according to the use case. */

#endif
