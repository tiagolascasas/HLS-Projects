/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
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
void initializekNNModel(int Nknown, point *Known, int NFeatures, int NClasses);

/**
	Update point
*/
void copy(bestpoint *p, point x, dtype distance, int NFeatures);

/**
	Show a point: includes the print of the values of its features and its class
*/
void showPoint(point x, int NFeatures, char *classif[]);
	
/**
	Show the K nearest points
*/
void showBestPoints(bestpoint *BestPoints, int KValue, int NFeatures, char *classif[]);

/**
	Show all the points with classes determined
*/
void showPoints(point *KnownPoints, int Nknown, int NFeatures, char *classif[]);

/**
	Initializes the K BestPoints
*/
void initializeBest(bestpoint *BestPoints, int KValue, int NFeatures, int NClasses);

#endif
