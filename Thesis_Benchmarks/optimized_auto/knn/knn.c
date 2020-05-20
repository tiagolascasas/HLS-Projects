#include "knn.h"
/**
k-NN

Version by Jo�o MP Cardoso
Email: jmpc@fe.up.pt

April 2020
FEUP, Porto, Portugal
*/
/*
Update the set of k best points so far.
Points represent instances in the kNN model.
Those instances are the ones used in a previous learning phase.
*/
void updateBest(double distance, char classifID, double BestPointsDistances[3], char BestPointsClasses[3]) {
   double max = 0;
   int index = 0;
   //find the worst point in the BestPoints
   for(int i = 0; i < 3; i++) {
      /*if(BestPointsDistances[i] > max) {
      max = BestPointsDistances[i];
      index = i;
      }*/
      double dbest = BestPointsDistances[i];
      max = (dbest > max) ? dbest : max;
      index = (dbest > max) ? i : index;
   }
   // if the point is better (shorter distance) than the worst one (longer distance) in the BestPoints
   // update BestPoints substituting the wrost one
   /*if(distance < max) {
   //printf("point is better %e\n", distance);
   BestPointsDistances[index] = distance;
   BestPointsClasses[index] = classifID;
   }*/
   double dbest = BestPointsDistances[index];
   char cbest = BestPointsClasses[index];
   BestPointsDistances[index] = (distance < max) ? distance : dbest;
   BestPointsClasses[index] = (distance < max) ? classifID : cbest;
}

/**
kNN function without classifying but returning the k nearest points
We use here a linear search.
*/
char knn(double xFeatures[12], double knownFeatures[10000][12], char knownClasses[10000]) {
   double BestPointsDistances[3]; // array with the distances of the K nearest points to the point to classify
   char BestPointsClasses[3]; // array with the classes of the K nearest points to the point to classify
   // initialize the data structures (array) with the K best points
   initializeBest(BestPointsClasses, BestPointsDistances);
   // perform the Euclidean distance between the point to classify and each one in the model
   // and update the k best points if needed
   for(int i = 0; i < 10000; i++) {
      double distance = (double) 0;
      // perform Euclidean distance
      for(int j = 0; j < 12; j++) {
         distance += (((double) xFeatures[j] - (double) knownFeatures[i][j]) * ((double) xFeatures[j] - (double) knownFeatures[i][j]));
      }
      distance = sqrt(distance);
      //printf("distance %e\n", distance);
      // maintains the k best points updated
      updateBest(distance, knownClasses[i], BestPointsDistances, BestPointsClasses);
   }
   // classify the point based on the K nearest points
   char classifyID;
   classifyID = classify3NN(BestPointsClasses, BestPointsDistances);
   showBestPoints(BestPointsClasses, BestPointsDistances);
   
   return classifyID;
}

/**
Classify based on the K BestPoints returned by the kNN function
Specialized code when using K = 1
*/
char classify1NN(char BestPointsClasses[3]) {
   char classifID = BestPointsClasses[0]; // there is only one point
   
   return classifID;
}

/**
Classify based on the K BestPoints returned by the kNN function
Specialized code when using K = 3
*/
char classify3NN(char BestPointsClasses[3], double BestPointsDistances[3]) {
   char c1 = BestPointsClasses[0];
   double d1 = BestPointsDistances[0];
   char c2 = BestPointsClasses[1];
   double d2 = BestPointsDistances[1];
   char c3 = BestPointsClasses[2];
   double d3 = BestPointsDistances[2];
   char classID;
   /*
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
   */
   double mindist = d1;
   classID = c1;
   classID = (mindist > d2) ? c2 : c1;
   mindist = (mindist > d2) ? d2 : c1;
   classID = (mindist > d3) ? c3 : c1;
   //mindist = (mindist > d3) ? d3 : c1;
   classID = (c1 == c2) ? c1 : classID;
   classID = (c1 == c3) ? c1 : classID;
   classID = (c1 == c3) ? c2 : classID;
   classID = ((c1 != c2) && (c2 != c3)) ? c2 : classID;
   
   return classID;
}

/**
This function can be heavely optimized by using specialized versions according to the value of K.
K=1, K=2, K=3, etc. Previous functions are examples of specialized code for K=1 and K=3.
*/
char classifyKNN(char BestPointsClasses[3], double BestPointsDistances[3]) {
   unsigned char histogram[9];
   for(int i = 0; i < 8 + 1; i++) histogram[i] = 0;
   double min_distance = 1.7976931348623157e+308;
   int index;
   for(int i = 0; i < 3; i++) {
      double distance = BestPointsDistances[i];
      if(distance < min_distance) {
         min_distance = distance;
         index = i;
      }
      histogram[(unsigned int) BestPointsClasses[i]] += 1;
   }
   unsigned char max = 0;
   char classID = 8; // the default is the unknwown
   for(int i = 0; i < 8 + 1; i++) {
      if(histogram[i] > max) {
         max = histogram[i];
         classID = i;
      }
   }
   if(max == 1) classID = BestPointsClasses[index];
   //printf("\n#### Final kNN classification: %s: \n", classif[index]);
   
   return classID;
}
