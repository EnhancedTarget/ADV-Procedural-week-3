#include <stdio.h>
#include <string.h>

#define STATES 5	//states
#define CAND 4		//candidates

//function definitions
void readVotes(int votes[][CAND]);
void printVotes(int votes[][CAND]);
void calculateVotes(int votes[][CAND]);
void displayMayor(int votesPerCandidate[CAND]);
void saveToFile(FILE* fp, int votes[][CAND]);

void main() {
	int tableOfVotes[STATES][CAND];

	FILE* fp = fopen("votes.txt", "w");
	if (fp == NULL) {
		printf("The file could not be opened.");
	}
	
	readVotes(tableOfVotes);
	printVotes(tableOfVotes);
	calculateVotes(tableOfVotes);

	//save results to file
	saveToFile(fp, tableOfVotes);
}

//reads the input for the votes
void readVotes(int votes[][CAND]) {
	for (int i = 0; i < STATES; i++) {
		for (int j = 0; j < CAND; j++) {
			printf("Please enter the votes for state %d and candidate %d:\n", (i + 1), (j + 1));
			scanf("%d", &votes[i][j]);
		}
	}
}

//prints the votes
void printVotes(int votes[][CAND]) {
	//Print first line to show candidate numbers
	char candidate[] = {'A', 'B', 'C', 'D'};
	printf("Candidate:");
	for (int x = 0; x < CAND; x++) {
		printf("\t|%c|", candidate[x]);
	}
	printf("\n\n");

	//prints the table of votes to the console
	for (int i = 0; i < STATES; i++) {	
		printf("State: %d|", (i + 1));

		for (int j = 0; j < CAND; j++) {
			printf("\t|%d| ", votes[i][j]);
		}
		printf("\n");
	}
}

//calculate the votes per candidate
void calculateVotes(int votes[][CAND]){
	//inintialize array with default value 0 on each index
	int votesPerCandidate[CAND];
	for(int candIndex = 0; candIndex < CAND; candIndex++){
		votesPerCandidate[candIndex] = 0;
	}

	//add votes per candidate to the votesPerCandidate variable based on the candidates index
	for (int stateIndex = 0; stateIndex < STATES; stateIndex++) {
		for (int candIndex = 0; candIndex < CAND; candIndex++) {
			votesPerCandidate[candIndex] = votes[stateIndex][candIndex] + votesPerCandidate[candIndex];
		}
	}

	displayMayor(votesPerCandidate);
}

//display the winner
void displayMayor(int votesPerCandidate[CAND]){
	int highestNumber = -1;
	int highestNumberIndex = -1;

	//calculates the highest number to find the winner
	for (int candIndex = 0; candIndex < CAND; candIndex++) {
		if(votesPerCandidate[candIndex] > highestNumber){
			highestNumber = votesPerCandidate[candIndex];
			highestNumberIndex = candIndex;
		}
	}

	//display Winner
	char candidate[] = {'A', 'B', 'C', 'D'};
	printf("\nCandidate %c has won the election with a total of %d votes and is now the new mayor!\n", candidate[highestNumberIndex], highestNumber);
}

//save the table to the file votes.txt
void saveToFile(FILE* fp, int votes[][CAND]){
	//Print first line to show candidate numbers
	char candidate[] = {'A', 'B', 'C', 'D'};
	fputs("Candidate:", fp);
	for (int x = 0; x < CAND; x++) {
		fprintf(fp, "\t|%c|", candidate[x]);
	}
	fputs("\n\n", fp);

	//prints the table of votes to the file
	for (int i = 0; i < STATES; i++) {
		fprintf(fp, "State: %d|", (i + 1));

		for (int j = 0; j < CAND; j++) {
			fprintf(fp, "\t|%d| ", votes[i][j]);
		}
		fputs("\n", fp);
	}
	fclose(fp);
}