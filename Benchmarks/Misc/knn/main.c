/**
	kNN
	
	Versions 
	- v0.1, November 2020
	
	by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	SPeCS, FEUP.DEI, Porto, Portugal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dataproperties.h"  // where the definitions are located
#include "knn.h"

#define WINDOWS_TIMING // for considering timing measurements in Windows

#ifdef WINDOWS_TIMING
	#include <windows.h>
#endif

// constants are defines in dataproperties.h


// the points representing the kNN instances in the model
ftype instancesXfeatures[NUM_KNOWN_POINTS][NUM_FEATURES];
ctype classifIDs[NUM_KNOWN_POINTS]; // Classes are repreented by an integer ID.

/**
	Create point to classify
*/
void newPoint(ftype xFeatures[NUM_FEATURES], int IDUnknown)  {
	for(int j=0; j<NUM_FEATURES; j++) {
		xFeatures[j] = getRandFeatureValue();  // from 0 to MAX_VALUE_OF_FEATURE
	}
}

int main() {

#ifdef WINDOWS_TIMING
	 __int64 freq, start, end;
    long elapsedTime;
	
    // get ticks per second
    QueryPerformanceFrequency( ( LARGE_INTEGER* )&freq );
    
    // start timer
    QueryPerformanceCounter( ( LARGE_INTEGER* )&start );
#endif
   	
   
	printf("Initializing data points...\n");
	initializekNNModel(instancesXfeatures, classifIDs);
	//showPoints(KnownPoints, NKnowns, NFeatures, classif);
	printf("\nend initialization\n");


	ftype xFeatures[NUM_FEATURES];
			
	// Create a random point to classify
	//printf("Point x to classify: \n");
	newPoint(xFeatures, NUM_CLASSES);
	//showPoint(x, NFeatures, classif);

	// Run knn
	printf("\n%d-NN considering, %d classes, %d instances learned in model, each one with %d features\n", K, NUM_CLASSES, NUM_KNOWN_POINTS, NUM_FEATURES);	
	printf("Executing knn...\n");
	ctype classifyID = knn(xFeatures, instancesXfeatures, classifIDs); // classify
	
	printf("End knn\n");

	// show the best points		
   	//showBestPoints(BestPoints);
   	
   	printf("\n#### kNN classification of x: %d \n", classifyID);
	

#ifdef WINDOWS_TIMING	
	QueryPerformanceCounter( ( LARGE_INTEGER* )&end );
    elapsedTime = ( ( end - start ) * 1000 ) / freq;
    printf( "It took %ld ms\n", elapsedTime );
#endif

	return 0;
}
