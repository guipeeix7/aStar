
#include "./puzzle.h"

int sizeofPuzzle; 
int **solved;

puzzleState *initPuzzleState(unsigned int **data){
    puzzleState *headNode = (puzzleState*) malloc(sizeof(puzzleState));
    headNode->g = 0; 
    headNode->h = 999999; 
    headNode->f = 999999;
    headNode->puzzle = data;
    headNode->father = NULL;
    headNode->tilePosistion->i = 0;
    headNode->tilePosistion->j = 0;
    
    return headNode;
}

int *avaliableTilePositions(coordinate *tilePosition, int *avaliablePos){
    if(tilePosition->i != 0) //Top
        avaliablePos[0] = 1;
    if(tilePosition->j != (sizeofPuzzle-1))
        avaliablePos[1] = 1; 
    if(tilePosition->i != (sizeofPuzzle-1))
        avaliablePos[2] = 1;
    if(tilePosition->j != (0))
        avaliablePos[3] = 1;    
}

puzzleState *insert(puzzleState *father, coordinate *tilePosistion){
    puzzleState *currentNode = (puzzleState*) malloc(sizeof(puzzleState));
    
    // headNode->puzzle = father->puzzle; //This data is coming from static movements that could be created right here (; 
    coordinate *fatherTile; 
    fatherTile = father->tilePosistion;  
    
    coordinate *fathePrevVal; 
    fathePrevVal = tilePosistion; 

    //The movement
    currentNode->puzzle[fatherTile->i][fatherTile->j] = currentNode->puzzle[tilePosistion->i][tilePosistion->j];
    currentNode->puzzle[tilePosistion->i][tilePosistion->j] = currentNode->puzzle[fatherTile->i][fatherTile->j];
    //End of the movement

    currentNode->father = father;
    currentNode->tilePosistion->i = tilePosistion->i;
    currentNode->tilePosistion->j = tilePosistion->j;

    currentNode->g = father->g; 
    currentNode->h = heuristic(currentNode); 
    currentNode->f = currentNode->g + currentNode->h;

    return currentNode;
}


int main(){
    sizeofPuzzle = 0; 
    coordinate *tilePosition = (coordinate*) malloc(sizeof(coordinate)); 
    tilePosition->i = 0; 
    tilePosition->j = 0;


    scanf("%d", &sizeofPuzzle);
    int **tempData = (int **) malloc(sizeofPuzzle*sizeof(int *));
    for(int i = 0 ; i < sizeofPuzzle ; i++){
        tempData[i] = (int *) malloc(sizeofPuzzle*sizeof(int));    
    }

    for(int i = 0; i < sizeofPuzzle; i++)
    {
        for(int j = 0; j < sizeofPuzzle; j++) 
        {
        //Use lf format specifier, %c is for character
            if(!scanf("%d ", &tempData[i][j])) 
                break;
            if(tempData[i][j] == 0){
                tilePosition->i = i;
                tilePosition->j = j;
            }
        }
    }

    puzzleState *initialState = initPuzzleState(tempData);
    

    int **solved = (int **) malloc(sizeofPuzzle*sizeof(int *));
    for(int i = 0 ; i < sizeofPuzzle ; i++){
        solved[i] = (int *) malloc(sizeofPuzzle*sizeof(int));    
    }   
    
    int count = 0;
    for(int i = 0 ; i < sizeofPuzzle ; i++){
        for(int j = 0 ; j < sizeofPuzzle ; j++){
            solved[i][j] = count++;    
        }
    }   
        
    //aStarEnd




    for(int i = 0 ; i < sizeofPuzzle ; i++){
        for(int j = 0; j < sizeofPuzzle; j++){
            printf("%d ",tempData[i][j]);
        }
        printf("\n");
    }

    for(int i = 0 ; i < sizeofPuzzle ; i++){
        free(tempData[i]);
        free(solved[i]);    
    }
    free(tempData);
    free(solved);
}
