#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataproperties.h"
#include "knn.h"
/**
kNN

Versions
- v0.1, November 2020

by Jo�o MP Cardoso
Email: jmpc@fe.up.pt

SPeCS, FEUP.DEI, Porto, Portugal
*/

//#define WINDOWS_TIMING // for considering timing measurements in Windows

// constants are defines in dataproperties.h

// the points representing the kNN instances in the model

float instancesXfeatures[1000][32];
char classifIDs[1000]; // Classes are repreented by an integer ID.
/**
Create point to classify
*/
void newPoint(float xFeatures[32], int IDUnknown) {
   for(int j = 0; j < 32; j++) {
      xFeatures[j] = getRandFeatureValue(); // from 0 to MAX_VALUE_OF_FEATURE
   }
}

int main() {
   // get ticks per second
   // start timer
   printf("Initializing data points...\n");
   initializekNNModel(instancesXfeatures, classifIDs);
   //showPoints(KnownPoints, NKnowns, NFeatures, classif);
   printf("\nend initialization\n");
   float xFeatures[32];
   // Create a random point to classify
   //printf("Point x to classify: \n");
   newPoint(xFeatures, 8);
   //showPoint(x, NFeatures, classif);
   // Run knn
   printf("\n%d-NN considering, %d classes, %d instances learned in model, each one with %d features\n", 3, 8, 1000, 32);
   printf("Executing knn...\n");
   char classifyID = knn(xFeatures, instancesXfeatures, classifIDs); // classify
   printf("End knn\n");
   // show the best points
   //showBestPoints(BestPoints);
   printf("\n#### kNN classification of x: %d \n", classifyID);
   
   return 0;
}
