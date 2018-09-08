// Name:    Ben Belden
// ID:      bpb2v
// Course:  CSCI 5350
// Program: OL1
// Due:     22:00:00, September 24, 2015
// Purpose: Explore different search algorithms by solving an 8-puzzle 
// Input:   Solved 8-puzzle board to random_board.cpp, randomized board 
//          to a-star.cpp. From terminal.
// Output:  Starting board and each move to solved board. Search stats.
//          To terminal.
//
// File:    a-star.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <cmath>

using namespace std;

const int GOAL[9] = {0,1,2,3,4,5,6,7,8};

const int ADJ[9][9] = {{0,1,0,1,0,0,0,0,0},
                       {1,0,1,0,1,0,0,0,0},
                       {0,1,0,0,0,1,0,0,0},
                       {1,0,0,0,1,0,1,0,0},
                       {0,1,0,1,0,1,0,1,0},
                       {0,0,1,0,1,0,0,0,1},
                       {0,0,0,1,0,0,0,1,0},
                       {0,0,0,0,1,0,1,0,1},
                       {0,0,0,0,0,1,0,1,0}};

const int REACH[9][9] = {{0,1,2,1,2,3,2,3,4},
                         {1,0,1,2,1,2,3,2,3},
                         {2,1,0,3,2,1,4,3,2},
                         {1,2,3,0,1,2,1,2,3},
                         {2,1,2,1,0,1,2,1,2},
                         {3,2,1,2,1,0,3,2,1},
                         {2,3,4,1,2,3,0,1,2},
                         {3,2,3,2,1,2,1,0,1},
                         {4,3,2,3,2,1,2,1,0}};

struct BOARD
{	
	int board[9];		
	int f;			
	int g;			
	int depth;			
	int id;				
	BOARD *parent;		
};

struct sortBoard
{
    bool operator () (const BOARD &l, const BOARD &r)
    {
        if(l.f > r.f)
            return true;
        else if(l.f == r.f)
            return l.id < r.id;
        return false;
    }
};

BOARD startNode;
list<BOARD> closedList;
priority_queue<BOARD, vector<BOARD>, sortBoard> frontier;
list<BOARD>::iterator it;

bool Goal(BOARD);
int Displaced(BOARD);		
int Heuristic(BOARD, int);	
bool InClosed(BOARD);
bool InParent(BOARD);
int Manhattan(BOARD);		
void Print(BOARD);
int RowCol(BOARD);  		
BOARD Explore(int,int);	

int main(int argc, char *argv[]) 
{
    if(argc != 3)
    {
        printf("Incorrect format.\n");
        return 1;
    }
    int h = atoi(argv[1]); 
    int g = atoi(argv[2]);
    for(int i=0; i<9; i++)
        scanf("%i",&startNode.board[i]);
    Print(Explore(h,g));
    return 0;
}

BOARD Explore(int h, int g)
{
    int i,j,swap,zero,id=1;
    BOARD currNode,childNode;	
    startNode.parent = NULL;
    startNode.id=0;
    startNode.depth=0;
    startNode.f = Heuristic(startNode,h);
    frontier.push(startNode);

    while(!frontier.empty())
    {
        currNode = frontier.top(); 
        frontier.pop();				
        closedList.push_back(currNode); 
        if(Goal(currNode)) 
            return currNode;
	
        for(i=0; i<9; i++)
        {
            if(currNode.board[i] == 0)
            {
                zero = i;
                break;
            }
        }
		
        for(i=0;i<9;i++)
        {
            if(ADJ[zero][i] == 0)
                continue;
            for(j=0; j<9; j++)
                childNode.board[j] = currNode.board[j];
            swap = i;
            childNode.board[zero] = childNode.board[swap];
            childNode.board[swap] = 0;
            childNode.parent = &closedList.back(); 
            id++;
            childNode.id = id;				
            childNode.depth = currNode.depth+1;	
            childNode.g = (currNode.g+g);		
            if(InParent(childNode))
                id--;	
            else if(InClosed(childNode))
                id--;
            else
            {
                childNode.f = childNode.g+Heuristic(childNode, h);
                frontier.push(childNode);	
            }
        }		
    }
    return currNode;
}

int Heuristic(BOARD node, int h)
{
    if(h==1) 
        return Displaced(node);
    else if(h==2) 
        return Manhattan(node);     
    else if(h==3) 
        return RowCol(node);   
    else 
        return 0;		 // h=0: uniform cost search
}

int Displaced(BOARD node)
{
    int h=0;		
    for(int i=0; i<9; i++)
        if(GOAL[i] != node.board[i])
            h++;	
    return h;
}

int Manhattan(BOARD node)
{
    int h=0;
    for(int i=0; i<9; i++)
        h+=REACH[node.board[i]][i];
    return h;
}

int RowCol(BOARD node)
{
    int h=0;
    for(int i=0; i<9; i++)
    {
        // out of row
        if (!((i>=0 && i<=2) && (node.board[i] >=0 && node.board[i] <=2)) ||
            !((i>=3 && i<=5) && (node.board[i] >=3 && node.board[i] <=5)) ||
            !((i>=6 && i<=8) && (node.board[i] >=6 && node.board[i] <=8)))
            h++;
        // out of col
        if (!(node.board[i] == i || node.board[i] == i+3 || 
                node.board[i] == i-3 || node.board[i] == i+6 || 
                node.board[i] == i-6))
            h++;
    }
    return h;
}

bool Goal(BOARD node)
{
    for(int i=0; i<9; i++)
        if(node.board[i] != GOAL[i]) 
            return false;
    return true;
}

bool InParent(BOARD node)
{
    BOARD * parentPtr;
    int same=0;
    parentPtr = node.parent;
    while(parentPtr != NULL)
    {
        for(int i=0; i<9; i++)
        {
            if(node.board[i] == parentPtr->board[i])
            {
                same++;
            }
        }
        if(same == 9)
            return true;
        same=0;
        parentPtr = parentPtr->parent;			
    }
    return false;
}

bool InClosed(BOARD node)
{
    int same=0;
    for(it = closedList.begin(); it != closedList.end(); it++)
    {
        for(int i=0; i<9; i++)
        {
            if(node.board[i] == (*it).board[i])
                same++;
        }
        if(same == 9)
            return true;
        same=0;
    }
    return false;
}

void Print(BOARD node)
{
    list<BOARD> print;
    BOARD * getParent;
    int c = closedList.size();
    int f = frontier.size();
    float b = log(c+f)/node.depth;  // find b using e^(log(N))/d
    printf("V=%i\nN=%i\nd=%d\nb=%f\n\n",c,c+f,node.depth,exp(b));
    getParent = &node;
    while(getParent != NULL)
    {
        print.push_front(*getParent);
        getParent = getParent->parent;
    }

    for(it = print.begin(); it != print.end(); it++)
    {
        for(int i=0; i<9; i++)
        {
            printf("%i ",(*it).board[i]);
            if((i+1)%3 == 0)
                printf("\n");
        }
        printf("\n");
    }
}

