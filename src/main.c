#include <stdio.h>
#include <stdlib.h>

/*

                PROJET N°20 : Taquin
                L1-X Informatique
                MARCORY Claire
                KANOUTE Daouda
*/

typedef int game [10][10];
typedef int resolve [1000];

//Vérifier si le programme a atteint le goal
int isCorrect(game grid, game goal, int n){
    int x, y;
    for(x = 0; x < n; x++){
        for(y = 0; y < n; y++){
            if (grid[x][y] != goal[x][y]){
              return 0;
            }
        }
    }
    return 1;
}

//Effectuer un mouvement
void move (game grid, int x, int y, int zero_x, int zero_y){
    grid[zero_x][zero_y] = grid[x][y];
    grid[x][y] = 0;
    return;
}

// Verifie si la case vide ne depasse pas la case vide ne sort pas de la grille
int inBound (int n, int x, int y){
    if ((x >= 0) && (x < n) && (y >= 0) && (y < n)){
        return 1;
    }
    return 0;
}


// Afficher la grille
void display (game grid, int n){
    int x, y;
    for (x = 0; x < n; x++){
        printf("\t\t");
        for (y = 0; y < n; y++){
            printf("%4d", grid[x][y]);
        }
        printf("\n");
    }
}

// Affiche la solution mouvement par mouvement à l'aide de display et du tableau solution contenant les "played", les mouvements effectués
void display_swap (game grid, resolve solution, int n, int zero_x, int zero_y, int depth){
    int i;
    for (i = 0; i < depth; i++){
        if (solution[i] == 1){
            printf("\t\t coup %d : bas\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x + 1][zero_y];
            grid[zero_x + 1][zero_y] = 0;
            display(grid, n);
            printf("\n");
            zero_x = zero_x + 1;
        }
        if (solution[i] == 11){
            printf("\t\t coup %d : bas (case 1x2)\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x + 2][zero_y];
            grid[zero_x + 2][zero_y] = 0;
            display(grid, n);
            printf("\n");
            zero_x = zero_x + 2;
        }
        if (solution[i] == 2){
            printf("\t\t coup %d : haut\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x - 1][zero_y];
            grid[zero_x - 1][zero_y] = 0;
            display(grid, n);
            printf("\n");
            zero_x = zero_x - 1;
        }
        if (solution[i] == 12){
            printf("\t\t coup %d : haut (case 1x2)\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x - 2][zero_y];
            grid[zero_x - 2][zero_y] = 0;
            display(grid, n);
            printf("\n");
            zero_x = zero_x - 2;
        }
        if (solution[i] == 3){
            printf("\t\t coup %d : droite\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x][zero_y + 1];
            grid[zero_x][zero_y + 1] = 0;
            display(grid, n);
            printf("\n");
            zero_y = zero_y + 1;
        }
        if (solution[i] == 13){
            printf("\t\t coup %d : droite (case 1x2)\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x][zero_y + 2];
            grid[zero_x][zero_y + 2] = 0;
            display(grid, n);
            printf("\n");
            zero_y = zero_y + 2;
        }
        if (solution[i] == 4){
            printf("\t\t coup %d : gauche\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x][zero_y - 1];
            grid[zero_x][zero_y - 1] = 0;
            display(grid, n);
            printf("\n");
            zero_y = zero_y - 1;
        }
        if (solution[i] == 14){
            printf("\t\t coup %d : gauche (case 1x2)\n", i + 1);
            grid[zero_x][zero_y] = grid[zero_x][zero_y - 2];
            grid[zero_x][zero_y - 2] = 0;
            display(grid, n);
            printf("\n");
            zero_y = zero_y - 2;
        }
    }
}

// fonction principale, elle effectue les mouvements et la recherche de solution
// grid_safe > une "copie" de la grille de départ qui va être utilisé pour afficher la solution trouvée
// z_x / z_y > la première position de la case vide (0), dans le grid de départ 
// grid > grille de départ
// goal > grille d'arrivée
// n > dimension de la grille (n*n)
// zero_x / zero_y > position de la case "vide" ici représenté par un 0
// depth > le nombre de coups effectués, s'incrémente après chaque appel de la fonction taquin
// max_depth > nombre de coups maximum, on recherche une solution qui s'effectue en moins de coups que max_depth
// played > donner une valeur à chaque move effectué (1 pour bas, 11 pour bas avec une case 1x2, 2 pour haut, 12 pour haut avec une case 1x2...)
// moves > tableau qui continent la solution que l'on vient de trouver (les played effectués lors de la recherche de solution)
// solution > tableau final, celui qui contient la meilleure solution
void taquin (game grid_safe, int z_x, int z_y, game grid, game goal, int n, int zero_x, int zero_y, int depth, int max_depth, int played, resolve moves, resolve solution){

    // Sil y'a trop de coups (plus que depth_max), s'arrêter
    if (depth >= max_depth){
        return;
    }

    // Faire un tableau contenant les coups que l'on vient d'effectuer
    if (depth != 0){
        moves[depth - 1] = played;
    }

    // une fois une solution trouvée, faire un tableau "solution" qui contient les mouvements effectués pour résoudre le taquin
    if (isCorrect(grid, goal, n)){
        printf("solution trouvée en  %d étapes\n\n", depth);
        int i;
        for(i = 0; i < depth; i++){
            solution[i] = moves[i];
        }
        display_swap(grid_safe, solution, n, z_x, z_y, depth);
        exit(0);
    }
    
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;

    // mvt vers le bas
    x1 = zero_x + 1;
    y1 = zero_y;

    // mvt vers le haut
    x2 = zero_x - 1;
    y2 = zero_y;

    // mvt vers la droite
    x3 = zero_x;
    y3 = zero_y + 1;

    // mvt vers la gauche
    x4 = zero_x;
    y4 = zero_y - 1;

        // PERMUTATION

    // coup vers le bas, avec une case 1x2
    if (inBound(n, x1 + 1, y1) && (grid[x1][y1] == grid[x1 + 1][y1]) && (played != 12)){
        move(grid, x1 + 1, y1, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x1 + 1, y1, depth + 1, max_depth, 11, moves, solution);
        grid[x1 + 1][y1] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers le haut, avec une case 1x2
    if (inBound(n, x2 - 1, y2) && (grid[x2][y2] == grid[x2 - 1][y2]) && (played != 11)){
        move(grid, x2 - 1, y2, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x2 - 1, y2, depth + 1, max_depth, 12, moves, solution);
        grid[x2 - 1][y2] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers la droite, avec une case 1x2
    if (inBound(n, x3, y3 + 1) && (grid[x3][y3] == grid[x3][y3 + 1]) && (played != 14)){
        move(grid, x3, y3 + 1, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x3, y3 + 1, depth + 1, max_depth, 13, moves, solution);
        grid[x3][y3 + 1] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers la gauche, avec une case 1x2
    if (inBound(n, x4, y4 - 1) && (grid[x4][y4] == grid[x4][y4 - 1]) && (played != 13)){
        move(grid, x4, y4 - 1, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x4, y4 - 1, depth + 1, max_depth, 14, moves, solution);
        grid[x4][y4 - 1] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers le bas
    if (inBound(n, x1, y1) && (played != 2) && (grid[x1][y1] != grid[x1 + 1][y1]) && (grid[x1][y1] != grid[x1][y1 + 1]) && (grid[x1][y1] != grid[x1][y1 - 1])){
        move(grid, x1, y1, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x1, y1, depth + 1, max_depth, 1, moves, solution);
        grid[x1][y1] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers le haut
    if (inBound(n, x2, y2) && (played != 1) && (grid[x2][y2] != grid[x2 - 1][y2]) && (grid[x2][y2] != grid[x2][y2 + 1]) && (grid[x2][y2] != grid[x2][y2 - 1])){
        move(grid, x2, y2, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x2, y2, depth + 1, max_depth, 2, moves, solution);
        grid[x2][y2] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
    // coup vers la droite
    if (inBound(n, x3, y3) && (played != 4) && (grid[x3][y3] != grid[x3][y3 + 1]) && (grid[x3][y3] != grid[x3 + 1][y3]) && (grid[x3][y3] != grid[x3 - 1][y3])){
        move(grid, x3, y3, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x3, y3, depth + 1, max_depth, 3, moves, solution);
        grid[x3][y3] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0; 
    }
    // coup vers la gauche
    if (inBound(n, x4, y4) && (played != 3) && (grid[x4][y4] != grid[x4][y4 - 1]) && (grid[x4][y4] != grid[x4 + 1][y4]) && (grid[x4][y4] != grid[x4 - 1][y4])){
        move(grid, x4, y4, zero_x, zero_y);
        taquin(grid_safe, z_x, z_y, grid, goal, n, x4, y4, depth + 1, max_depth, 4, moves, solution);
        grid[x4][y4] = grid[zero_x][zero_y]; grid[zero_x][zero_y] = 0;
    }
}

int main(){
    int dimension = 4; // les dimensions de notre grille de taquin (3x3, 4x4.....), toujours un carré 
    int max_depth = 30; // le nombre de coup maximum que l'on souhaite avoir (si aucune solution n'est possible avec ce nombre de coup, la fonction taquin ne renvoie rien)
    game grid = {{7, 1, 3, 3},{7, 4, 4, 5},{8, 0, 10, 9},{11, 2, 12, 6}}; // la grille de départ
    game grid_safe = {{7, 1, 3, 3},{7, 4, 4, 5},{8, 0, 10, 9},{11, 2, 12, 6}}; // la grille de départ qui va servir pour afficher la solution
    game goal = {{1, 2, 3, 3},{4, 4, 5, 6},{7, 8, 9, 10},{7, 11, 12, 0}}; // notre objectif
    resolve moves;
    resolve solution;
    int i, j;
    int origin_x, origin_y;
    // chercher la case vide dans la grille de départ
    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension; j++){
            if (grid[i][j] == 0){
                origin_x = i;
                origin_y = j;
                break;
            }
        }
    }
    printf("\n\t\t** GRILLE DE DEPART **\n\n"); display(grid, dimension); printf("\n");
    taquin(grid_safe, origin_x, origin_y, grid, goal, dimension, origin_x, origin_y, 0, max_depth, 0, moves, solution);
}
