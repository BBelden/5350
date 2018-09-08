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

int main(int argc, char* argv[]) {
    
    int i,j,seed,numDims,numGauss,max=10000;
    double coord[numDims],nextCoord[numDims];
    double coordEval,nextEval,temp=1000.0;
    
    seed = atoi(argv[1]);
    numDims = atoi(argv[2]);
    numGauss = atoi(argv[3]);
    srandom(seed);
    SumofGaussians sog(numDims,numGauss);

    for(i=0;i<numDims;i++)
    {
        coord[i] = getRandom();
        printf("%f ",coord[i]);
    }

    coordEval = sog.eval(coord);
    printf("%f\n",coordEval);

    for(j=0;j<max;j++)
    {
        if(max % 100 == 0)
            temp -= 1;

        for(i=0;i<numDims;i++)
            nextCoord[i] = getRandom();

        nextEval = sog.eval(nextCoord);

        if(nextEval >= coordEval)
        {
            for(i=0;i<numDims;i++)
                coord[i] = nextCoord[i];
            coordEval = sog.eval(coord);
        }
        else
        {
            if(getRandom()/10 > exp(std::abs(nextEval-coordEval)/temp))
            {
                for(i=0;i<numDims;i++)
                    coord[i] = nextCoord[i];
                coordEval = sog.eval(coord);
            }
        }

        for(i=0;i<numDims;i++)
            printf("%f ",coord[i]);
        printf("%f\n",coordEval);
    }
    return 0;
}
