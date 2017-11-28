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
#define iSpan 16
int iBoard[15][15];
int iMyside=0;
int iEneside=0;
char chGamestatus[10];

//evaluate
void fnEVA(){
    ;
}

//alpha beta pruning
void fnABP(){
    ;
}

//placing program's body
void fnPlace(){
    /*output standard
        printf("6 7\n");
        fflush(stdout);
    */
    int iROW,iCOL;
    for(iROW=0,iCOL=0;iROW<=15&&iCOL<=15;iROW++,iCOL++){
        //random
    }
}

//reply to stdin
void fnReply(){
    if(strcmp(chGamestatus, "TURN")==0){
        //my turn
        fnPlace();
    }
    else if(strcmp(chGamestatus,"PLACE")==0){
        //enemy's turn,record
        int iROW,iCOL;
        scanf("%d %d",&iROW,&iCOL);
        iBoard[iROW][iCOL]=iEneside;
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

//can reverse?

//make step

//undo step

//reverse count


int main(int argc, const char * argv[]) {
    //function prepare
    void fnReply(void);
    
    //set board to start
    memset(iBoard,0,sizeof(iBoard));
    iBoard[8][8]=iBoard[9][9]=WHITE;
    iBoard[8][9]=iBoard[9][8]=BLACK;
    
    //set basic evaluate parameters
    
    //test area
    
    //game start
    while(strcmp(chGamestatus,"END")!=0){
        scanf("%s",chGamestatus);
        fnReply();
    }
}
