/**
	K-Means + k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#include "utils.h"

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
void showPoint(point x, int NFeatures, const char *classif[])  {
		for(int j=0; j<NFeatures; j++) {
			printf("--> feature %d: %e \n", j, x.features[j]);
		}
		printf("--> class: %s\n", classif[(int) x.classifID]);
}
	
/**
	Show the K nearest points
*/
void showBestPoints(bestpoint *BestPoints, int KValue, int NFeatures, const char *classif[]) {
	for(int i=0; i<KValue; i++) {
		printf("Best point %d: \n", i);
		showPoint(BestPoints[i].x, NFeatures, classif);
		printf("--> distance = %e: \n", BestPoints[i].distance);	
	}
}

/**
	Show all the points with classes determined
*/
void showPoints(point *KnownPoints, int Nknown, int NFeatures, const char *classif[]) {
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


