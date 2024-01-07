#include <stdio.h>
#include <string.h>

int main(void) {
    FILE* start_file = fopen("project.txt", "r");
    // переменные
    int counter_files;
    int number = fscanf(start_file, "%d\n", &counter_files);
    //printf("counter files: %d", counter_files);
    int counter_files_flag = 0;
    // переменные

    char file_name[1000];
    while(counter_files_flag < counter_files){
        // переменные
        char first_symbol;
        char second_symbol;
        int flag_quotes_1 = 0;
        int flag_quotes_2 = 0;
        int quotes = 0;
        // переменные

        fgets(file_name, 35, start_file);
        if (feof(start_file) == 0){
            file_name[strlen(file_name)-1]='\0';
        }


        FILE *input = fopen(file_name, "r");
        int name_length = strlen(file_name); // длина имени файла

        for (int j = name_length; j >= 0; j--) {
            if (file_name[j] == '.') {
                file_name[j + 1] = 'w';
                file_name[j + 2] = 'c';
                file_name[j + 3] = '\0';
                break;
            }
        }

        FILE *output = fopen(file_name, "w");

        // cчитывание первого символа для проверки на ковычки 1.0
        if (feof(input) == 0) {
            first_symbol = fgetc(input);
        }

        // проверка на ковычки 1.1
        if (first_symbol == '"') {
            quotes++;
        }


        while (feof(input) == 0) {
            second_symbol = fgetc(input);

            // проверка на ковычки 1.2
            if (second_symbol == '"'  && first_symbol != '\\' && first_symbol != '\'' && flag_quotes_1 != 1 && flag_quotes_2 != 1) {
                quotes++;
            }

            // проверка на (1) комментарий в 2 кавычках
            if (first_symbol == '/' && second_symbol == '*' && flag_quotes_1 == 0 && flag_quotes_2 == 0 && quotes % 2 == 0) {
                first_symbol = fgetc(input);
                second_symbol = fgetc(input);
                flag_quotes_1 = 1;
            }


           
            // проверка на (2) комментарий 
            if (first_symbol == '/' && second_symbol == '/' && quotes % 2 == 0) {
                flag_quotes_2 = 1;
            }

            // посимвольное добавление в выходной файл
            if (flag_quotes_1 == 0 && flag_quotes_2 == 0) {
                fputc(first_symbol, output);
            }

            // проверка на (1) комментарий 
            if (second_symbol == '/' && first_symbol == '*' && flag_quotes_1 == 1) {
                second_symbol = fgetc(input);
                flag_quotes_1 = 0;
            }


            if (first_symbol == '\\' && flag_quotes_2 == 1) {
                flag_quotes_2 = 1;
                first_symbol = fgetc(input);
                second_symbol = fgetc(input);
            }

            // проверка на перенос
            if (second_symbol == '\n' && flag_quotes_2 == 1 && first_symbol != '\\') {
                flag_quotes_2 = 0;
            }

            ///////////////////////////////////////////////////////////////
            first_symbol = second_symbol;
            ///////////////////////////////////////////////////////////////
        }

        if(flag_quotes_2 == 0 && flag_quotes_1 == 0 && first_symbol != -1){
            fputc(first_symbol, output);
        }
        counter_files_flag++;
        
    }
    fclose(start_file);
}