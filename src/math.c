/* $Id$ */
#include "kleidi.h"

double k_round(double v) {
	double d = v - floor(v);
	if(d > 0.5) return ceil(v);
	return floor(v);
}
