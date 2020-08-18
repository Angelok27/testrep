#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "hangman.h"
#include "interface.h"
#include "game.h"

int difficult = 0;

/*
  * ф-ия: difficultSet (Выбор сложности)
  *
  * GtkToggleButton *button:  GtkButton запоминает состояние при нажатии
  *
*/
void difficultSet(GtkToggleButton *button)
{
    if (gtk_toggle_button_get_active(button))
    /*Запрашивает GtkToggleButton и возвращает его текущее состояние.
     Возвращает TRUE, если кнопка переключения нажата, и FALSE, если она
     поднята.*/

    {
        const char *difficult_game = gtk_button_get_label(GTK_BUTTON(button));
        /*Извлекает текст из метки кнопки*/

        if (!strcmp(difficult_game, "Just"))
        /*strcmp() сравнение строк; difficult_game, "just" - сравниваемые строки*/
            difficult = 0;
        else if (!strcmp(difficult_game, "Easy"))
            difficult = 1;
        else if (!strcmp(difficult_game, "Medium"))
            difficult = 2;
        else if (!strcmp(difficult_game, "Hard"))
            difficult = 3;
    }
}

/*
  *ф-ия: начало игры
*/
void startGame()
{
    int i;
    err_amount = 0;
    gtk_image_set_from_file(Image, "./iwi/image/0.jpg");
    gtk_widget_hide(general_windows); /*заставляет скрыть виджет(невид-ый для
    пользователя)*/
    gtk_widget_hide(mess_windows);
    gtk_widget_show_all(GTK_WIDGET(keyboard_Gr));

    if (!(word_game = WordSelect(difficult)))
        return;
    printf("Word: %s\n", word_game);

    for (word_size = 0; word_game[word_size] != '\0'; word_size++);

    hiddenWord = (char*)malloc(word_size*sizeof(char));
    for (i = 0; i < word_size; i++)
        hiddenWord[i] = '-';
    hiddenWord[i] = '\0';

    gtk_label_set_text(Hidden_Wor_Lab, hiddenWord);
    gtk_widget_show(level_windows);
}

/*
  *ф-ия: играть заново
*/
void replayGame()
{

    gtk_widget_hide(level_windows);
    gtk_widget_hide(mess_windows);
    gtk_widget_show(general_windows);
}
