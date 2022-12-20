typedef struct coordinate{
    int i; 
    int j; 
}coordinate;

typedef struct puzzleState
{
    /* data */
    unsigned int g;
    unsigned int h;
    unsigned int f;
    unsigned int **puzzle;
    struct coordinate *tilePosistion; 
    struct puzzleState *father;   
} puzzleState;