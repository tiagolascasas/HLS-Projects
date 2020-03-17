/**
	K-Means + k-NN
	
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
	Update point
*/
void copy(bestpoint *p, point x, dtype distance, int NFeatures);

/**
	Show a point: includes the print of the values of its features and its class
*/
void showPoint(point x, int NFeatures, const char *classif[]);
	
/**
	Show the K nearest points
*/
void showBestPoints(bestpoint *BestPoints, int KValue, int NFeatures, const char *classif[]);

/**
	Show all the points with classes determined
*/
void showPoints(point *KnownPoints, int Nknown, int NFeatures, const char *classif[]);

/**
	Initializes the K BestPoints
*/
void initializeBest(bestpoint *BestPoints, int KValue, int NFeatures, int NClasses);

#endif


