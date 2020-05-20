/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#include "utils.h"

/**
	Return a random integer number from min to max).
*/	
int randInt(int min, int max) {
	int number = (int) (min + rand() / (RAND_MAX / (max - min + 1) + 1));
	return number;
}

/**
	Return a random double number from min to max).
*/	
double randDouble(double min, double max) {
	double number = (double) (min + rand() / (RAND_MAX / (max - min + 1) + 1));
	return number;
}

/**
	Return a random float number from min to max).
*/	
float randFloat(float min, float max) {
	int number = (float) (min + rand() / (RAND_MAX / (max - min + 1) + 1));
	return number;
}
 
/**
 	Return a random value for a feature.
*/
 ftype getRandFeatureValue() {
 	ftype value;
	 #if ftype == double 
		value = (ftype) randDouble(0,MAX_VALUE_OF_FEATURE);  // from 0 to MAX_VALUE_OF_FEATURE
	#elif ftype == float 
		value = (ftype) randFloat(0,MAX_VALUE_OF_FEATURE);  // from 0 to MAX_VALUE_OF_FEATURE
	#elif ftype == int 
		value = (ftype) randInt(0,MAX_VALUE_OF_FEATURE);  // from 0 to MAX_VALUE_OF_FEATURE
	#else 
		value = (ftype) randDouble(0,MAX_VALUE_OF_FEATURE);  // from 0 to MAX_VALUE_OF_FEATURE
	#endif
	return value;
}
		
/**
	Initializes the kNN model with random values.
	
	Nknown: number of points
	NFeatures: number of features in each point
	NClasses: desired number of classes
	*Known: the data structure with the points
*/
void initializekNNModel(ftype instancesXfeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype classifIDs[NUM_KNOWN_POINTS]) {

	// initialize the array of the data points to be preclassified: database of classified points
	// this can be moved to a function
	for(int i=0; i<NUM_KNOWN_POINTS; i++) {
		for(int j=0; j<NUM_FEATURES; j++) {
			instancesXfeatures[i][j] = getRandFeatureValue();  // from 0 to MAX_VALUE_OF_FEATURE
			//printf("feature %e\n", x->features[j]);
		}
		// assign a random class ID to each vector i
		classifIDs[i] = (ctype) randInt(0, NUM_CLASSES);
	}
}


/**
	Show a point: includes the print of the values of its features and its class
*/
void showPoint(ftype xFeatures[NUM_FEATURES], ctype classifID)  {
		for(int j=0; j<NUM_FEATURES; j++) {
			printf("--> feature %d: %e \n", j, xFeatures[j]);
		}
		printf("--> class: %d\n", classifID);
}
	
/**
	Show the K nearest points
*/
void showBestPoints(ctype BestPointsClasses[K], dtype BestPointsDistances[K]) {
	for(int i=0; i<K; i++) {
		printf("Best point %d: \n", i);
		printf("--> class: %d\n", BestPointsClasses[i]);
		printf("--> distance = %e: \n", BestPointsDistances[i]);	
	}
}

/**
	Show all the points with classes determined
*/
void showPoints(ftype instancesXfeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype classifIDs[NUM_KNOWN_POINTS]) {
	for(int i=0; i<NUM_KNOWN_POINTS; i++) {
		printf("Point %d: \n", i);
		showPoint(instancesXfeatures[i], classifIDs[i]);
	}
}

/**
	Initializes the K BestPoints
*/
void initializeBest(ctype BestPointsClasses[K], dtype BestPointsDistances[K]) {
	for(int i=0; i<K; i++) {
		BestPointsDistances[i] = MAXDISTANCE;
		/*point *x = &(bp->x);
		for(int j=0; j<NFeatures; j++) {
			x->features[j] = 0;
		}*/
		BestPointsClasses[i] = NUM_CLASSES; // unknown
	}
}
