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
#define SPAN 8
int iBoard[SPAN][SPAN];
int iMyside=0;
int iEneside=0;
char chGamestatus[10];
//需要拓宽8->16
int TopoBoard[SPAN][SPAN]={
    { 90,-60, 10, 10, 10, 10,-60, 90},
    {-60,-80,  5,  5,  5,  5,-80,-60},
    { 10,  5,  1,  1,  1,  1,  5, 10},
    { 10,  5,  1,  1,  1,  1,  5, 10},
    { 10,  5,  1,  1,  1,  1,  5, 10},
    { 10,  5,  1,  1,  1,  1,  5, 10},
    {-60,-80,  5,  5,  5,  5,-80,-60},
    { 90,-60, 10, 10, 10, 10,-60, 90}
};

//测试用
void fnPrintBoard(){
    int i;
    int j;
    for(i=0;i<=SPAN-1;i++){
        for(j=0;j<=SPAN-1;j++){
            printf("%d ",iBoard[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//估值函数
int fnEVA(){
    int iTotal=0;
    //地势因素
    int iRow,iCol;
    for(iRow=0;iRow<=SPAN-1;iRow++){
        for(iCol=0;iCol<=SPAN-1;iCol++){
            if(iBoard[iRow][iCol]==iMyside){
                ;
            }
        }
    }
    return iTotal;
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
    if(iBoard[iRow][iCol]!=NONE){
        return false;
    }
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

int fnFlipone(int iRow,int iCol,int iSide,void (*direction)(int *,int *)){
    int iTurn=fnRevcount(iRow,iCol,iSide,direction);
    int iCount=iTurn;
    if(iCount>=1){
        for(;iCount>0;iCount--){
            (direction)(&iRow,&iCol);
            iBoard[iRow][iCol]=iSide;
        }
    }
    return iTurn;
}

int iU,iUL,iL,iDL,iD,iDR,iR,iUR;
//模拟下子
void fnFlip(int iRow,int iCol,int iSide){
    iBoard[iRow][iCol]=iSide;
    iU=fnFlipone(iRow,iCol,iSide,U);
    iUL=fnFlipone(iRow,iCol,iSide,UL);
    iL=fnFlipone(iRow,iCol,iSide,L);
    iDL=fnFlipone(iRow,iCol,iSide,DL);
    iD=fnFlipone(iRow,iCol,iSide,D);
    iDR=fnFlipone(iRow,iCol,iSide,DR);
    iR=fnFlipone(iRow,iCol,iSide,R);
    iUR=fnFlipone(iRow,iCol,iSide,UR);
}
//撤销下子
void fnUnFlipone(int iRow,int iCol,int iSide,int iTurn,void (*direction)(int *,int *)){
    if(iSide==WHITE){
        for(;iTurn>0;iTurn--){
            (direction)(&iRow,&iCol);
            iBoard[iRow][iCol]=BLACK;
        }
    }
    else if(iSide==BLACK){
        for(;iTurn>0;iTurn--){
            (direction)(&iRow,&iCol);
            iBoard[iRow][iCol]=WHITE;
        }
    }
}

void fnUnFlip(int iRow,int iCol,int iSide){
    iBoard[iRow][iCol]=NONE;
    fnUnFlipone(iRow,iCol,iSide,iU,U);
    fnUnFlipone(iRow,iCol,iSide,iUL,UL);
    fnUnFlipone(iRow,iCol,iSide,iL,L);
    fnUnFlipone(iRow,iCol,iSide,iDL,DL);
    fnUnFlipone(iRow,iCol,iSide,iD,D);
    fnUnFlipone(iRow,iCol,iSide,iDR,DR);
    fnUnFlipone(iRow,iCol,iSide,iR,R);
    fnUnFlipone(iRow,iCol,iSide,iUR,UR);
}


//alpha beta 剪枝
void fnABP(){
    ;
}

//下棋
void fnPlace(){
    /*输出标准格式
     printf("6 7\n");
     fflush(stdout);
     */
    ;
    /*随机落子*/
    int iRow,iCol;
    bool temp=false;
    for(iRow=0;iRow<=SPAN-1;iRow++){
        for(iCol=0;iCol<=SPAN-1;iCol++){
            if(fnAblecheck(iRow,iCol,iMyside)){
                printf("%d %d\n",iRow,iCol);
                fflush(stdout);
                fnFlip(iRow,iCol,iMyside);
                //fnPrintBoard();
                temp=true;
                break;
            }
        }
        if(temp==true){
            break;
        }
    }
    /**/
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
        fnFlip(iRow,iCol,iEneside);
        //fnPrintBoard();
        /*fnUnFlip(iRow, iCol, iEneside);
        fnPrintBoard();*/
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

int main(int argc, const char * argv[]) {
    //声明函数或变量
    
    //初始化棋盘
    memset(iBoard,0,sizeof(iBoard));
    iBoard[SPAN/2-1][SPAN/2-1]=iBoard[SPAN/2][SPAN/2]=WHITE;
    iBoard[SPAN/2-1][SPAN/2]=iBoard[SPAN/2][SPAN/2-1]=BLACK;
    //fnPrintBoard();
    
    //设置估值函数基本参数
    
    //调试用区
    
    //游戏开始
    while(strcmp(chGamestatus,"END")!=0){
        scanf("%s",chGamestatus);
        fnReply();
    }
}
