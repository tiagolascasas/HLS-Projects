/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#ifndef KNN_H
#define KNN_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "dataproperties.h"
#include "utils.h"
#include "macros.h"


/*
	Update the set of best points so far.
*/
void updateBest(dtype distance, point known, bestpoint *BestPoints, int NFeatures, int KValue);
	
/**
	kNN function without classifying but returning the k nearest points
	We use here a linear search.
*/
void knn(point x, point *known, int Nknown, bestpoint *BestPoints, int NFeatures, int KValue);

/**
	Classify based on the K BestPoints returned by the kNN function
*/
ctype classify1NN(bestpoint *BestPoints); // specialized version for K=1

ctype classify3NN(bestpoint *BestPoints); // specialized version for K=3

ctype classifyKNN(bestpoint *BestPoints, int NClasses, int KValue); // generic version fot k>=1

#endif
