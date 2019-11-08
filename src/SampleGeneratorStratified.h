#pragma once

#include "sampleGenerator.h"

class CSampleGeneratorStratified : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		int m = std::sqrt(n);

		for(int i = 0; i < m; i ++)
			for(int j = 0; j < m; j ++){
				int pos = i * m + j;
				float e1 = DirectGraphicalModels::random::U<float>(0, 1);
				float e2 = DirectGraphicalModels::random::U<float>(0, 1);
				u[pos] 			= (i + e1) / m;
				v[pos] 			= (j + e2) / m;
				weight[pos] 	= 1.0f / n;
			}
	}
};
