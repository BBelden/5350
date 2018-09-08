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
// File:    random_board.cpp
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    int board[9]={0,1,2,3,4,5,6,7,8};
    int adj[9][9]={{0,1,0,1,0,0,0,0,0},
                   {1,0,1,0,1,0,0,0,0},
                   {0,1,0,0,0,1,0,0,0},
                   {1,0,0,0,1,0,1,0,0},
                   {0,1,0,1,0,1,0,1,0},
                   {0,0,1,0,1,0,0,0,1},
                   {0,0,0,1,0,0,0,1,0},
                   {0,0,0,0,1,0,1,0,1},
                   {0,0,0,0,0,1,0,1,0}};
   int zeroPos = 0;
   int i,j,k,moves,toPos,randPos,temp,seed,shuffles,posCnt;
   seed = atoi(argv[1]);
   srand(seed);
   shuffles = atoi(argv[2]);
    for (i=0; i<shuffles;i++)
    {
        moves=0;
        for (j=0;j<9;j++)
        {
            if(adj[zeroPos][j] == 1)
                moves++;
        }
        randPos = rand()%moves + 1;
        posCnt = 0;
        for (j=0;j<9;j++)
        {
            if(adj[zeroPos][j] == 1)
                posCnt++;
            if (posCnt==randPos){
                toPos=j;
                break;}
        }
        temp=board[zeroPos];
        board[zeroPos]=board[toPos];
        board[toPos]=temp;
        zeroPos=toPos;
    }
    for (i=0; i<3;i++)
        printf("%i %i %i\n",board[i*3],board[i*3+1],board[i*3+2]);
    return 0;
}

