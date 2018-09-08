// Name:    Ben Belden
// ID:      bpb2v
// Course:  CSCI 5350
// Program: OL4
// Due:     22:00:00, December 1, 2015
// Purpose: Develop a software agent in C++ to perform K-means
//          clustering on labeled classification data.
// Input:   From pre-formatted files.
// Output:  To terminal.
//
// File:    kmeans.cpp
//

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int atts;
struct dataPt
{
    int label;
	vector<float> feats;
};

float dist (const dataPt lhs, const dataPt rhs)
{
    float sum=0;
    for(int i=0;i<atts;i++)
        sum+=pow((lhs.feats[i] - rhs.feats[i]),2.0);
    return sqrt(sum);
}

int main(int argc, char **argv)
{
    bool done=false;
    int i,j,k,seed,clusters,trainers=0,testers=0,hits=0,classes;
    float feat;
	vector<dataPt> points,tests,cntrPts;

	if (argc != 6)
	{
        printf("Should be: kmeans randomSeed numClusters numFeatures trainFile.txt testFile.txt\n");
		return -1;
	}
    
    ifstream trainFile, testFile;
    seed = atoi(argv[1]);
    clusters = atoi(argv[2]);
	atts = atoi(argv[3]);
	trainFile.open(argv[4]);
	testFile.open(argv[5]);

    if (!trainFile || !testFile)
	{
		printf("ERROR: One of the files cant be opened\n");
		return -1;
	}
 
    if (atts == 4) classes=3;
    else classes=6;

    while (trainFile)
	{
		dataPt daPt;
		for (i=0; i<atts; i++)
		{
			trainFile >> feat;
			daPt.feats.push_back(feat);
		}
		trainFile >> daPt.label;
		trainers++;
        points.push_back(daPt);
		trainFile.ignore(2, EOF);
		int g = trainFile.tellg();
		trainFile.seekg(g-1);
	}
	trainFile.close();

    vector< vector<float> > bigTable(trainers, vector<float>(clusters));
    vector< vector<int> > majority(clusters, vector<int>(classes,0));
    vector<int> currVotes(trainers,0),oldVotes(trainers,1),littleCount(clusters,0),shuff(trainers);
    
    srand(seed);

    for (i=0;i<trainers;i++)
        shuff[i] = i;
    
    random_shuffle(shuff.begin(),shuff.end());
    
    for (i=0;i<clusters;i++)
    {
        dataPt tmp = points[shuff[i]];
        tmp.label=-1;
        cntrPts.push_back(tmp);
    }

    while(!done)
    {
        for(i=0;i<trainers;i++)
        {
            float min=999999.9;
            int ind=0;
            for(j=0;j<clusters;j++)
                bigTable[i][j] = dist(points[i],cntrPts[j]);
            for (j=0;j<clusters;j++)
            {
                if (bigTable[i][j] < min)
                {
                    min = bigTable[i][j];
                    ind = j;
                }
            }
            currVotes[i] = ind;
        }

        for(i=0;i<clusters;i++)
        {
            for(j=0;j<atts;j++)
            {
                cntrPts[i].feats[j] = 0.0;
                littleCount[i] = 0;
            }
        }

        for (i=0;i<trainers;i++)
        {
            for (j=0;j<clusters;j++)
            {
                if (currVotes[i] == j)
                {
                    for(k=0;k<atts;k++)
                        cntrPts[j].feats[k]+=points[i].feats[k];
                    littleCount[j]++;
                }
            }
        }

        for(i=0;i<clusters;i++)
            for(j=0;j<atts;j++)
                if (littleCount[i] !=0)
                    cntrPts[i].feats[j]/=(float)littleCount[i];

        done=true;
        
        for (i=0;i<trainers;i++)
        {
            if (oldVotes != currVotes)
            {
                done=false;
                break;
            }
        }
        oldVotes = currVotes;
    }
    
    for (i=0;i<trainers;i++)
        majority[currVotes[i]][points[i].label]++;
    
    for (i=0;i<clusters;i++)
    {
        int maj=0;
        int biggest=0;
        for(j=0;j<classes;j++)
        {
            if (majority[i][j] >= biggest)
            {
                maj=j;
                biggest=majority[i][j];
            }
        }
        cntrPts[i].label=maj;
    }
    
    while (testFile)
	{
		dataPt p;
		for (i=0; i<atts; i++)
		{
			testFile >> feat;
			p.feats.push_back(feat);
		}
		testFile >> p.label;
		tests.push_back(p);
		testFile.ignore(2, EOF);
		int g = testFile.tellg();
		testFile.seekg(g-1);
	}
	testFile.close();
    
    tests.shrink_to_fit();
    vector< vector<float> > testTable(tests.size(), vector<float>(clusters));
    
    for(i=0;i<tests.size();i++)
    {
        float min=999999.9;
        int ind=0;
        for(j=0;j<clusters;j++)
            testTable[i][j] = dist(tests[i],cntrPts[j]);
            
        for (j=0;j<clusters;j++)
        {
            if (testTable[i][j] < min)
            {
                min = testTable[i][j];
                ind = j;
            }
        }
        currVotes[i] = ind;
        if (tests[i].label == cntrPts[currVotes[i]].label)
            hits++;
    }
    
    printf("%i\n",hits);

	return 0;
}
