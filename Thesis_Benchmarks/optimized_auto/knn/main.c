#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataproperties.h"
#include "knn.h"
#include <windows.h>
/**
kNN

Versions
- v0.1, November 2020

by Jo�o MP Cardoso
Email: jmpc@fe.up.pt

SPeCS, FEUP.DEI, Porto, Portugal
*/

// constants are defines in dataproperties.h

// the points representing the kNN instances in the model

double instancesXfeatures[10000][12];
char classifIDs[10000]; // Classes are repreented by an integer ID.
/**
Create point to classify
*/
void newPoint(double xFeatures[12], int IDUnknown) {
   for(int j = 0; j < 12; j++) {
      xFeatures[j] = getRandFeatureValue(); // from 0 to MAX_VALUE_OF_FEATURE
   }
}

int main() {
   long long freq, start, end;
   long elapsedTime;
   // get ticks per second
   QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
   // start timer
   QueryPerformanceCounter((LARGE_INTEGER *) &start);
   printf("Initializing data points...\n");
   initializekNNModel(instancesXfeatures, classifIDs);
   //showPoints(KnownPoints, NKnowns, NFeatures, classif);
   printf("\nend initialization\n");
   double xFeatures[12];
   // Create a random point to classify
   //printf("Point x to classify: \n");
   newPoint(xFeatures, 8);
   //showPoint(x, NFeatures, classif);
   // Run knn
   printf("\n%d-NN considering, %d classes, %d instances learned in model, each one with %d features\n", 3, 8, 10000, 12);
   printf("Executing knn...\n");
   char classifyID = knn(xFeatures, instancesXfeatures, classifIDs); // classify
   printf("End knn\n");
   // show the best points		
   //showBestPoints(BestPoints);
   printf("\n#### kNN classification of x: %d \n", classifyID);
   QueryPerformanceCounter((LARGE_INTEGER *) &end);
   elapsedTime = ((end - start) * 1000) / freq;
   printf("It took %ld ms\n", elapsedTime);
   
   return 0;
}
