/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	April 2020
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
void updateBest(dtype distance, ctype classifID, dtype BestPointsDistances[K], ctype BestPointsClasses[K]);
	
/**
	kNN function without classifying but returning the k nearest points
	We use here a linear search.
*/
ctype knn(ftype xFeatures[NUM_FEATURES], ftype knownFeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype knownClasses[NUM_KNOWN_POINTS]);

/**
	Classify based on the K BestPoints returned by the kNN function
*/
ctype classify1NN(ctype BestPointsClasses[K]); // specialized version for K=1

ctype classify3NN(ctype BestPointsClasses[K], dtype BestPointsDistances[K]); // specialized version for K=3

ctype classifyKNN(ctype BestPointsClasses[K], dtype BestPointsDistances[K]); // generic version fot k>=1

#endif
