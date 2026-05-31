#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct _DisjointSet {
    int size;
    int *ptr_arr; // parent
} DisjointSets;

typedef struct _PrintDisjointSet {
    int size;
    int *ptr_arr;
    // wall, (if wall exists -> 1, otherwise 0)
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n, int seed);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

void init(DisjointSets *sets, PrintDisjointSets *maze, int n, int seed) {
    int num_cells = n * n;
    
    if (seed == -1) {
        srand((unsigned int)time(NULL));
    } else {
        srand((unsigned int)seed);
    }
    
    sets->size = num_cells + 1;
    sets->ptr_arr = (int*)malloc(sizeof(int) * sets->size);
    for (int i = 1; i <= num_cells; i++) {
        sets->ptr_arr[i] = 0; 
    }
    
    maze->size = num_cells * 2;
    maze->ptr_arr = (int*)malloc(sizeof(int) * maze->size);
    for (int i = 0; i < maze->size; i++) {
        maze->ptr_arr[i] = 1; 
    }
}

int find(DisjointSets *sets, int x) {
    if (sets->ptr_arr[x] <= 0) {
        return x;
    }
    return sets->ptr_arr[x] = find(sets, sets->ptr_arr[x]);
}

void union_(DisjointSets *sets, int i, int j) {
    int root1 = find(sets, i);
    int root2 = find(sets, j);
    
    if (root1 != root2) {
        sets->ptr_arr[root2] = root1;
    }
}

void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    int num_cells = n * n;
    
    while (find(sets, 1) != find(sets, num_cells)) {
        int wall_idx = rand() % (num_cells * 2); 
        
        int cell1 = -1, cell2 = -1;
        
        if (wall_idx < num_cells) {
            cell1 = wall_idx + 1;
            if (cell1 % n != 0) { 
                cell2 = cell1 + 1;
            }
        } else {
            cell1 = (wall_idx - num_cells) + 1;
            if (cell1 <= num_cells - n) {
                cell2 = cell1 + n;
            }
        }
        
        if (cell2 != -1 && find(sets, cell1) != find(sets, cell2)) {
            union_(sets, cell1, cell2);    
            maze->ptr_arr[wall_idx] = 0;  
        }
    }
}
void printMaze(PrintDisjointSets *maze, int n) {
    int num_cells = n * n;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("*-");
        }
        printf("*\n");

        for (int c = 0; c < n; c++) {
            int cell_idx = r * n + c + 1;

            if (c == 0) {
                if (cell_idx == 1) printf(" ");
                else printf("|");
            }

            printf(" ");

            if (c == n - 1) {
                if (cell_idx == num_cells) printf(" \n");
                else printf("|\n");
            } else {
                int v_wall_idx = cell_idx - 1;
                if (maze->ptr_arr[v_wall_idx] == 0) printf(" ");
                else printf("|");
            }
        }
    }
    for (int c = 0; c < n; c++) {
        printf("*-");
    }
    printf("*\n");
}

void freeMaze(DisjointSets *sets, PrintDisjointSets *maze) {
    if (sets != NULL) {
        if (sets->ptr_arr != NULL) free(sets->ptr_arr);
        free(sets);
    }
    if (maze != NULL) {
        if (maze->ptr_arr != NULL) free(maze->ptr_arr);
        free(maze);
    }
}

int main(int argc, char* argv[]) {
    int num, seed;
    FILE *fi = fopen(argv[1], "r");
    
    int inputCount = fscanf(fi, "%d %d", &num, &seed);
    fclose(fi);
    
    if (inputCount < 2) seed = -1;
    
    DisjointSets *sets = (DisjointSets*)malloc(sizeof(DisjointSets));
    PrintDisjointSets *maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));
    
    init(sets, maze, num, seed);
    createMaze(sets, maze, num);
    printMaze(maze, num);
    freeMaze(sets, maze);
    
    return 0;
}
