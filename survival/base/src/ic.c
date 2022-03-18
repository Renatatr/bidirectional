#include "../rps.h"

void ic(const gsl_rng *w, int *phi){
	int i;

//	FILE *file= fopen("phi-1.dat", "r");
//	for(i= 0; i< Nx*Ny*Nz; i++){
//		fscanf(file, "%d", &phi[i]);
//	}
//	fclose(file);

	for(i= 0; i< Nx*Ny*Nz; i++){
		phi[i]= gsl_rng_uniform(w)*(NS+1);
	}
}
