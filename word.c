#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *WordSelect(int difficult) {
  FILE *words = NULL; //текстовый файл

  switch (difficult) //уровень сложности
  {
    /*код выполнится, если difficult будет равен 0*/
  case 0:
    words = fopen("./iwi/words/just.txt", "r"); //открытие текстового файла
                                                /*
                                                Оператор break используется для того, чтобы прерывать ход программы в
                                                операторе switch и передавать управление следующему оператору, после switch
                                                */
    break;
  case 1:
    words = fopen("./iwi/words/easy.txt", "r");
    break;
  case 2:
    words = fopen("./iwi/words/medium.txt", "r");
    break;
  case 3:
    words = fopen("./iwi/words/hard.txt", "r");
    break;
  }
  if (words == NULL) {
    printf("Words database not found.\n");
    return 0;
  }

  /*
    words_amount: кол-во слов
    word_length: длина слова
    */
  int words_amount = 0, word_length = 0;
  char ch;

  while (ch != EOF) {
    ch = fgetc(words);
    /* fgetc – чтение одного байта из указанного потока данных */
    if (ch != '\n')
      word_length++;
    if (ch == '\n')
      words_amount++;
  }
  fseek(words, 0, SEEK_SET);
  /*
    fseek– установка позиции в потоке данных
    words: указатель на управляющую таблицу потока данных
    0:  смещение позиции
    SEEK_SET: точка отсчета смещения (Начало файла)
  */
  word_length /= words_amount;
  /* /= Деление, совмещённое с присваиванием */

  srand(time(NULL));
  /* srand(time(NULL)) устанавливает в качестве базы текущее время */
  int new_wordNum = rand() % words_amount;
  /*
    генерации псевдослучайных чисел используется функция rand(); %-остаток от
    деления
  */

  char *new_word;
  new_word = (char *)malloc(word_length * sizeof(char));
  /* выделение динамической памяти; malloc() распред-ет байты размера и
        возвращает указатель на выделенную память */

  int i = 0;
  while (i != new_wordNum) {
    ch = fgetc(words);
    if (ch == '\n')
      i++;
  }

  for (i = 0; i < word_length; i++)
    new_word[i] = fgetc(words);

  return new_word;
}
