/**
	K-Means + k-NN
	
	Version by Jo�o MP Cardoso
	Email: jmpc@fe.up.pt
	
	December 2016
	FEUP, Porto, Portugal
*/

#include "kmeansmain.h"

/**
	Use kmeans to determine classes (clusters)
	
	Nknown: number of points
	NFeatures: number of features in each point
	NClasses: desired number of classes -> clusters
	*Known: the data structure with the points
*/
void initializeKnowns(int Nknown, point *Known, int NFeatures, int NClasses)
{

    // initialize the array of the data points to be preclassified: database of classified points
    // this can be moved to a function
    for (int i = 0; i < Nknown; i++)
    {
        point *x = &Known[i];
        for (int j = 0; j < NFeatures; j++)
        {
            x->features[j] = (ftype)(rand() % MAX_VALUE_OF_FEATURE); // from 0 to MAX_VALUE_OF_FEATURE
                                                                     //printf("feature %e\n", x.features[j]);
        }
    }

    // classify known points using kmeans
    int n = Nknown;
    int m = NFeatures;

    // code to interface to the external k_means function data structures
    ftype **data;
    data = malloc(sizeof(ftype *) * n);
    for (int index = 0; index < n; index++)
    {
        *(data + index) = malloc(sizeof(ftype) * m);
    }
    for (int i = 0; i < n; i++)
    {
        point *x = &Known[i];
        for (int j = 0; j < m; j++)
        {
            data[i][j] = x->features[j];
        }
    }

    double t = KMEANS_ERROR_TOLERANCE; //0.0001;  //error tolerance

    //	dtype **centroids;
    //	int **labels = k_means(data, n, m, NClasses, t, centroids);
    ctype *labels = k_means(data, n, m, NClasses, t, NULL);

    for (int i = 0; i < n; i++)
    {
        point *x = &Known[i];
        x->classifID = labels[i];
    }
    free(labels);
    for (int i = 0; i < n; i++)
    {
        free(data[i]);
    }
    free(data);
}
