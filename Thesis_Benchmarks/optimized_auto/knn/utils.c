#include "utils.h"
/**
k-NN

Version by Jo�o MP Cardoso
Email: jmpc@fe.up.pt

December 2016
FEUP, Porto, Portugal
*/
/**
Return a random integer number from min to max).
*/
int randInt(int min, int max) {
   int number = (int) (min + rand() / (0x7FFF / (max - min + 1) + 1));
   
   return number;
}

/**
Return a random double number from min to max).
*/
double randDouble(double min, double max) {
   double number = (double) (min + rand() / (0x7FFF / (max - min + 1) + 1));
   
   return number;
}

/**
Return a random float number from min to max).
*/
float randFloat(float min, float max) {
   int number = (float) (min + rand() / (0x7FFF / (max - min + 1) + 1));
   
   return number;
}

/**
Return a random value for a feature.
*/
float getRandFeatureValue() { // from 0 to MAX_VALUE_OF_FEATURE // from 0 to MAX_VALUE_OF_FEATURE // from 0 to MAX_VALUE_OF_FEATURE
   float value;
   value = (float) randDouble(0, 1); // from 0 to MAX_VALUE_OF_FEATURE
   
   return value;
}

/**
Initializes the kNN model with random values.

Nknown: number of points
NFeatures: number of features in each point
NClasses: desired number of classes
*Known: the data structure with the points
*/
void initializekNNModel(float instancesXfeatures[1000][32], char classifIDs[1000]) {
   // initialize the array of the data points to be preclassified: database of classified points
   // this can be moved to a function
   for(int i = 0; i < 1000; i++) {
      for(int j = 0; j < 32; j++) {
         instancesXfeatures[i][j] = getRandFeatureValue(); // from 0 to MAX_VALUE_OF_FEATURE
         //printf("feature %e\n", x->features[j]);
      }
      // assign a random class ID to each vector i
      classifIDs[i] = (char) randInt(0, 8);
   }
}

/**
Show a point: includes the print of the values of its features and its class
*/
void showPoint(float xFeatures[32], char classifID) {
   for(int j = 0; j < 32; j++) {
      printf("--> feature %d: %e \n", j, xFeatures[j]);
   }
   printf("--> class: %d\n", classifID);
}

/**
Show the K nearest points
*/
void showBestPoints(char BestPointsClasses[3], float BestPointsDistances[3]) {
   for(int i = 0; i < 3; i++) {
      printf("Best point %d: \n", i);
      printf("--> class: %d\n", BestPointsClasses[i]);
      printf("--> distance = %e: \n", BestPointsDistances[i]);
   }
}

/**
Show all the points with classes determined
*/
void showPoints(float instancesXfeatures[1000][32], char classifIDs[1000]) {
   for(int i = 0; i < 1000; i++) {
      printf("Point %d: \n", i);
      showPoint(instancesXfeatures[i], classifIDs[i]);
   }
}

/**
Initializes the K BestPoints
*/
void initializeBest(char BestPointsClasses[3], float BestPointsDistances[3]) {
   #pragma HLS inline
   for(int i = 0; i < 3; i++) {
      BestPointsDistances[i] = 1.7976931348623157e+308;
      /*point *x = &(bp->x);
      for(int j=0; j<NFeatures; j++) {
      x->features[j] = 0;
      }*/
      BestPointsClasses[i] = 8; // unknown
   }
}
