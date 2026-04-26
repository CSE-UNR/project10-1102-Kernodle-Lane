//Author: Lane Kernodle
//Purpose: Final Project - Wordle style game

#include<stdio.h>
#define STRCAP 50
#define WRD_LGTH 5
#define NUM_GUESS 6
#define WORDS 10

void loadWord(char word[STRCAP]);
void toLowCas(char guess[STRCAP]);
void getGuess(int tryCtr, char guess[STRCAP]);
void evalGuess(char guess[STRCAP], char word[STRCAP], char evaluation[STRCAP]);
void trackPrnt(int tryCtr, char tracker[][STRCAP], char guess[STRCAP], char evaluation[STRCAP]);
int rounds(char guess[STRCAP], char word[STRCAP], char evaluation[STRCAP], int tryCtr);

int main(){
	
	char word[STRCAP], guess[STRCAP], evaluation[STRCAP], tracker[NUM_GUESS*2][STRCAP];
	int tryCtr=0, solved=0;
	
	loadWord(word);
	
	while(solved==0 && tryCtr < NUM_GUESS){
		solved = rounds(guess, word, evaluation, tryCtr);
		trackPrnt(tryCtr, tracker, guess, evaluation);
		tryCtr++;
	}
	if(solved==1){
		printf("================================\n");
		printf("             %s\n", guess);
		printf("      You won in  %d guesses!\n", tryCtr);
		printf("            Amazing!\n");
	}
	else{
		printf("You lost, better luck next time!\n");
	}
	
	return 0;
}

void loadWord(char word[STRCAP]){
	char arr[WORDS][STRCAP], dmp;
	int number=0;
	FILE* wordPtr;
	
	wordPtr = fopen("words.txt", "r");
	if(wordPtr==NULL){
		printf("Could not open file.\n");
	}
	for(int i=0;i<WORDS;i++){
		fgets(arr[i], STRCAP, wordPtr);
	}
	fclose(wordPtr);
	printf("Please choose a number between 0-%d: ", WORDS-1);
	scanf(" %d%c", &number, &dmp);
	for(int i=0; arr[number][i]!='\0';i++){
		word[i] = arr[number][i];
	}
}

void toLowCas(char guess[STRCAP]){
	for(int i=0; guess[i]!='\0'; i++){
		if(guess[i]<91 && guess[i]>64){
			guess[i] += 32;
		}
	}
}

void getGuess(int tryCtr, char guess[STRCAP]){
	int i, length, badChar;
	do{
		badChar=0;
		
		if(tryCtr==NUM_GUESS-1){
			printf("FINAL GUESS : ");
		}
		else{
			printf("GUESS %d! Enter your guess: ", tryCtr+1);
		}
		
		fgets(guess, STRCAP, stdin);
		toLowCas(guess);
		
		length=0;
		for(i=0; guess[i]!='\0' && guess[i]!='\n'; i++){
			length++;
			if((guess[i] < 'a' || guess[i] > 'z') && (guess[i] < 'A' || guess[i] > 'Z')){
				badChar=1;
			}
		}
		if(badChar==1){
			printf("Your guess must contain only letters.\n");
		}
		if(length!=WRD_LGTH){
			printf("Your guess must be 5 letters long.\n");
		}
	}while(length != WRD_LGTH || badChar==1);
}

void evalGuess(char guess[STRCAP], char word[STRCAP], char evaluation[STRCAP]){
	
	int i=0;
	for(i=0; guess[i]!='\0'; i++){
		if(guess[i]==word[i]){
			guess[i] -= 32;
			evaluation[i] = ' ';
		}
		else{
			evaluation[i] = '1';
		}		
	}
	evaluation[i-1]='\0';
	guess[i-1]='\0';
	word[i-1]='\0';
	for(i=0; guess[i]!='\0'; i++){
		if(evaluation[i]=='1'){
			for(int j=0; word[j]!='\0'; j++){
				if(evaluation[j]=='1' && guess[i]==word[j]){
					evaluation[i] = '^';
					break;
				}
			}
		}
	}
	for(i=0; evaluation[i]!='\0'; i++){
		if(evaluation[i]=='1'){
			evaluation[i]=' ';
		}
	}
}

void trackPrnt(int tryCtr, char tracker[][STRCAP], char guess[STRCAP], char evaluation[STRCAP]){
	int i=0;
	for(i=0; guess[i]!='\0'; i++){
		tracker[tryCtr*2][i] = guess[i];
		tracker[(tryCtr*2)+1][i] = evaluation[i];
	}
	tracker[tryCtr*2][i] = '\0';
	tracker[(tryCtr*2)+1][i] = '\0';
	
	printf("================================\n");
	for(i=0; i<=(tryCtr*2)+1; i++){
		printf("%s\n", tracker[i]);
	}
}

int rounds(char guess[STRCAP], char word[STRCAP], char evaluation[STRCAP], int tryCtr){
	int solved=1;
	getGuess(tryCtr, guess);
	evalGuess(guess, word, evaluation);
	for (int i=0; word[i]!='\0'; i++){
		if(word[i] != guess[i]+32){
			solved = 0;
		}
	}
	return solved;
}
