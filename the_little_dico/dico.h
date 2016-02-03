#ifndef DICO
  #define DICO
  #define WORD_MAX 100
  #define WORD_LENGTH_MAX 30

  /*Errors :
    1 : Bad argument
    2 : Bad argument
    3 : Problem with file
  */

  #define NOT_ENOUGH_ARGUMENT 1
  #define BAD_ARGUMENT 2
  #define FILE_DONT_OPEN 3

  #define Boolean int
  #define Word char*

  #include <stdlib.h>
  #include <stdio.h>
  #include <string.h>
  #include <ctype.h>

  typedef struct node{
          char car;
          struct node *leftChild, *rightBrother;
  }* Dictionary;

  //public
  Dictionary createDictionary();
  Dictionary addWord(Dictionary, Word);
  Dictionary deleteWord(Dictionary, Word);
  Boolean insideDictionary(Dictionary, Word);
  Boolean emptyDictionary(Dictionary);
  Dictionary freeDictionary(Dictionary);
  char* displayDictionary(Dictionary);
  int saveDictionary(Dictionary , char*);
  Dictionary loadDictionary(Dictionary, char*);
  int numberOfWords(Dictionary);

  void en_minus(char*);

  //private
  Dictionary makeLetters(Word word);
  void displaySubDictionary(Dictionary dictionary, Word word, int offset, char*);
#endif
