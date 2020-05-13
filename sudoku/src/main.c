/*
  Auteur : Clément Morand
  Date : 26/02/2020
  But : -implémenter un outil qui résoud n'importe quelle grille de sudoku faisable en utilisant l'algorithme de backtracking
        -donner un algorithme qui génère des grilles de sudoku valables (avec une seule solution)
        -permettre à l'utilisateur de rentrer une grille pour obtenir la solution / si c'est une grille valide
        -jouer au sudoku (s'intéresser à la gestion de la mémoire avec chargement d'une partie !)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#include "sudoku.h"

int main(int argc, char ** argv){
  srand((unsigned)time(NULL));
  // initialisations
  bool toSolve; // mode de fonctionnement : false si génération de grille, true si résolution de grille passée
  char test = 'A';
  printf("voulez vous résoudre la grille ou en g%cn%crer une nouvelle ? (r / g)\n", 130, 130);
  while(test != 'R' && test != 'r' && test != 'g' && test != 'G')
    scanf(" %c", &test);
  if(test == 'R' || test == 'r')
    toSolve = true;
  else
    toSolve = false;

  if(toSolve){
    // rentrer la grille ici
    // à faire : lire la grille depuis un fichier extérieur, comme ça il n'y aura plus besoin de compiler à chaque nouvelle grille
    int grille[SIZE][SIZE] = {
      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},

      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},

      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},
      {0, 0, 0,  0, 0, 0,  0, 0, 0},
    };
    int **solution = convert(grille);
    int nbSol = 0;
    solve(&solution, &nbSol);
    printf("votre grille poss%cde %d solutions", 138, nbSol);
    afficher(solution);
    system("PAUSE");
    freeGrid(&solution);
  }
  else{
    bool continuer = true;
    while(continuer){
      //génération d'une grille à solution unique
      int **solution = convert(grilleBase);
      shuffle(&solution);
      int **new = generate(solution);
      afficher(new);
      sauvegarde(new);

      freeGrid(&new);
      freeGrid(&solution);
      printf("voulez vous g%cn%crer une nouvelle grille ? (o/n)\n", 130, 130);
      test = 'A';
      while(test != 'O' && test != 'o' && test != 'N' && test != 'n'){
        printf("veuillez entrer un caract%cre parmi O, o, N ou n", 138);
        scanf(" %c",&test);
      }
      if(test == 'n' || test == 'N'){
        printf("Au revoir");
        continuer = false;
      }


    }
  }
  return 0;
}

//convertir un tableau statique en tableau dynamique
int **convert(const int grid[SIZE][SIZE]){
  int **new;
  allocateGrid(&new);
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      new[i][j] = grid[i][j];
    }
  }
  return new;
}

bool coup_valide(int **grid, COUP coup){
  if(coup.val < 0 || coup.val > 9 || conflit_ligne(grid, coup) || conflit_carre(grid, coup) || conflit_colonne(grid, coup))
    return false;
  return true;
}

bool conflit_ligne(int **grid, COUP coup){

  int i = 0;
  while( (coup.lig+i) < 9){
    if(grid[coup.lig + i][coup.col] == coup.val)
      return true;
    i++;
  }
  i = 1;
  while( (coup.lig-i) >= 0){
    if(grid[coup.lig - i][coup.col] == coup.val)
      return true;
    i++;
  }
  return false;
}

bool conflit_colonne(int **grid, COUP coup){

  int i = 0;
  while( (coup.col+i) < 9){
    if(grid[coup.lig][coup.col + i] == coup.val)
      return true;
    i++;
  }
  i = 1;
  while( (coup.col - i) >= 0){
    if(grid[coup.lig][coup.col - i] == coup.val)
      return true;
    i++;
  }
  return false;
}

bool conflit_carre(int **grid, COUP coup){

  int ligDepart = coup.lig/3 * 3;
  int colDepart = coup.col/3 * 3;
  for(int i = ligDepart; i < (ligDepart + 3); i++){
    for(int j = colDepart; j < (colDepart + 3); j++){
      if(grid[i][j] == coup.val)
        return true;
    }
  }
  return false;
}

void afficher(int **grid){

  for(int i =0; i < SIZE; i++){
    if(i % 3 == 0)
      printf("|---------|---------|---------|\n");
    for(int j = 0; j < SIZE; j++){
      if(j%3 == 0)
        printf("|");
      printf(" %d ", grid[i][j]);
    }
    printf("|\n");
  }
  printf("|---------|---------|---------|\n");
}

// trouver une cellule vide dans la grille
COUP find(int **grid){
    for(int i = 0; i < SIZE; i++){
      for(int j = 0; j < SIZE; j++){
        if(grid[i][j] == 0){
          COUP coup = {i, j, 1};
          return coup;
        }
      }
    }
    COUP coup = {0, 0, 0};
    return coup;
}

void solve(int ***grid, int *nbSol){
  /*
   on coupe dès qu'on a trouvé plus d'une solution
   car on a pas d'intêret à les trouver toutes, on veut juste savoir
   si la grille ne possède qu'une seule solution ou aucune
  */
  if(*nbSol > 1)
    return;
  COUP found = find(*grid);
  if(found.val == 0){
    *nbSol += 1;
  }else{
    for(int k = 1; k<10; k++){
      found.val = k;
      if(coup_valide(*grid, found)){
        (*grid)[found.lig][found.col] = found.val;
        solve(grid, nbSol);
        if(*nbSol > 1)
          return;
        (*grid)[found.lig][found.col] = 0;
      }
    }
  }
}

