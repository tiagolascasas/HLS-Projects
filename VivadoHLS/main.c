/**
	K-Means + k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dataproperties.h"  // where the definitions are located
#include "kmeansmain.h"
#include "knn.h"

//#define WINDOWS_TIMING // for considering timing measurements in Windows


#ifdef WINDOWS_TIMING
	#include <windows.h>
#endif

// constants are defines in dataproperties.h
// careful as all NUM_CLASSES+1 elements of "classif" must be initialized
// the last element represents an "unknown" class
// "a1", "a2", ... identify classes
const char *classif[NUM_CLASSES+1] = {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "unknown"};  // depends on NUM_CLASSES

bestpoint BestPoints[K]; // array with the K nearest points to the pointo to classify

point KnownPoints[NUM_KNOWN_POINTS];  // the points to be classified by kmeans in NUM_CLASSES classes

/**
	Create point to classify
*/
point newPoint(int NFeatures, int IDUnknown)  {
	point x;
	for(int j=0; j<NFeatures; j++) {
		x.features[j] = rand() % 50;  // from 0 to 49
	}
	x.classifID = IDUnknown;
	return x;
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
    
	int NKnowns = NUM_KNOWN_POINTS;
	int NFeatures = NUM_FEATURES;
	int KValue = K;
	int NClasses = NUM_CLASSES;
   
   	//KnownPoints = (point *) malloc(NKnowns*sizeof(point));
   
	printf("Executing kmeans...\n");
	initializeKnowns(NKnowns, KnownPoints, NFeatures, NClasses);  // includes kmeans
	// showPoints(KnownPoints, NKnowns, classif);
	printf("\nEnd kmeans\n");
	
	// initialize the data structures (array) with the K best points
	initializeBest(BestPoints, KValue, NFeatures, NClasses);
   	//showBestPoints(BestPoints, KValue);
	
	// Create a random point to classify
	printf("Point x to classify: \n");
	point x = newPoint(NFeatures, NClasses);
	showPoint(x, NFeatures, classif);

	// Run knn
	printf("\n%d-NN considering, %d classes, %d preclassified points, each one with %d features\n", KValue, NClasses, NKnowns, NFeatures);	
	printf("Executing knn...\n");
	knn(x, KnownPoints, NKnowns, BestPoints, NFeatures, KValue); // classify
	printf("End knn\n");

	// show the best points		
   	//showBestPoints(BestPoints);
   	
   	// classify the point based on the K nearest points
   	ctype classifyID;
	switch(KValue) {
		case 1: classifyID = classify1NN(BestPoints); break;
		case 3: classifyID = classify3NN(BestPoints); break;
		default: classifyID = classifyKNN(BestPoints, NFeatures, KValue);
	} 
   	x.classifID = classifyID;
	printf("\n#### kNN classification of x: %s \n", classif[(int) classifyID]);

#ifdef WINDOWS_TIMING	
	QueryPerformanceCounter( ( LARGE_INTEGER* )&end );
    elapsedTime = ( ( end - start ) * 1000 ) / freq;
    printf( "It took %ld ms\n", elapsedTime );
#endif

	return 0;
}


