/* Mastermind Game by Pailin Mack (pmack) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 25 	// Max element for user's input
#define MAX 4		// Max element of array in game

/* Prototype functions*/
int *gen_key();
char validate(char *user_input);
char check_key(char *secret, char *guess);
void sum_time(double valid_time);
int *gen_guess();

/* Main Function */
int main(int argc, char *argv[])
{
	// Variables declaration:
	char input[LIMIT];
	int *key;
	char code[MAX] = {0};
	int i, j;
	int valid_ctr = 0;

	// Generate key for the game:
	key = gen_key();

	// Convert int array to char array:
	for (i = 0; i < MAX; i++) {
		j += sprintf(&code[i], "%d", key[i]);
	}

	// Optional: Print cheat for validation testing
	// printf("Cheat: %s\n", code);

	// Command Line Argument:
	if (argc >= 3) {
		printf("Error: Only accept 'autoplay' as CLA\n");
	} else if (argc == 2) {
		if (strcmp(argv[1], "autoplay") == 0) {
			while (1) {
				// Prompt computer for guess:
				printf("Guess a number: ");
				int *r_input = gen_guess();

				for (i = 0; i < MAX; i++) {
					j += sprintf(&input[i], "%d", 
					r_input[i]);
				}
				
				printf("%s\n", input);

				/* Validate user's input:
					All 4 digits must be valid */
				if (validate(input) == MAX) {
					valid_ctr++;

					// Check valid guess with random key:
					if (check_key(code, input) == 1) {
						printf("You win! ");
						printf("It took you ");
						printf("%d guesses.\n", 
						valid_ctr);
						
						break;
					}
				}
			}
		} else {
			printf("Error: Only accept 'autoplay' as CLA\n");
		}
	} else if (argc == 1) {
		// Time variables:
		double time;
		double sum[10] = {0.0};
		double avg;

		while (1) {
			// Time start:
			clock_t begin = clock();

			// Prompt user for guess:
			printf("Guess a number: ");
			fgets(input, LIMIT, stdin);
			input[strlen(input) - 1] = '\0';

			// Time stop:
			clock_t end = clock();

			/* Validate user's input:
				All 4 digits must be valid */
			if (validate(input) == MAX) {
				valid_ctr++;

				// Calculate only valid time:
				time = (double)(end - begin)
					     * 100000 / CLOCKS_PER_SEC;
								
				// Calculate sum of total time:
				for (i = 0; i < valid_ctr; i++) {
					
					sum[i] += time;
				}
				
				// Check valid guess with random key:
				if (check_key(code, input) == 1) {
					printf("You win! It took you ");
					printf("%d guesses.\n", valid_ctr);
					
					double ctr = (double)(valid_ctr);
					avg = *sum / ctr;
					printf("Average time: %.2f", avg);
					printf("\n");

					break;
				}
			}
		}
	}

	return 0;
}

/*Generate 4 random digits:
  Additional feat - Repeated digits */

int *gen_key()
{
	static int key[MAX];
	int min = 1;
	int max = 6;
	int i;

	srand((unsigned)time(NULL));

	for (i = 0; i < MAX; i++) {
		key[i] = (rand()%(max - min + 1)) + min;
	}

	return key;
}

/*Generate 4 random digits:
  Additional feat - autoplay */
int *gen_guess()
{
	static int r_guess[MAX];
	int min = 1;
	int max = 6;
	int i;

	for (i = 0; i < MAX; i++) {
		r_guess[i] = (rand()%(max - min + 1)) + min;
	}

	return r_guess;
}

/*Validate user's input:
 1. Input must be 4 characters
 2. Input must be all integers 
 3. Input must be 1-6*/
char validate(char *user_input)
{
	char *str;		// Hold string from strtol()
	char valid = 0;		// Set valid to '0' = false
	int i;
	
	strtol(user_input, &str, 10);

	if (str == user_input || *str != '\0') {
		printf("Invalid: Please enter 4 digits between 1 and 6\n");
	} else if (strlen(user_input) > 4 || strlen(user_input) < 4) {
		printf("Invalid: Please enter 4 digits between 1 and 6\n");
	} else {
		for (i = 0; i < MAX; i++) {
			if (user_input[i] <= '0' || user_input[i] >= '7') {
				printf("Invalid: All 4 digits ");
				printf("must be between 1 and 6\n");
				break;
			} else {
				valid++;	// Increment if true
			}
		}
	}

	return valid;
}

/* Check valid guess:
 1. Red: Correct number and position
 2. White: Correct number, but not position */

/*Cited code:
Title: A simple Mastermind game in C
Author: user302686
Date: 2016
Code version: Unknown
Availability: https://codereview.stackexchange.com
*/

char check_key(char *secret, char *guess)
{
	int i, j;
	int red = 0;
	int white = 0;
	char status = 0;		   // Set to 1, if red = 4
	int check_s[MAX] = {1, 1, 1, 1};   // Check index status for key
	int check_g[MAX] = {1, 1, 1, 1};   // Check index status for guess

	// Red checker:
	for (i = 0; i < MAX; i++) {
		if (guess[i] == secret[i]) {
			red++;
			check_s[i] = check_g[i] = 0;
		}
	}

	// White checker:
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (guess[j] == secret[i] && check_g[i] 
			&& check_s[j] && i != j) {
				white++;
				check_g[i] = check_s[j] = 0;
			}
		}
	}

	// Print:	
	if (red > 0 && white > 0) {
		printf("%d red, %d white\n", red, white);
	} else if (red > 0 && white == 0) {
		printf("%d red\n", red);
	} else if (white > 0 && red == 0) {
		printf("%d white\n", white);
	} else if (white == 0 && red == 0) {
		printf("No matches\n");
	}
	
	// Status:
	if (red == MAX) {
		status = 1;
	}

	return status;
}