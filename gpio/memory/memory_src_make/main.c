#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <gpiod.h>
#define NUM_OF_LEDS 4
#ifndef MEMORY_H
#define MEMORY_H
int buttonPress(int* output, int number);
void light_led(int number);
#endif
int main(int argc, char ** argv) {
	time_t previous = time(NULL) * 1000;
	int * password;
	int * try;
	int tries = 0;
	int length;
	bool guessed = false;
	printf("Hi, this is a house lock app\n");
	printf("Button 12 is 1, button 13 is 2, button 14 is 3 and button 15 is 4\n");
	printf("Please input the length of your passcode from 1 to 4\n");
	buttonPress(&length, 1);
	printf("The length of your password is %d\n\n", length);
	password = malloc(length*(sizeof(int)));
	try = malloc(length*(sizeof(int)));
	printf("Saving...\n");
	sleep(1);
	printf("Saved!...\n");
	printf("Please input your password\n");
	printf("Button 12 is 1, button 13 is 2, button 14 is 3 and button 15 is 4\n");
	buttonPress(password, length);
	printf("Your password is \n");
	for(int i = 0; i < length; ++i) {
		printf("%d ", password[i]);
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("THE SAFE IS LOCKED\n");
	printf("Please enter the code now\n");
	while(guessed == false && tries < 3) {
		guessed = true;
		light_led(3 - tries);
		buttonPress(try, length);
		for(int i = 0; i < length; ++i) {
			if(password[i] != try[i]){
				guessed = false;
				++tries;
				printf("Bad luck, try again (%d tries left)\n", 3 - tries);
				break;
			}
		}
		if(tries == 3) {
			while(true) {
				printf("YOU'RE A THIEF, I'M CALLING THE POLICE!\n");
				light_led(4);
				sleep(0.4);
				light_led(0);
				sleep(0.4);
			}
		}
		
	}
	printf("Congratulations, you've guessed the password!\n");
	light_led(0);

}
