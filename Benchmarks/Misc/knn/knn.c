/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#include "knn.h"


/*
	Update the set of k best points so far.
	Points represent instances in the kNN model.
	Those instances are the ones used in a previous learning phase.
*/
void updateBest(dtype distance, point known, bestpoint *BestPoints, int NFeatures, int KValue) {
	dtype max = 0;
	int index=0;

	//find the worst point in the BestPoints
	for(int i=0; i<KValue; i++) {
		if(BestPoints[i].distance > max) {
			max = BestPoints[i].distance;
			index = i;
		}
	}
	// if the point is better (shorter distance) than the worst one (longer distance) in the BestPoints
	// update BestPoints substituting the wrost one
	if(distance < max) {
		//printf("point is better %e\n", distance);
		copy(&BestPoints[index], known, distance, NFeatures);
	}
}

/**
	kNN function without classifying but returning the k nearest points
	We use here a linear search.
*/
void knn(point x, point *known, int Nknown, bestpoint *BestPoints, int NFeatures, int KValue) {

	// perform the Euclidean distance between the point to classify and each one in the model
	// and update the k best points if needed
	for(int i=0; i<Nknown; i++) {
		dtype distance = (dtype) 0;
		
		// perform Euclidean distance
		for(int j=0; j<NFeatures; j++) {
			distance += sqr((dtype)x.features[j]-(dtype)known[i].features[j]);
		}
		distance = sqrt(distance);
		//printf("distance %e\n", distance);
		
		// maintains the k best points updated
		updateBest(distance, known[i], BestPoints, NFeatures, KValue);
	}
}

/**
	Classify based on the K BestPoints returned by the kNN function
	Specialized code when using K = 1
*/
ctype classify1NN(bestpoint *BestPoints) {
	point p = BestPoints[0].x; // there is only one point	
	return p.classifID;
}

/**
	Classify based on the K BestPoints returned by the kNN function
	Specialized code when using K = 3
*/
ctype classify3NN(bestpoint *BestPoints) {
		
		point p1 = BestPoints[0].x;
		dtype d1 = BestPoints[0].distance;
		ctype c1 = p1.classifID;
		point p2 = BestPoints[1].x;
		dtype d2 = BestPoints[1].distance;
		ctype c2 = p2.classifID;
		point p3 = BestPoints[2].x;
		dtype d3 = BestPoints[2].distance;
		ctype c3 = p3.classifID;
		
		int classID;
		
		if(c1 == c2) {
			classID = c1;
		} else if(c1 == c3) {
			classID = c1;
		} else if(c2 == c3) {
			classID = c2;
		} else {
			dtype mindist = d1;
			classID = c1;
			if(mindist > d2) {
				mindist = d2;
				classID = c2;
			}
			if(mindist > d3) {
				mindist = d3;
				classID = c3;
			}
		}	
	return classID;
}

/**
	This function can be heavely optimized by using specialized versions according to the value of K.
	K=1, K=2, K=3, etc. Previous functions are examples of specialized code for K=1 and K=3.
*/
ctype classifyKNN(bestpoint *BestPoints, int NClasses, int KValue) {
	unsigned char histogram[NClasses+1];
	for(int i=0; i<NClasses+1; i++) 
		histogram[i]=0;
	
	dtype min_distance = MAXDISTANCE;
	
	for(int i=0; i<KValue; i++) {
		point p = BestPoints[i].x;
		if(BestPoints[i].distance < min_distance) min_distance = BestPoints[i].distance;
		
		histogram[(unsigned int) p.classifID] += 1;
	}
	unsigned char max = 0;
	ctype classID = NClasses ; // the default is the unknwown
	for(int i=0; i<NClasses +1; i++) {
		if(histogram[i] > max) {
			max = histogram[i];
			classID = i;
		}
	}		
	//printf("\n#### Final kNN classification: %s: \n", classif[index]);
	return classID;
}

