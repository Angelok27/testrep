#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include "game.h"

/*
  * ф-ия: выбора слова
  *
  * difficult: сложность игры
  *
  * return: новое загадываемое слово
  *
*/
char *WordSelect(int difficult)
{
    FILE *words = NULL;
    char path_word[260], difficult_game[10];
    /* сожность*/
    switch (difficult)
    /*Оператор switch сравнивает значение одной переменной с несколькими
    константами*/
    {
        case 0: /*код выполнится, если difficult будет равен 0*/

            sprintf(difficult_game, "just");
            /*Функция sprintf() идентична printf(), а исключением того, что
            вывод производится в массив*/

            break; /*Оператор break используется для того, чтобы прерывать ход
            программы в операторе switch и передавать управление следующему
            оператору, после switch*/

        case 1:
            sprintf(difficult_game, "easy");
            break;
        case 2:
            sprintf(difficult_game, "medium");
            break;
        case 3:
            sprintf(difficult_game, "hard");
            break;
    }
    /*вывод записывается в массив path_word*/
    sprintf(path_word, "./iwi/words/%s.txt", difficult_game);
    words = fopen(path_word, "r");
    if (words == NULL)
    {
        printf("Words database \"%s\" not found.\n", path_word);
        GtkWidget *errWordsMsg = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Error");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(errWordsMsg), "Words database \"%s\" not found.\n", path_word);
        gtk_dialog_run(GTK_DIALOG(errWordsMsg));
        gtk_main_quit();
        return NULL;
    }
    /*кол-во слов, длина слова*/
    int words_amount = 0, word_length = 0;
    char str[10];/*массив куда будет записываться загадываемое слово*/

    /* пока не достигнут конец файла*/
    while (!feof(words))
    {
        fgets(str, 10, words);
/*чтение строки из потока данных(words), str - массив в который будет помещена
считанная строка, 10 - максимально допустимая длина считываемой строки*/
        words_amount++;
    }

    srand(time(NULL));
    /*srand(time(NULL)) устанавливает в качестве базы текущее время*/
    int new_wordNum = rand() % words_amount;// рандомно выбираем новое слово
    /*генерации псевдослучайных чисел используется функция rand();
     %-остаток от деления*/

    fseek(words, 0, SEEK_SET);
    /*изменить позицию на 0 байт относительно начала файла(SEEK_SET)*/

    int i = 0;
    while (i != new_wordNum)
    {
        fgets(str, 10, words);
        i++;
    }

    word_length = strlen(str) - 1;
    /*strlen – определение длины строки; str – указатель на строку.
    Функция strlen вычисляет количество символов в строке до первого вхождения
    символа конца строки. При этом символ конца строки не входит в подсчитанное
    количество символов.*/

    char *new_word;
    new_word = (char*)malloc(word_length*sizeof(char));
    /*выделение динамической памяти; malloc() распред-ет байты размера и
    возвращает указатель на выделенную память*/

    for (i = 0; i < word_length; i++)
        new_word[i] = str[i];
    new_word[i] = '\0';//конец строки

    fclose(words);

    return new_word;
}
