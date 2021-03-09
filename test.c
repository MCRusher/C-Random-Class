#include "random.h"

#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {
	RngDefault rng_state;
	RngDefault_init(&rng_state, time(NULL) * 0x00F);
	Rng * rng = &rng_state.rng;
	
	//have tested, it can reach 0.0 and 1.0
	double f = Rng_gen(rng);
	printf("%f\n", f);
	
	bool b = Rng_genBool(rng);
	printf("%s\n", b ? "true" : "false");
	
	float fr = Rng_genRange(rng, 1, 100);
	printf("%f\n", fr);
	
	//rounding nearest should not effect distribution
	int ir = round(Rng_genRange(rng, -2, 2));
	printf("%d\n", ir);
	
	//testing how even the distribution is over very large numbers of trials
	unsigned long long ts = 0;
	unsigned long long fs = 0;
	unsigned long long i;
	for(i = 0; i < 20000000; i++){
		if(Rng_genBool(rng)){
			++ts;
		}else{
			++fs;
		}
	}
	printf("\ntrials: %llu\ntrues: %llu\nfalses: %llu\n\n", i, ts, fs);
	
	//double fe;
	//do {
	//	fe = Rng_gen(rng);
	//}while(fe != 0.0);
	//printf("%lf ", fe);
	//printf("\b\n");
	
	double fe2;
	do {
		fe2 = Rng_genRange(rng, 1.0, 10.0);
	}while(fe2 >= 1.0 && fe2 <= 10.0);
	printf("%lf ", fe2);
	printf("\b\n");
}