void initGrid(int ***grid){
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      (*grid)[i][j] = 0;
    }
  }
}

// renvoie un coup aléatoire
COUP randomCell(){
  int i = rand() % SIZE;
  int j = rand() % SIZE;
  int k = (rand() % SIZE) + 1;
  COUP coup = {i, j, k};
  return coup;
}

int** generate(int ** solution){
  /*
    on utilise la solution qui est une grille valide aléatoire,
    depuis la grille de solution on enlèvera le nombre de cases,
    on otera le nombre de cases choisis (nb)
  */
  int **grid;
  allocateGrid(&grid);
  duplicate(solution, &grid);
  COUP new;
  int tmp;
  while (nbSolGrid(grid) == 1){
    new = randomCell();
    tmp = grid[new.lig][new.col];
    grid[new.lig][new.col] = 0;
  }
  grid[new.lig][new.col] = tmp;
  return grid;
}

int nbSolGrid(int **grid){
  // renvoie le nombre de solutions possible sur la grille grid, comme solve modifie la grille, il nous faut la dupliquer
  int ct = 0;
  int **cpy;
  allocateGrid(&cpy);
  duplicate(grid, &cpy);
  solve(&cpy, &ct);
  freeGrid(&cpy);
  return ct;
}

// alouer un tableau dynamique à 2D de SIZE * SIZE
void allocateGrid(int ***grid){
  (*grid) = (int**)malloc(SIZE * sizeof(int*));
  for(int i = 0; i<SIZE; i++){
    (*grid)[i] = (int*)malloc(SIZE * sizeof(int));
  }
}

// copier les valeurs du tableau grid dans le tableau cpy
void duplicate(int **grid, int ***cpy){

  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      (*cpy)[i][j] = grid[i][j];
    }
  }
}

// rend la mémoire allouée à un tableau dynamique 2D SIZE*SIZE
void freeGrid(int ***cpy){
  for (int i = 0; i < SIZE; i++) {
    free((*cpy)[i]);
  }
  free(*cpy);
  cpy = NULL;
}

//mélanger une grille de sudoku de façon à garder sa cohérence
void shuffle(int ***grid){
  for(int j = 0; j < 4; j++){
    for(int i = 0; i < 3; i++){
      shuffleLig(grid, i*3);
    }
    for(int i = 0; i < 3; i++){
      shuffleCol(grid, i*3);
    }
  }
}

void shuffleCol(int ***grid, int colDepart){
  // on mélange les colones 3 à 3 pour garder la cohérence de la grille
  // il faut commencer par récupérer les trois colonnes qui nous intéressent
  int cols[3][SIZE];
  for(int j = colDepart; j < (colDepart + 3); j++){
    for(int i = 0; i<SIZE; i++){
      cols[j - colDepart][i] = (*grid)[i][j];
    }
  }

  int *comb = randCombinaison();
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < SIZE; j++){
      (*grid)[j][comb[i] + colDepart] = cols[i][j]; // les indices de comb vont de 0 à 2
    }
  }
  free(comb);
}

void shuffleLig(int ***grid, int ligDepart){
  int ligs[3][SIZE];
  for(int j = ligDepart; j < (ligDepart + 3); j++){
    for(int i = 0; i<SIZE; i++){
      ligs[j - ligDepart][i] = (*grid)[j][i];
    }
  }

  int *comb = randCombinaison();
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < SIZE; j++){
      (*grid)[comb[i] + ligDepart][j] = ligs[i][j]; // les indices de comb vont de 0 à 2
    }
  }
  free(comb);
}

int *randCombinaison(){
  int i = rand()%6;
  int *comb = (int*)malloc(3*sizeof(int));
  for(int j = 0; j < 3; j++){
    comb[j] = combinaisons[i][j];
  }
  return comb;
}

// permet à l'utilisateur, s'il le souhaite de sauvegarder la grille dans un fichier txt
void sauvegarde(int **grid){
  printf("voulez vous sauvegarder cette grille ?\n");
  char test = 'A';
  while(test != 'O' && test != 'o' && test != 'N' && test != 'n'){
    printf("veuillez entrer un caract%cre parmi O, o, N ou n", 138);
    scanf(" %c",&test);
  }
  if(test == 'O' || test == 'o'){
    printf("entrez le nom du fichier pour la sauvegarde :");
    char nom[50];
    FILE* newFile = NULL;
    while(newFile == NULL){
      scanf("%s", nom);
      nom[50] = '\0';
      char fileName[55];
      strcpy(fileName, nom);
      strcat(fileName, ".txt");
      newFile = fopen(fileName, "w");
       // on a pas un réel controle sur la validité du nom, on assure juste que la sauvegarde sera bien réalisée dans un fichier
      // (dont le nom ne sera pas forcément celui souhaité par l'utilisateur si le nom de fichier n'est pas valide)
      if(newFile == NULL)
        printf("nom de fichier non valide");
    }
    for(int i =0; i < SIZE; i++){
      if(i % 3 == 0)
        fprintf(newFile, "|---------|---------|---------|\n");
      for(int j = 0; j < SIZE; j++){
        if(j%3 == 0)
          fprintf(newFile, "|");
        fprintf(newFile, " %d ", grid[i][j]);
      }
      fprintf(newFile, "|\n");
    }
    fprintf(newFile, "|---------|---------|---------|\n");
    fclose(newFile);
  }
}
