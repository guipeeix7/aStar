// #include "./minHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../puzzle/puzzle.c"
#include "./../heap/minHeap.c"



int heuristic(puzzleState *node){
    int res = 0;
    for(int i = 0 ; i < sizeofPuzzle ; i++){
        for(int j = 0 ; j < sizeofPuzzle ; j++){
            if(node->puzzle[i][j] == 0 || node->puzzle[i][j] == solved[i][j]) continue; 
            int y = (int) floor((node->puzzle[i][j]/sizeofPuzzle));
            int x = abs(node->puzzle[i][j]%sizeofPuzzle);
            res += abs(y) + abs(x);
        }
    }

    return res; 
}


void aStarSearch(puzzleState *initialState){
    MinHeap* openHeap = init_minheap(initialState);
    MinHeap* closedHeap = init_minheap(initialState);
    delete_element(closedHeap, 0);


    while(!checkIfEmpty(openHeap)){
        // let the currentNode equal the node with the least f value
        puzzleState *currentPuzzleState =  (puzzleState *) malloc(sizeof(puzzleState));
        
        *currentPuzzleState = *openHeap->arr[0]; 
        delete_element(openHeap, 0);
        insert_minheap(closedHeap, currentPuzzleState); 

        if(currentPuzzleState->f == 0){
            printf("Solution founded!");
            return;
        }

        int *avaliablePos = (int*) calloc(4 , sizeof(int));
        avaliableTilePositions(currentPuzzleState->tilePosistion, avaliablePos);

        if(avaliablePos[0] == 1){
            coordinate *tilePosistion = (coordinate*) malloc(sizeof(coordinate)); 
            tilePosistion->i = currentPuzzleState->tilePosistion->i - 1;
            tilePosistion->j = currentPuzzleState->tilePosistion->j;            
            insert_minheap(openHeap, insert(currentPuzzleState, tilePosistion));
        }

        if(avaliablePos[1] == 1){
            coordinate *tilePosistion = (coordinate*) malloc(sizeof(coordinate)); 
            tilePosistion->i = currentPuzzleState->tilePosistion->i;
            tilePosistion->j = currentPuzzleState->tilePosistion->j + 1;
            insert_minheap(openHeap, insert(currentPuzzleState, tilePosistion));
        }
        if(avaliablePos[2] == 1){
            coordinate *tilePosistion = (coordinate*) malloc(sizeof(coordinate)); 
            tilePosistion->i = currentPuzzleState->tilePosistion->i + 1;
            tilePosistion->j = currentPuzzleState->tilePosistion->j;
            insert_minheap(openHeap, insert(currentPuzzleState, tilePosistion));
        }
        
        if(avaliablePos[3] == 1){
            coordinate *tilePosistion = (coordinate*) malloc(sizeof(coordinate)); 
            tilePosistion->i = currentPuzzleState->tilePosistion->i ;
            tilePosistion->j = currentPuzzleState->tilePosistion->j - 1;
            insert_minheap(openHeap, insert(currentPuzzleState, tilePosistion));
        }



        free(avaliablePos);
        // let the children of the currentNode equal the adjacent nodes
        //Pausaa
    }    
}