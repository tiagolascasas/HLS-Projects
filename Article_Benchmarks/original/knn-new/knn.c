/**
	k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	April 2020
	FEUP, Porto, Portugal
*/

#include "knn.h"


/*
	Update the set of k best points so far.
	Points represent instances in the kNN model.
	Those instances are the ones used in a previous learning phase.
*/
void updateBest(dtype distance, ctype classifID, dtype BestPointsDistances[K], ctype BestPointsClasses[K]) {
	dtype max = 0;
	int index =0;

	//find the worst point in the BestPoints
	for(int i=0; i<K; i++) {
		
		/*if(BestPointsDistances[i] > max) {
			max = BestPointsDistances[i];
			index = i;
		}*/
		dtype dbest = BestPointsDistances[i];
		dtype max_tmp = max;
		max = (dbest > max_tmp) ? dbest : max; 
		index = (dbest > max_tmp) ? i : index;
	}
	// if the point is better (shorter distance) than the worst one (longer distance) in the BestPoints
	// update BestPoints substituting the wrost one
	
	/*if(distance < max) {
		//printf("point is better %e\n", distance);
		BestPointsDistances[index] = distance;
		BestPointsClasses[index] = classifID;
	}*/
	dtype dbest = BestPointsDistances[index];
	ctype cbest = BestPointsClasses[index];
	
	BestPointsDistances[index] = (distance < max) ? distance : dbest;
	BestPointsClasses[index] = (distance < max) ? classifID : cbest;
}

/**
	kNN function without classifying but returning the k nearest points
	We use here a linear search.
*/
ctype knn(ftype xFeatures[NUM_FEATURES], ftype knownFeatures[NUM_KNOWN_POINTS][NUM_FEATURES], ctype knownClasses[NUM_KNOWN_POINTS]) {

	dtype BestPointsDistances[K]; // array with the distances of the K nearest points to the point to classify
	ctype BestPointsClasses[K]; // array with the classes of the K nearest points to the point to classify


	// initialize the data structures (array) with the K best points
	initializeBest(BestPointsClasses, BestPointsDistances);


	// perform the Euclidean distance between the point to classify and each one in the model
	// and update the k best points if needed
	for(int i=0; i<NUM_KNOWN_POINTS; i++) {
		dtype distance = (dtype) 0;
		
		// perform Euclidean distance
		for(int j=0; j<NUM_FEATURES; j++) {
			distance += sqr((dtype) xFeatures[j]-(dtype) knownFeatures[i][j]);
		}
		distance = sqrt(distance);
		//printf("distance %e\n", distance);
		
		// maintains the k best points updated
		updateBest(distance, knownClasses[i], BestPointsDistances, BestPointsClasses);
	}
	
		// classify the point based on the K nearest points
   	ctype classifyID;
	#if K == 1
		classifyID = classify1NN(BestPointsClasses);
	#elif K == 3
		classifyID = classify3NN(BestPointsClasses, BestPointsDistances);
	#else
		classifyID = classifyKNN(BestPointsClasses, BestPointsDistances);
	#endif

   	showBestPoints(BestPointsClasses, BestPointsDistances);
   	
   	return classifyID;
}

/**
	Classify based on the K BestPoints returned by the kNN function
	Specialized code when using K = 1
*/
ctype classify1NN(ctype BestPointsClasses[K]) {
	ctype classifID = BestPointsClasses[0]; // there is only one point	
	return classifID;
}

/**
	Classify based on the K BestPoints returned by the kNN function
	Specialized code when using K = 3
*/
ctype classify3NN(ctype BestPointsClasses[K], dtype BestPointsDistances[K]) {
		
		ctype c1 = BestPointsClasses[0];
		dtype d1 = BestPointsDistances[0];
		
		ctype c2 = BestPointsClasses[1];
		dtype d2 = BestPointsDistances[1];
		
		ctype c3 = BestPointsClasses[2];
		dtype d3 = BestPointsDistances[2];
		
		ctype classID;
		
		/*
		if(c1 == c2) {
			classID = c1;
		} else if(c1 == c3) {
			classID = c1;
		} else if(c2 == c3) {
			classID = c2;
		} else {  // ELSE
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
		*/
		
		// ELSE
		dtype mindist = d1;
		//classID = c1;
		classID = (mindist > d2) ? c2 : c1;
		mindist = (mindist > d2) ? d2 : d1;
			
		classID = (mindist > d3) ? c3 : classID;
		mindist = (mindist > d3) ? d3 : mindist;
		
		// } else if(c2 == c3) {
		classID = (c2 == c3) ? c2 : classID;
		// } else if(c1 == c3) {
		classID = (c1 == c3) ? c1 : classID;
		// if(c1 == c2) {
		classID = (c1 == c2) ? c1 : classID; 
		//classID = classID1;
		
	return classID;
}

/**
	This function can be heavely optimized by using specialized versions according to the value of K.
	K=1, K=2, K=3, etc. Previous functions are examples of specialized code for K=1 and K=3.
*/
ctype classifyKNN(ctype BestPointsClasses[K], dtype BestPointsDistances[K]) {
	
	unsigned char histogram[NUM_CLASSES+1];
	
	for(int i=0; i<NUM_CLASSES+1; i++) // last is not a class
		histogram[i]=0;
	
	dtype min_distance = MAXDISTANCE;
	int index;
	
	for(int i=0; i<K; i++) {
		dtype distance = BestPointsDistances[i];
		if(distance < min_distance) {	
			min_distance = distance;
			index = i;
		}
		histogram[(unsigned int) BestPointsClasses[i]] += 1;
	}
	unsigned char max = 0;
	ctype classID = NUM_CLASSES ; // the default is the unknwown
	for(int i=0; i<NUM_CLASSES+1; i++) {
		if(histogram[i] > max) {
			max = histogram[i];
			classID = i;
		}
	}	
	if(max == 1) classID = BestPointsClasses[index];
	
	//printf("\n#### Final kNN classification: %s: \n", classif[index]);
	return classID;
}

