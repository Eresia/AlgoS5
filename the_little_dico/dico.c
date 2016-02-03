#include "dico.h"

Dictionary createDictionary(){
    return NULL;
}

Dictionary addWord(Dictionary dictionary, Word word){
    en_minus(word);
    Dictionary node = NULL;

    if (dictionary == NULL) {
        dictionary = makeLetters(word);
    } else if (dictionary->car == word[0]) {
        #ifdef DEBUG
        printf("Lettre déjà existante: %c\n", word[0]);
        #endif
        dictionary->leftChild = addWord(dictionary->leftChild, word+1);
    } else if (dictionary->car < word[0]) {
        dictionary->rightBrother = addWord(dictionary->rightBrother, word);
    } else {
        node = makeLetters(word);
        node->rightBrother = dictionary;
        dictionary = node;
    }

    return dictionary;
}

Dictionary deleteWord(Dictionary dictionary, Word word){
    if(!insideDictionary(dictionary, word)){
        return dictionary;
    }
    en_minus(word);
    Dictionary node = NULL;

    if (dictionary == NULL) {
        dictionary = NULL;
    } else if (dictionary->car == word[0]) {
        dictionary->leftChild = deleteWord(dictionary->leftChild, word+1);
        if (dictionary->leftChild == NULL) {
            node = dictionary;
            dictionary = dictionary->rightBrother;
            free(node);
        }
    } else if (dictionary->car < word[0]) {
        dictionary->rightBrother = deleteWord(dictionary->rightBrother, word);
    } else {
        // Do nothing, word is not in dictionary
    }
    return dictionary;
}

Boolean insideDictionary(Dictionary dictionary, Word word){
    en_minus(word);
    if (dictionary == NULL) {
        return word[0] == '\0';
    } else if (dictionary->car == word[0]) {
        return insideDictionary(dictionary->leftChild, word+1);
    } else if (dictionary->car < word[0]) {
        return insideDictionary(dictionary->rightBrother, word);
    } else {
        return 0;
    }
}

Dictionary freeDictionary(Dictionary dico){
    if(dico != NULL){
        freeDictionary(dico->leftChild);
        freeDictionary(dico->rightBrother);
        free(dico);
    }
    return NULL;
}

Boolean emptyDictionary(Dictionary dictionary){
    return dictionary == NULL;
}

Dictionary makeLetters(Word word){
    Dictionary node = malloc(sizeof(struct node));
    if (word[0] == '\0') {
        #ifdef DEBUG
        printf("Fin du mot ajouté \n");
        #endif
        node->car = '\0';
        node->leftChild = NULL;
        node->rightBrother = NULL;
    } else {
        #ifdef DEBUG
        printf("Lettre ajouté : %c\n", word[0]);
        #endif
        node->car = word[0];
        node->leftChild = makeLetters(word+1);
        node->rightBrother = NULL;
    }

    return node;
}

char* displayDictionary(Dictionary dictionary){
    Word word = malloc(WORD_LENGTH_MAX * sizeof(char));
    char* display = malloc(WORD_MAX * WORD_LENGTH_MAX * sizeof(char));
    displaySubDictionary(dictionary, word, 0, display);
    return display;
}

void displaySubDictionary(Dictionary dictionary, Word word, int offset, char* display){
    //printf("%s\n", word);
    if (dictionary == NULL) {
        return;
    } else if(dictionary->car == '\0') {
        word[offset] = '\0';
        display = strcat(display, word);
        display = strcat(display, "\n");
        displaySubDictionary(dictionary->rightBrother, word, offset, display);
        return;
    } else {
        word[offset] = dictionary->car;
        displaySubDictionary(dictionary->leftChild, word, offset+1, display);
        displaySubDictionary(dictionary->rightBrother, word, offset, display);
        return;
    }
}

int saveDictionary(Dictionary dictionary, char* fileName){
    FILE* file = fopen(fileName, "w");

    if(file == NULL){
        return FILE_DONT_OPEN;
    }

    fputs(displayDictionary(dictionary), file);

    fclose(file);
    return 0;
}

Dictionary loadDictionary(Dictionary dictionary, char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        return NULL;
    }

    Word word = malloc(WORD_LENGTH_MAX * sizeof(char));
    memset(word, '\0', WORD_LENGTH_MAX);
    int position = 0;

    char c = fgetc(file);

    while(!feof(file)){
        if(c == '\n'){
            dictionary = addWord(dictionary, word);
            memset(word, '\0', position);
            position = 0;
        } else{
            word[position] = c;
            position++;
        }
        c = fgetc(file);
    }

    dictionary = addWord(dictionary, word);

    fclose(file);

    return dictionary;
}

int numberOfWords(Dictionary dictionary){
    if (dictionary == NULL) {
        return 0;
    } else if (dictionary->car == '\0') {
        return 1 + numberOfWords(dictionary->rightBrother);
    } else {
        return numberOfWords(dictionary->leftChild) + numberOfWords(dictionary->rightBrother);
    }
}

void en_minus(Word string){
    int i;
    for(i = 0; i < strlen(string); i++){
        string[i] = tolower(string[i]);
    }
}
