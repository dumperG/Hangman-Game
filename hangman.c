#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int running = 1;
const int max_strikes = 6;
char* word;

// print the current state of the hangman
void print_hangman(int num_strikes) {
     switch (num_strikes) {
          case 0: // empty body
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |        \n");
               printf("   |        \n");
               printf("   |        \n");
               printf("-------     \n");
               break;
          case 1: // head
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |        \n");
               printf("   |        \n");
               printf("-------     \n");
               break;
          case 2: // body
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |    |   \n");
               printf("   |        \n");
               printf("-------     \n");
               break;
          case 3: // left arm
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |   /|   \n");
               printf("   |        \n");
               printf("-------     \n");
               break;
          case 4: // right arm
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |   /|\\ \n");
               printf("   |        \n");
               printf("-------     \n");
               break;
          case 5: // left leg
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |   /|\\ \n");
               printf("   |   /    \n");
               printf("-------     \n");
               break;
          case 6: // right leg
               printf("   YOU LOSE! \n");
               printf("   ------   \n");
               printf("   |    |   \n");
               printf("   |    O   \n");
               printf("   |   /|\\ \n");
               printf("   |   / \\ \n");
               printf("-------     \n");
               break;
     }
}


// gets a random word from words.txt
char* get_word() {
     FILE* fp = fopen("words.txt", "r");
     if(fp == NULL) {
          printf("Failed to open words.txt\n");
          exit(EXIT_FAILURE);
     }
     
     char line[50];
     int line_count = 0;
     int line_num = 0;
     
     while(fgets(line, sizeof(line), fp) != NULL) {
          line_count++;
          if(line_count == rand() % line_count + 1) {
               line_num = line_count - 1;
          }
     }
     
     rewind(fp);
     for(int i = 1; i < line_num; i++) {
          fgets(line, sizeof(line), fp);
     }
     
     word = strdup(line);
     word[strlen(word) - 1] = '\0'; // remove the newline character
     
     fclose(fp);

     return word;

}

int main() {
     int curr_strikes = 0;
     word = get_word();
     printf("%s", word);
     while(running) {
          print_hangman(curr_strikes);
          if(curr_strikes >= max_strikes) {
               running = 0;
               break;
          }
          
          printf("Enter a letter: ");
          char* guess;
          scanf("%s", &guess);
          
          if(strchr(word, guess) == NULL) {
               printf("%c is not in the word.\n", guess);
               curr_strikes++;
          } else {
               printf("%c is in the word.\n", guess);
          }   
     }
     
     printf("Thanks for playing!\n");
     return EXIT_SUCCESS;
}