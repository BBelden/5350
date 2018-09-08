// a-star

#include <stdio.h>
#include <stdlib.h>
#include <queue>

struct boardState{
    int board[9];
    int id;
    int fCost;
    int gCost;
    int heuristic;
    int depth;
    boardState * parent;
};

int main(int argc, char *argv[])
{
    int i,j,k,heuristic,cost;
    int id = 0;
    int board[9]={3,2,1,7,0,6,4,5,8};
    heuristic = atoi(argv[1]);
    cost = atoi(argv[2]);
    for (i=0;i<9;i++)
        scanf("%i",&board[i]);
    printf("heuristic: %i\tcost: %i\n",heuristic,cost);
 
    std::priority_queue<boardState> q;

    
    
    
    
    for (i=0;i<3;i++)
        printf("%i %i %i\n",board[i*3],board[i*3+1],board[i*3+2]);
    return 0;
}

// 0 1 2
// 3 4 5
// 6 7 8
// 
// checkBoard
// 0,1,2,3,4,5,6,7,8
//
// adjacency matrix
// 0,1,0,1,0,0,0,0,0
// 1,0,1,0,1,0,0,0,0
// 0,1,0,0,0,1,0,0,0
// 1,0,0,0,1,0,1,0,0
// 0,1,0,1,0,1,0,1,0
// 0,0,1,0,1,0,0,0,1
// 0,0,0,1,0,0,0,1,0
// 0,0,0,0,1,0,1,0,1
// 0,0,0,0,0,1,0,1,0
//
// reachability matrix
// 0,1,2,1,2,3,2,3,4
// 1,0,1,2,1,2,3,2,3
// 2,1,0,3,2,1,4,3,2
// 1,2,3,0,1,2,1,2,3
// 2,1,2,1,0,1,2,1,2
// 3,2,1,2,1,0,3,2,1
// 2,3,4,1,2,3,0,1,2
// 3,2,3,2,1,2,1,0,1
// 4,3,2,3,2,1,2,1,0
//
//
// heuristic=0
// h = 0;
//
//
// heuristic=1
// displacement
// h = 0;
// for i in board
//      if board[i] != checkBoard[i]
//          h++;
//
// 
// heuristic=2
// manhattan
// h = 0 ;
// for i in board
//      h += reach[board[i]][i];
//
//
// heuristic=3
// num out of row + num out of column
// h = 0;
// for i in board
//      if out of row
//      if (!((i>=0 && i<=2) && (board[i] >=0 && board[i] <=2)) ||
//          !((i>=3 && i<=5) && (board[i] >=3 && board[i] <=5)) ||
//          !((i>=6 && i<=8) && (board[i] >=6 && board[i] <=8)))
//          h++;
//      out of col
//      if !(board[i] == i || board[i] == i+3 || board[i] == i-3 || board[i] == i+6 || board[i] == i-6)
//          h++;
//
//

