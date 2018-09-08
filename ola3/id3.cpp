// Name:    Ben Belden
// ID:      bpb2v
// Course:  CSCI 5350
// Program: OL3
// Due:     22:00:00, November 12, 2015
// Purpose: Develop a software agent in C++ to learn an ID3 decision tree from
//          labeled classification data.
// Input:   From pre-formatted files.
// Output:  To terminal.
//
// File:    id3.cpp
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

int atts;
list<node> treeList;

struct node
{
    int label;
    int att;
    float splitPt;
    bool leaf;
    node *lChild;
    node *rChild;
    node():
    leaf(false), splitPt(0), att(0), label(), lChild(NULL), rChild(NULL){}
};

struct dataPt
{
    int label;
    int att;
	vector<float> feats;
};

bool compareDataPts(const dataPt& lhs, const dataPt& rhs)
{ return lhs.feats[lhs.att] < rhs.feats[rhs.att]; }

struct decnPt
{
    int att;
    float gain;
    float splitPt;
    list<dataPt> left;
    list<dataPt> right;
};

bool compareAtts(const decnPt& lhs, const decnPt& rhs)
{ return lhs.att < rhs.att; }

bool compareDecn(const decnPt& lhs, const decnPt& rhs)
{ return lhs.gain < rhs.gain; }

list<dataPt> split(list<dataPt> l)
{
    list<dataPt> tmp;
    for (list<dataPt>::iterator it = l.begin(); it != l.end(); it++)
    {
        for (int i=0; i<atts; i++)
        {
            dataPt pt = *it;
            pt.att = i;
            tmp.push_back(pt);
        }
    }
    return tmp;
}

float getSplit(list<dataPt> &pts)
{
	map<int, float> m;
	for (list<dataPt>::iterator it = pts.begin(); it != pts.end(); it++)
	{
		if (m.find(it->label) == m.end())
			m[it->label] = 1;
		else
			m[it->label]+=1;
	}
	float splitPt=0;
	for (map<int, float>::iterator it = m.begin(); it != m.end(); it++)
	{
        float tmp = it->second;
		tmp /= pts.size();
		splitPt += tmp * log2(tmp);
	}
    splitPt *= -1;
	return splitPt;
}

node * decnTree(list<dataPt> l)
{
	if (getSplit(l) == 0)
	{
		node leafNode;
		leafNode.leaf = true;
		leafNode.label = l.front().label;
		treeList.push_back(leafNode);
		return &treeList.back();
	}
	else
	{
		list<decnPt> daPts;
		for (int i = 0; i < atts; i++)
		{
			list<dataPt> subset;
			for (list<dataPt>::iterator it = l.begin(); it != l.end(); it++)
				if (it->att == i)
					subset.push_back(*it);

            subset.sort(compareDataPts);

            float uncertn = getSplit(subset);
			for (list<dataPt>::iterator it = subset.begin(); next(it, 1) != subset.end(); it++)
			{
				if (it->label != next(it, 1)->label && it->feats[i] != next(it, 1)->feats[i])
				{
					decnPt dePt;
					dePt.att = it->att;
					dePt.splitPt  = (it->feats[i] + next(it, 1)->feats[i]) / 2;
					dePt.left.insert(dePt.left.begin(), subset.begin(), next(it, 1));
					float lowPrior = getSplit(dePt.left);
					list<dataPt> right;
					dePt.right.insert(dePt.right.begin(), next(it, 1), subset.end());
					float upPrior = getSplit(dePt.right);
					dePt.gain = uncertn - (lowPrior * (float)(dePt.left.size() / (float)subset.size()) + upPrior * (float)(dePt.right.size() / (float)subset.size()));
					daPts.push_back(dePt);
				}
			}
		}

        daPts.sort(compareDecn);
		decnPt best = daPts.back();
		list<decnPt> bests;
		
        for (list<decnPt>::iterator it = daPts.begin(); it != daPts.end(); it++)
			if (it->gain == best.gain)
				bests.push_back(*it);
		
        if (bests.size() != 1)
		{
			bests.sort(compareAtts);
			best = bests.front();
		}
		
        l.clear();
		daPts.clear();
		bests.clear();
		
        node branch;
		branch.leaf = false;
		branch.splitPt = best.splitPt;
		branch.att = best.att;
		
        list<dataPt> lSplit = split(best.left);
		list<dataPt> rSplit = split(best.right);
		best.left.clear();
		best.right.clear();

        branch.lChild = decnTree(lSplit);
        branch.rChild = decnTree(rSplit);
        treeList.push_back(branch);
		return &treeList.back();
    }
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		cout << "Should be: id3 numFeatures trainFile.txt testFile.txt" << endl;
		return -1;
	}
    ifstream trainFile, testFile;
	atts = atoi(argv[1]);
	trainFile.open(argv[2]);
	testFile.open(argv[3]);

    if (!trainFile || !testFile)
	{
		cout << "ERROR: One of the files cant be opened" << endl;
		return 1;
	}
    int i,decisions=0,trainers=0;
	list<dataPt> points;
	string line;

    while (trainFile)
	{
		float feat;
		dataPt daPt;
		for (i=0; i<atts; i++)
		{
			trainFile >> feat;
			daPt.feats.push_back(feat);
		}
		trainFile >> daPt.label;
		trainers++;
		for (i=0; i<atts; i++)
		{
			dataPt tempPnt = daPt;
			tempPnt.att = i;
			points.push_back(tempPnt);
		}
		trainFile.ignore(2, EOF);
		int g = trainFile.tellg();
		trainFile.seekg(g-1);
	}
	trainFile.close();

    node root = *decnTree(points);
    
    list<dataPt> tests;

    while (testFile)
	{
		dataPt p;
		for (i=0; i<atts; i++)
		{
			float feat;
			testFile >> feat;
			p.feats.push_back(feat);
		}
		testFile >> p.label;
		tests.push_back(p);
		testFile.ignore(2, EOF);
		int g = testFile.tellg();
		testFile.seekg(g-1);
	}
	int guessedRight = 0;

    for (list<dataPt>::iterator it = tests.begin(); it != tests.end(); it++)
	{
		node tree = root;
		while (true)
		{
			if (tree.leaf == true)
			{
				if (it->label == tree.label)
					guessedRight++;
				break;
			}
			else
			{
				if(it->feats[tree.att] < tree.splitPt)
					tree = *tree.lChild;
				else
					tree = *tree.rChild;
			}
		}
	}
	cout << guessedRight << endl;
	testFile.close();
	return 0;
}
