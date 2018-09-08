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
// File:    ga.cpp
//

//#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
//#include <iterator>
//#include <algorithm>
//#include <cmath>
#include "SumofGaussians.h"

struct coords{std::vector<double> point; double eval;};
std::vector<coords *> coordList;
std::vector<coords *>::iterator it;

bool SortCoords (coords *l, coords *r){ return l->eval > r->eval;}

void CopyCoords(coords *newP, coords *oldP, int numDims)
{
    for(int i=0;i<numDims;i++)
        newP->point.push_back(oldP->point[i]);
    newP->eval = oldP->eval;
}

void ToArray(double point[], std::vector<double>& pointV)
{
    for(int i=0;i<pointV.size();i++)
        point[i] = pointV[i];
}


int main(int argc, char *argv[])
{
    int i,j,k,pop=10,max=100000;
    int seed,numDims,numGauss,numToRep,crossValue,numToCross,mutator;
    double point[numDims];
    coords *newCoords, *child1, *child2;
    
    seed = atoi(argv[1]);
    numDims = atoi(argv[2]);
    numGauss = atoi(argv[3]);
    srandom(seed);
    SumofGaussians sog(numDims,numGauss);
    
    for(i=0;i<pop;i++)
    {
        newCoords = new coords;
        for(j=0;j<numDims;j++)
            newCoords->point.push_back(getRandom());
        ToArray(point, newCoords->point);
        newCoords->eval = sog.eval(point);
        coordList.push_back(newCoords);
    }

    for(i=0;i<max;i++)
    {
        // select fittest
        sort(coordList.begin(), coordList.end(), SortCoords);
        while(coordList.size() > pop)
        {
            delete coordList.back();
            coordList.pop_back();
        }
        for(j=0;j<numDims;j++)
            printf("%f ",coordList.front()->point[j]);
        printf("%f\n",coordList.front()->eval);

        // replicate
        numToRep = (0.75)*coordList.size();
        it = coordList.begin();
        coords *newCoords;
        for(j=0;j<numToRep;j++)
        {
            newCoords = new coords;
            CopyCoords(newCoords, (*it), numDims);
            coordList.push_back(newCoords);
            it++;
        }

        // splice
        std::vector<coords*>::iterator fIter = coordList.begin();
        std::vector<coords*>::iterator mIter = fIter;
        mIter++;
        crossValue = numDims/2;
        numToCross = coordList.size()*0.25;
        
        if(numToCross%2 != 0)
            numToCross++;
        
        for(j=1;j<numToCross;j+=2)
        {
            child1 = new coords;
            child2 = new coords;
            CopyCoords(child1, (*fIter), numDims);
            CopyCoords(child2, (*mIter), numDims);
            
            for(k=0;k<crossValue;k++)
            {
                child1->point[numDims-(k+1)] = (*mIter)->point[k];
                child2->point[numDims-(k+1)] = (*fIter)->point[k];
            }
            
            ToArray(point, child1->point);
            child1->eval = sog.eval(point);
            coordList.push_back(child1);
            ToArray(point, child2->point);
            child2->eval = sog.eval(point);
            coordList.push_back(child2);
            advance(fIter,2);
            advance(mIter,2);
        }
        
        // mutate
        mutator = coordList.size()*0.25;
        for(j=0;j<mutator;j++)
        {
            it = coordList.begin();
            advance(it, random()%coordList.size());
            (*it)->point[random()%numDims] = getRandom();
            ToArray(point, (*it)->point);
            (*it)->eval = sog.eval(point);
        }
    }

    return 0;
}

