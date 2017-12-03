//
//  main.c
//  Reversi
//  Brain Code
//  Created by Khazeus on 28/11/2017.
//  Copyright © 2017 Khazeus. All rights reserved.
//

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#define NONE 0
#define BLACK 1
#define WHITE 2
#define SPAN 16
int iBoard[SPAN-1][SPAN-1];
int iMyside=0;
int iEneside=0;
char chGamestatus[10];

//估值函数
void fnEVA(){
    ;
}

//alpha beta 剪枝
void fnABP(){
    ;
}

//调整检查函数
void U(int *pRow,int *pCol){
    *pRow-=1;
}

void UL(int *pRow,int *pCol){
    *pCol-=1;
    *pRow-=1;
}

void L(int *pRow,int *pCol){
    *pCol-=1;
}

void DL(int *pRow,int *pCol){
    *pCol-=1;
    *pRow+=1;
}

void D(int *pRow,int *pCol){
    *pRow+=1;
}

void DR(int *pRow,int *pCol){
    *pCol+=1;
    *pRow+=1;
}

void R(int *pRow,int *pCol){
    *pCol+=1;
}

void UR(int *pRow,int *pCol){
    *pCol+=1;
    *pRow-=1;
}

//查看是否越出棋盘边界
bool fnValid(int iRow,int iCol){
    if(iRow<0||iRow>SPAN-1||iCol>SPAN-1||iCol<0){
        return false;
    }
    else{
        return true;
    }
}

//翻转计数
int fnRevcount(int iRow,int iCol,int iSide,void (*direction)(int *,int *)){
    int iTurn=0;
    int i=iRow;
    int j=iCol;
    (direction)(&i,&j);
    if(iBoard[i][j]==NONE||iBoard[i][j]==iSide){
        iTurn=0;
    }
    else{
        while(fnValid(i,j)&&iBoard[i][j]!=iSide&&iBoard[i][j]!=NONE){
            iTurn++;
            (direction)(&i,&j);
        }
        if(!fnValid(i,j)){
            iTurn=0;
        }
        else if(iBoard[i][j]==NONE){
            iTurn=0;
        }
    }
    return iTurn;
}

//落子是否能翻转
bool fnAblecheck(int iRow,int iCol,int iSide){
    if(fnRevcount(iRow,iCol,iSide,U)>=1
       ||fnRevcount(iRow,iCol,iSide,UL)>=1
       ||fnRevcount(iRow,iCol,iSide,L)>=1
       ||fnRevcount(iRow,iCol,iSide,DL)>=1
       ||fnRevcount(iRow,iCol,iSide,D)>=1
       ||fnRevcount(iRow,iCol,iSide,DR)>=1
       ||fnRevcount(iRow,iCol,iSide,R)>=1
       ||fnRevcount(iRow,iCol,iSide,UR)>=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//下棋
void fnPlace(){
    /*输出标准格式
     printf("6 7\n");
     fflush(stdout);
     */
    int iRow,iCol;
    for(iRow=0,iCol=0;iRow<=SPAN-1&&iCol<=SPAN-1;iRow++,iCol++){
        //随机函数
        if(fnAblecheck(iRow,iCol,iMyside)){
            printf("%d %d\n",iRow,iCol);
        }
    }
}

//回复stdin
void fnReply(){
    if(strcmp(chGamestatus,"TURN")==0){
        //my turn
        fnPlace();
    }
    else if(strcmp(chGamestatus,"PLACE")==0){
        //enemy's turn,record
        int iRow,iCol;
        scanf("%d %d",&iRow,&iCol);
        iBoard[iRow][iCol]=iEneside;
    }
    else if(strcmp(chGamestatus,"START")==0){
        //game start,prepare and reply
        scanf("%d",&iMyside);
        if(iMyside==BLACK){
            iEneside=WHITE;
        }
        else if(iMyside==WHITE){
            iEneside=BLACK;
        }
        printf("OK\n");
        fflush(stdout);
    }
}


//模拟下子
void fnMove(){
    ;
}
//撤销下子
void fnUnmove(){
    ;
}

int main(int argc, const char * argv[]) {
    //声明函数或变量
    
    //初始化棋盘
    memset(iBoard,0,sizeof(iBoard));
    iBoard[8][8]=iBoard[9][9]=WHITE;
    iBoard[8][9]=iBoard[9][8]=BLACK;
    
    //设置估值函数基本参数
    
    //调试用区
    
    //游戏开始
    while(strcmp(chGamestatus,"END")!=0){
        scanf("%s",chGamestatus);
        fnReply();
    }
}
