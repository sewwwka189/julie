#include <stdio.h>
#include <string.h>


int not_under_attack(int game_field_aboba[][25], int N, int x, int y) {
    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

    for (int k = 0; k < 8; k++) {
        int new_x = x + dx[k];
        int new_y = y + dy[k];
        if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N) {
            if (game_field_aboba[new_x][new_y] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

void rasstanovka(int board[][25], int N, int L, int x, int y) {
    if (L == 0) { // все фигуры расставлены, выводим координаты позиций, где стоит единица
        FILE* input_file = fopen("output.txt", "a");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 1) {
                    fprintf(input_file, "(%d,%d) ", i, j);
                }
            }
        }
        fprintf(input_file, "\n");
        fclose(input_file);
        return;
    }
    for (int i = x; i < N; i++) {
        if (i > x)
            y = 0;
        for (int j = y; j < N; j++) {
            if (board[i][j] == 0 && (not_under_attack(board, N, i, j) == 1)) {
                board[i][j] = 1;
                if (j == N - 1) {
                    rasstanovka(board, N, L - 1, i + 1, 0);
                }else {
                    rasstanovka(board, N, L - 1, i, y + 1);
                }
                board[i][j] = 0;
            }
        }
    }
}

int main() {
    // |N           |   |L               |        |K              |
    // |размер доски|   |нужно расставить|        |уже расставлены|
    int N, L, K;
    FILE* input_file = fopen("input.txt", "r");
    FILE* output_file = fopen("output.txt", "w");
    fscanf(input_file, "%d %d %d", &N, &L, &K);
    int board[25][25];
    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 25; j++){
            board[i][j] = 0;
        }
    }
    // заполняем доску фигурами, 1 - место занято, 0 - свободно
    for (int i = 0; i < K; i++) { 
        int x, y;
        fscanf(input_file, "%d %d", &x, &y);
        board[x][y] = 1;
    }
    output_file = fopen("output.txt", "w");
    rasstanovka(board, N, L, 0, 0);
    // открываем файл на чтение, чтобы просмотреть, есть ли там результаты
    output_file = fopen("output.txt", "r");
    // если в файле нет никаких решений, то no solutions
    if (fgetc(output_file) == EOF) {
        output_file = fopen("output.txt", "w");
        fprintf(output_file, "no solutions");
    }
    fclose(input_file);
    fclose(output_file);
}