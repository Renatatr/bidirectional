#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#define Nx  	250     /* grid size                      			*/
#define Ny  	250     /* grid size                      			*/
#define Nz  	1       /* grid size                      			*/
#define NG  	100000  /* number of generations          			*/
#define NS  	3       /* number of types of species     			*/
/* pm + pr + pp = 1.0                                				*/
#define pm 	0.50    /* probability of motion          			*/
#define pr  	0.25    /* probability of reproduction    			*/
#define pp  	0.25    /* probability of predation 				   */
#define kappa	1.00    /* probability of bidirectional predation  */


#define PROBABILITY_OF_PREDATION1 \
const double p1[NS*NS]= {\
	0.00, 1.00, 0.00, \
	0.00, 0.00, 1.00, \
	1.00, 0.00, 0.00, \
};

#define PROBABILITY_OF_PREDATION \
const double p[NS*NS]= {\
	0.00, 1.00, 1.00, \
	1.00, 0.00, 1.00, \
	1.00, 1.00, 0.00, \
};
