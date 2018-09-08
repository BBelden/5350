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
// File:    id3.cpp
//

#include <iostream>
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
    {
        sum+=pow((lhs.feats[i] - rhs.feats[i]),2.0);
    }
    return sqrt(sum);
}


int main(int argc, char **argv)
{
    bool hit=false,done=false;
    int i,j,k,seed,clusters,trainers=0,testers=0,hits=0,classes;
    float feat,avg;
	vector<dataPt> points,tests,cntrPts;
    vector< vector<float> > bigTable(trainers, vector<float>(clusters)), testTable(10, vector<float>(clusters));
    vector< vector<int> > majority(clusters, vector<int>(classes));
    vector<int> littleTable(trainers,0),littleCopy(trainers,0),littleCount(clusters,0);

	if (argc != 6)
	{
		cout << "Should be: kmeans randomSeed numClusters numFeatures trainFile.txt testFile.txt" << endl;
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
		cout << "ERROR: One of the files cant be opened" << endl;
		return 1;
	}
 
    if (atts == 4)
        classes = 3;
    else
        classes = 6;

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

    srand(seed);

    for(i=0;i<clusters;i++)
    {
        dataPt tmp = points[rand()%trainers];
        tmp.label=-1;
        cntrPts.push_back(tmp);
    }

    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3]);

    
    for(i=0;i<trainers;i++)
    {
        float min=999999.9;
        int ind=0;
        //cout << littleTable[i] << endl;
        for(j=0;j<clusters;j++)
        {
            bigTable[i][j] = dist(points[i],cntrPts[j]);
            //printf("%.5f\t",bigTable[i][j]);
            
        }
        for (j=0;j<clusters;j++)
        {
            if (bigTable[i][j] < min)
            {
                min = bigTable[i][j];
                ind = j;
            }
        }
        littleTable[i] = ind;
        //cout << littleTable[i] << endl;
    }
    //cout << endl;
    littleCopy = littleTable;

    //for(i=0;i<trainers;i++)
    //    printf("%i\n",littleTable[i]);
    
    for(i=0;i<clusters;i++)
        for(j=0;j<atts;j++)
            cntrPts[i].feats[j]=0;
    
    for (i=0;i<trainers;i++)
    {
        for (j=0;j<clusters;j++)
        {
            if (littleTable[i] == j)
            {
                for(k=0;k<atts;k++)
                {
                    cntrPts[j].feats[k]+=points[i].feats[k];
                }
                littleCount[j]++;
           }
        }
    }
    //cout << endl;
    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3]);
    //for(i=0;i<clusters;i++)
    //    printf("%i\n",littleCount[i]);
    for(i=0;i<clusters;i++)
    {
        for(j=0;j<atts;j++)
        {
            if (littleCount[i] !=0)
                cntrPts[i].feats[j]/=littleCount[i];
            else
                cntrPts[i] = points[rand()%trainers];
        }
    }
    //cout << endl;
    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3]);
    
    
    while(!done)
    {
    
    
    
    for(i=0;i<trainers;i++)
    {
        float min=999999.9;
        int ind=0;
        //cout << littleTable[i] << endl;
        for(j=0;j<clusters;j++)
        {
            bigTable[i][j] = dist(points[i],cntrPts[j]);
            //printf("%.5f\t",bigTable[i][j]);
            
        }
        for (j=0;j<clusters;j++)
        {
            if (bigTable[i][j] < min)
            {
                min = bigTable[i][j];
                ind = j;
            }
        }
        littleTable[i] = ind;
        //cout << littleTable[i] << endl;
    }
    //cout << endl;

    //for(i=0;i<trainers;i++)
    //    printf("%i\n",littleTable[i]);
    
    for(i=0;i<clusters;i++)
        for(j=0;j<atts;j++)
            cntrPts[i].feats[j] = littleCount[i] = 0;
    
    
    
    for (i=0;i<trainers;i++)
    {
        for (j=0;j<clusters;j++)
        {
            if (littleTable[i] == j)
            {
                for(k=0;k<atts;k++)
                {
                    cntrPts[j].feats[k]+=points[i].feats[k];
                }
                littleCount[j]++;
            }
        }
    }
    //cout << endl;
    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3]);
    //for(i=0;i<clusters;i++)
    //    printf("%i\n",littleCount[i]);
    for(i=0;i<clusters;i++)
    {
        for(j=0;j<atts;j++)
        {
            if (littleCount[i] !=0)
                cntrPts[i].feats[j]/=littleCount[i];
            else
                cntrPts[i] = points[rand()%trainers];
        }
    }
    //cout << endl;
    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3]);
        done=true;
        
        for (i=0;i<trainers;i++)
        {
            if (littleCopy != littleTable)
            {
                done=false;
                break;
            }
        }
        littleCopy = littleTable;

    }
    
    
    
    for (i=0;i<trainers;i++)
        majority[littleTable[i]][points[i].label]++;
    
    //for (i=0;i<clusters;i++)
    //{
    //    for(j=0;j<classes;j++)
    //        printf("%i\t",majority[i][j]);
    //    cout << endl;
    //}
    
    for (i=0;i<clusters;i++)
    {
        int maj=0;
        int biggest=0;
        for(j=0;j<classes;j++)
        {
            if (majority[i][j] > biggest)
            {
                maj=j;
                biggest=majority[i][j];
            }
            else if (majority[i][j] == biggest)
            {
                maj=j;
                biggest=majority[i][j];
            }
        }
        cntrPts[i].label=maj;
    }
    
    //for(i=0;i<clusters;i++)
    //    printf("%10.5f\t%10.5f\t%10.5f\t%10.5f\t%i\n",cntrPts[i].feats[0],cntrPts[i].feats[1],cntrPts[i].feats[2],cntrPts[i].feats[3],cntrPts[i].label);
    
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
    
    for(i=0;i<10;i++)
    {
        float min=999999.9;
        int ind=0;
        //cout << littleTable[i] << endl;
        for(j=0;j<clusters;j++)
        {
            testTable[i][j] = dist(tests[i],cntrPts[j]);
            //printf("%.5f\t",testTable[i][j]);
            
        }
        for (j=0;j<clusters;j++)
        {
            if (testTable[i][j] < min)
            {
                min = testTable[i][j];
                ind = j;
            }
        }
        littleTable[i] = ind;
        if (tests[i].label == cntrPts[littleTable[i]].label)
        {
            hit=true;
            hits++;
        }
        //if (hit)
        //    cout << littleTable[i] << "\thit" << endl;
        //else
        //    cout << littleTable[i] << "\tmiss" << endl;
        hit=false;
    }
    
    cout << hits << endl;


	return 0;
}



