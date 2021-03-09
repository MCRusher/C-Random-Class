#include <custom/oop.h>
#include <custom/export.h>

#include "random.h"

EXPORTED void Rng_init(Rng * rng, double (*gen)(Rng *));
EXPORTED double Rng_gen(Rng * rng);
EXPORTED bool Rng_genBool(Rng * rng);
EXPORTED double Rng_genRange(Rng * rng, double min, double max);
EXPORTED void RngDefault_init(RngDefault * rng, uint64_t seed);

static double RngDefault_gen(Rng * rng);

void Rng_init(Rng * rng, double (*gen)(Rng *)) {
	rng->gen = gen;
}

double Rng_gen(Rng * rng) {
	return rng->gen(rng);
}

bool Rng_genBool(Rng * rng) {
	//true: 0.0 to 0.09, 0.1 to 0.19, 0.2 to 0.29, 0.3 to 0.39, 0.4 to 0.49 (10x1, 9x4, 46 chances)
	//false: 0.5 to 0.59, 0.6 to 0.69, 0.7 to 0.79, 0.8 to 0.89, 0.9 to 1.0 (9x4, 10x1, 46 chances)
	return rng->gen(rng) < 0.5;
}

double Rng_genRange(Rng * rng, double min, double max) {
	//makes sure max holds the largest value
	// without this, the sign of the result can be effected.
	//EX: .1 * (100 - -100) + -100 = -80, .1 * (-100 - 100) + 100 = 80
	if(max < min){
		double const tmp = max;
		max = min;
		min = tmp;
	}else if(max == min){
		//nothing to generate, the range of values is 1
		return max;
	}
	//expand range of [0.0, 1.,0] to [min, max]
	return rng->gen(rng) * (max - min) + min;
}

//----------------------Default Implementation----------------------//

void RngDefault_init(RngDefault * rng, uint64_t seed) {
	//don't ever want the seed to be zero (dead end)
	rng->state = seed != 0 ? seed : 1;
	Rng_init(&rng->rng, RngDefault_gen);
}

static double RngDefault_gen(Rng * rng) {
	RngDefault * super = getSuper(RngDefault, rng, rng);
	uint64_t x = super->state;
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	super->state = x;
	x *= UINT64_C(0x2545F4914F6CDD1D);
	//discard less-random lower bits
	x >>= 32;
	//return double number from [0.0, 1.0]
	// (float can't hold u32 max)
	return x / (double)UINT32_MAX;
}