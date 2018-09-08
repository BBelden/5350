// Name:    Ben Belden
// ID:      bpb2v
// Course:  CSCI 5350
// Program: OL2
// Due:     22:00:00, October 8, 2015
// Purpose: Explore different optimization techniques (greedy, simulated annealing,
//          and genetic algorithm) to find the maximum value of the
//          SumofGaussians function.
// Input:   From terminal.
// Output:  To terminal.
//
// File:    greedy.cpp
//

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "SumofGaussians.h"

int main(int argc, char* argv[])
{
    int i,seed,numDims,numGauss;
    double dx[numDims],dGx[numDims],sum[numDims];
    double sumEvals,temp;
    bool done = false;

    seed = atoi(argv[1]);
    numDims = atoi(argv[2]);
    numGauss = atoi(argv[3]);
    srandom(seed);
    SumofGaussians sog(numDims,numGauss);

    for (i=0;i<numDims;i++)
    {
        sum[i] = getRandom();
        printf("%f ",sum[i]);
    }
    sumEvals = sog.eval(sum);
    printf("%f\n",sumEvals);

    while (!done)
    {
        sog.deriv(sum, dx);
        for(i=0;i<numDims;i++)
        {
            sum[i] += 0.1*dx[i];
            printf("%f ",sum[i]);
        }

        temp = sumEvals;
        sumEvals = sog.eval(sum);
        printf("%f\n",sumEvals);

        if(sumEvals < temp)
            done = true;
    }
    
    return 0;
}
