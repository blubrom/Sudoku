#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9
#define LONGUEUR_GRILLE 900
#define HAUTEUR_GRILLE 900
#define FPS 15
#define FRAME_DELAY 1000 / FPS

const   int combinaisons[6][3] = {
    {0,1,2},
    {0,2,1},
    {1,0,2},
    {1,2,0},
    {2,0,1},
    {2,1,0}
  };

const int grilleBase[SIZE][SIZE] = {
                    {1, 2, 3,   4, 5, 6,   7, 8, 9},
                    {7, 8, 9,   1, 2, 3,   4, 5, 6},
                    {4, 5, 6,   7, 8, 9,   1, 2, 3},

                    {9, 1, 2,   3, 4, 5,   6, 7, 8},
                    {3, 4, 5,   6, 7, 8,   9, 1, 2},
                    {6, 7, 8,   9, 1, 2,   3, 4, 5},

                    {8, 9, 1,   2, 3, 4,   5, 6, 7},
                    {2, 3, 4,   5, 6, 7,   8, 9, 1},
                    {5, 6, 7,   8, 9, 1,   2, 3, 4}
                  }; // la grille initiale qu'on mélange pour la génération

typedef struct COUP{
  int lig;
  int col;
  int val;
}COUP;

bool coup_valide(int **grid, COUP coup);
bool conflit_ligne(int **grid, COUP coup);
bool conflit_colonne(int **grid, COUP coup);
bool conflit_carre(int **grid, COUP coup);
void afficher(int **grid);
COUP find(int **grid);
void solve(int ***grid, int*nbSol);
void initGrid(int ***grid);
int **generate(int ** solution);
void duplicate(int **grid, int ***cpy);
COUP randomCell();
void freeGrid(int ***cpy);
void allocateGrid(int ***cpy);
int nbSolGrid(int **grid);
int **convert(const int grid[SIZE][SIZE]);
void shuffle(int ***grid);
void shuffleLig(int ***grid, int ligDepart);
void shuffleCol(int ***grid, int colDepart);
int *randCombinaison();
void sauvegarde(int **grid);



#endif
