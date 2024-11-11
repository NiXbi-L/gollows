#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <windows.h> 
#pragma warning(disable: 4996)

int getRandomNumber(int max) {
    srand(time(NULL));
    int randomNumber = rand() % max;

    return randomNumber;
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    setlocale(LC_ALL, "ru_RU.CP1251");
    system("chcp 1251");
    system("cls");

    FILE* file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }
    const char gallows[11][256] = {
        " ",
            "-----",
            "  |\n-----",
            "  |\n  |\n-----",
            "  |\n  |\n  |\n-----",
            "  |\n  |\n  |\n  |\n-----",
            " _______\n  |\n  |\n  |\n  |\n-----",
            " _______\n  |   |\n  |\n  |\n  |\n-----",
            " _______\n  |   |\n  |   0\n  |\n  |\n-----",
            " _______\n  |   |\n  |   0\n  |  /|\\\n  |\n-----",
            " _______\n  |   |\n  |   0\n  |  /|\\\n  |.../\\\n-----",
    };

    char line[256];
    int wordnum = getRandomNumber(100);
    
    for (int i = 0; fgets(line, sizeof(line), file); i++) {
        if (i == wordnum) break;
    }
    char gameword[255];
    for (int i = 0; i < strlen(line)-1; i++) {
        gameword[i] = '_';
    }
    gameword[strlen(line)-1] = '\0';
    printf("%s\n",gameword);
    char letter[2];
    int miss = 0;
    const char russianAlphabet[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    char spaces[] = "                                  ";
    while (1) {
        printf("Попытки: %i/10\n%s\n%s\nВведите букву:", miss,russianAlphabet, spaces);
        fgets(letter, sizeof(letter), stdin);
        for (int i = 0; i < strlen(russianAlphabet); i++) {
            if (russianAlphabet[i] == letter[0])spaces[i] = '*';
        }
        system("cls");
        // Очищаем буфер ввода
        clearInputBuffer();
        printf("%s\n%s\n", gallows[miss],gameword);
        if (strchr(line, letter[0])) {
            for (int i = 0; i < strlen(line) - 1; i++) {
                printf("%i %i\n%c %c\n%s\n\n", line[i], letter[0], line[i], letter[0], gameword);
                if (line[i] == letter[0])gameword[i] = letter[0];
            }
        }
        else
        {
            miss++;
        }
        system("cls");
        printf("%s\n%s\n", gallows[miss], gameword);
        if (!(strchr(gameword, '_'))) {
            system("cls");
            printf("Вы победили!");
            break;
        }
        else if(miss == 10)
        {
            system("cls");
            printf("%s\nВы проиграли!", gallows[10]);
            break;
        }
    }
    fclose(file);
    return 0;
}
//пользователь вводит букву
//проверака
// Такой буквы нет
//чистим консоль
// отрисовываем висилицу и просим ввести букву