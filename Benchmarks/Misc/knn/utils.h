/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	April 2020
	FEUP, Porto, Portugal
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "dataproperties.h"


/**
	Return a random integer number from min to max).
*/	
int randInt(int min, int max);

/**
	Return a random double number from min to max).
*/	
double randDouble(double min, double max);

/**
	Return a random float number from min to max).
*/	
float randFloat(float min, float max);
 
  
/**
 	Return a random value for a feature.
*/
 ftype getRandFeatureValue();

/**
	Initializes the kNN model with random values.
	
	Nknown: number of points
	NFeatures: number of features in each point
	NClasses: desired number of classes
	*Known: the data structure with the points
*/
//void initializekNNModel(int Nknown, point *Known, int NFeatures, int NClasses);
void initializekNNModel(ftype instancesXfeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype classifIDs[NUM_KNOWN_POINTS]);


/**
	Show a point: includes the print of the values of its features and its class
*/
void showPoint(ftype xFeatures[NUM_FEATURES], ctype classifID);
	
/**
	Show the K nearest points
*/
void showBestPoints(ctype BestPointsClasses[K], dtype BestPointsDistances[K]);

/**
	Show all the points with classes determined
*/
void showPoints(ftype instancesXfeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype classifIDs[NUM_KNOWN_POINTS]);

/**
	Initializes the K BestPoints
*/
void initializeBest(ctype BestPointsClasses[K], ftype BestPointsDistances[K]);

#endif
