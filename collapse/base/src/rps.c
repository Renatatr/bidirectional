#include "../rps.h"

void ic(const gsl_rng *w, int *);     /* initial conditions      */
void op(int , int *);                 /* data output             */

int main(int argc, char **argv){
	int i, j, t, ac, ps, tp, gd, nb;
	int who_died;
	int *phi, *dst;
	double at;
	PROBABILITY_OF_PREDATION1
	PROBABILITY_OF_PREDATION
	FILE *file;

	phi= (int *) calloc(Nx*Ny*Nz, sizeof(int));
	dst= (int *) calloc((NS+1), sizeof(int));

	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

	ic(w, phi);
	op(0, phi);
	
	for(i= 0; i< Nx*Ny*Nz; i++){
		dst[phi[i]]++;
	}

	file= fopen("dat/dst.dat", "a");
	for(i= 1; i< (NS+1); i++){
		fprintf(file, "%e ", (double)dst[i]/(Nx*Ny*Nz));
	}
	fprintf(file, "%e\n", (double)dst[0]/(Nx*Ny*Nz));
	fclose(file);
	t= 1;
	
	while(t== 1){
		gd= 0;
		while(gd < Nx*Ny*Nz){
			i= gsl_rng_uniform(w)*Nx;
			j= gsl_rng_uniform(w)*Ny;
			ac= j*Nx+i;
			if(phi[ac] != 0){
				nb= gsl_rng_uniform(w)*4;
				switch(nb){
					case 0:
						ps= j*Nx+((i+1)%Nx);
					break;
					case 1:
						ps= j*Nx+((i-1+Nx)%Nx);
					break;
					case 2:
						ps= ((j+1)%Ny)*Nx+i;
					break;
					default:
						ps= ((j-1+Ny)%Ny)*Nx+i;
				}
				at= gsl_rng_uniform(w);
				if(at < pm){ //mobilidade
					tp= phi[ps];
					phi[ps]= phi[ac];
					phi[ac]= tp;
					gd++;
				}else{
					if(at >= pm && at < (pm+pp)){
						if (gsl_rng_uniform(w) >= kappa){
							if(phi[ps] != 0 && gsl_rng_uniform(w) < p1[(phi[ac]-1)*NS+phi[ps]-1]){ //seleção direita
								dst[phi[ps]]--;
								dst[0]++;
								phi[ps]= 0;
								gd++;
							}	
						}else{
							if(phi[ps] != 0 && gsl_rng_uniform(w) < p[(phi[ac]-1)*NS+phi[ps]-1]){ //seleção bidirecional
								dst[phi[ps]]--;
								dst[0]++;
								phi[ps]= 0;
								gd++;
							}
						}					
					}else{
						if(phi[ps] == 0){ //reprodução
							phi[ps]= phi[ac];
							dst[phi[ps]]++;
							dst[0]--;
							gd++;
						}
					}
				}
			}
		}

/*		file= fopen("dat/dst.dat", "a");
		for(i= 1; i< (NS+1); i++){
			fprintf(file, "%e ", (double)dst[i]/(Nx*Ny*Nz));
		}
		fprintf(file, "%e\n", (double)dst[0]/(Nx*Ny*Nz));
		fclose(file);*/

		for (i = 1; i <= NS; i += 1){
			if(dst[i] == 0.0){
				who_died= i;
				t= NG;
			}
		}
//if (t%1 == 0){
//		op(n++, phi);
//}
	}

	file= fopen("dat/died.dat", "a");
	fprintf(file, "%d\n", who_died);
	fclose(file);

	gsl_rng_free(w);
	free(phi);
	free(dst);
	return 0;
}
