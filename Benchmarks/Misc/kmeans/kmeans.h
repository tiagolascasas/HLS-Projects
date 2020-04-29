#ifndef KMEANS_H
#define KMEANS_H

#include <float.h>
#include "macros.h"

#ifndef ftype
#define ftype double
#endif

#ifndef dtype
#define dtype double
#endif

#ifndef ctype
#define ctype unsigned int
#endif

#if dtype == double
#define MAXVAL DBL_MAX
#else
#define MAXVAL FLT_MAX
#endif

ctype *k_means(ftype **data, int n, int m, int k, dtype t, ftype **centroids);

#endif
