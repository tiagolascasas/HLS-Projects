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
void initializekNNModel(int Nknown, point *Known, int NFeatures, int NClasses) {

	// initialize the array of the data points to be preclassified: database of classified points
	// this can be moved to a function
	for(int i=0; i<Nknown; i++) {
		point *x = &Known[i];
		for(int j=0; j<NFeatures; j++) {
			x->features[j] = getRandFeatureValue();  // from 0 to MAX_VALUE_OF_FEATURE
			//printf("feature %e\n", x->features[j]);
		}
		// assign a random class ID to each vector i
		x->classifID = (ctype) randInt(0, NClasses);
	}
}

/**
	Update point
*/
void copy(bestpoint *p, point x, dtype distance, int NFeatures) {
	point *p1 = &(p->x);
	
	p1->classifID = x.classifID;
	
	// copy features
	for(int j=0; j<NFeatures; j++) {
		p1->features[j] = x.features[j];
	}
	p->distance = distance;
}

/**
	Show a point: includes the print of the values of its features and its class
*/
void showPoint(point x, int NFeatures, char *classif[])  {
		for(int j=0; j<NFeatures; j++) {
			printf("--> feature %d: %e \n", j, x.features[j]);
		}
		printf("--> class: %s\n", classif[(int) x.classifID]);
}
	
/**
	Show the K nearest points
*/
void showBestPoints(bestpoint *BestPoints, int KValue, int NFeatures, char *classif[]) {
	for(int i=0; i<KValue; i++) {
		printf("Best point %d: \n", i);
		showPoint(BestPoints[i].x, NFeatures, classif);
		printf("--> distance = %e: \n", BestPoints[i].distance);	
	}
}

/**
	Show all the points with classes determined
*/
void showPoints(point *KnownPoints, int Nknown, int NFeatures, char *classif[]) {
	for(int i=0; i<Nknown; i++) {
		printf("Point %d: \n", i);
		showPoint(KnownPoints[i], NFeatures, classif);
	}
}

/**
	Initializes the K BestPoints
*/
void initializeBest(bestpoint *BestPoints, int KValue, int NFeatures, int NClasses) {
	
	for(int i=0; i<KValue; i++) {
		bestpoint *bp = &BestPoints[i];
		bp->distance = MAXDISTANCE;
		point *x = &(bp->x);
		for(int j=0; j<NFeatures; j++) {
			x->features[j] = 0;
		}
		x->classifID = NClasses; // unknown
		
	}
}
