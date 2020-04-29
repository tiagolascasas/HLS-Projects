/**
	K-Means + k-NN
	
	Version by João MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#ifndef KMEANSMAIN_H
#define KMEANSMAIN_H

	#include <stdlib.h>
	#include <stdio.h>

	#include "dataproperties.h"
	#include "kmeans.h"
	
		/**
		Use kmeans to identify the class clusters
		*/
	void initializeKnowns(int Nknown, point *Known, int NFeatures, int NClasses);


#endif


