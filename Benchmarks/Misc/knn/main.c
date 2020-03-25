/**
	kNN
	
	Versions 
	- v0.1, December 2016
	- v0.2, November 2019
	
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
// careful as all NUM_CLASSES+1 elements of "classif" must be initialized
// the last element represents an "unknown" class
// "a1", "a2", ... identify classes
char *classif[NUM_CLASSES+1]; //= {"a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "unknown"};  // depends on NUM_CLASSES

bestpoint BestPoints[K]; // array with the K nearest points to the pointo to classify

point KnownPoints[NUM_KNOWN_POINTS];  // the points representing the kNN instances in the model

/**
	Classes are repreented by an integer ID.
	The classsif table stores the mampping from IDs from 0 to NUM_CLASSES-1 to a string with the name of the class.
	
	This version considers names of the classes starting with an 'a' followed by a digit (maximum of 10 classes + the unknown one)
*/
void createMapIDs2Classes() {
	for(int j=0; j<NUM_CLASSES; j++) {
		classif[j]=malloc(3 * sizeof(char));
		classif[j][0]='a';
		classif[j][1]= (char) (j+48);
		classif[j][2]= '\0';
		
	}
	classif[NUM_CLASSES] = "unknown";
	
	/*
	for(int j=0; j<NUM_CLASSES+1; j++) {
		printf("class: %s\n", classif[j]);
	}
	*/
}

/**
	Create point to classify
*/
point newPoint(int NFeatures, int IDUnknown)  {
	point x;
	for(int j=0; j<NFeatures; j++) {
		x.features[j] = getRandFeatureValue();  // from 0 to MAX_VALUE_OF_FEATURE
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
   
   	createMapIDs2Classes();
   	
   	//KnownPoints = (point *) malloc(NKnowns*sizeof(point));
   
	printf("Initializing data points...\n");
	initializekNNModel(NKnowns, KnownPoints, NFeatures, NClasses);  // includes kmeans
	//showPoints(KnownPoints, NKnowns, NFeatures, classif);
	
	// initialize the data structures (array) with the K best points
	initializeBest(BestPoints, KValue, NFeatures, NClasses);
   	//showBestPoints(BestPoints, KValue);
	printf("\nend initialization\n");
	
	// Create a random point to classify
	//printf("Point x to classify: \n");
	point x = newPoint(NFeatures, NClasses);
	//showPoint(x, NFeatures, classif);

	// Run knn
	printf("\n%d-NN considering, %d classes, %d instances learned in model, each one with %d features\n", KValue, NClasses, NKnowns, NFeatures);	
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
