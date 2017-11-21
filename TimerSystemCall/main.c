#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int printCounter = 0;

void printHello() {

     printCounter++;
     printf("Hello world! printed: %d times \n", printCounter );
     alarm(1);
     signal(SIGALRM, printHello); // Same here, call function again

}

int main(int argc, char *argv[]){


    signal(SIGALRM, printHello); // Make function call signal

    alarm(1); // set alarm to 1s

    while (1) { // An infinite loop so OS has enough time to respond on signal request
    }


    return 0;
}
