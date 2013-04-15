#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define numSmokers 3

// Semaphores for the agent and the three items
sem_t agent;
sem_t tobacco;
sem_t match;
sem_t paper;

bool isTobacco;
bool isPaper;
bool isMatch;

void* paperSmoker(void* arg) {

    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with paper waiting to smoke\n");
    }

}

void* matchSmoker(void* arg) {

    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with match waiting to smoke\n");
    }

}

void* tobaccoSmoker(void* arg) {

    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with tobacco waiting to smoke\n");
    }

}

int main() {

    // Initialize the semaphores
    sem_init(&agent, 0, 1);
    sem_init(&tobacco, 0, 0);
    sem_init(&match, 0, 0);
    sem_init(&paper, 0, 0);

    // Seeding the RNG for the agent
    srand(time(NULL));

    // Create threads of smokers
    pthread_t smokers[numSmokers];
    pthread_create(&smokers[0], NULL, paperSmoker, NULL);
    pthread_create(&smokers[0], NULL, matchSmoker, NULL);
    pthread_create(&smokers[0], NULL, tobaccoSmoker, NULL);


    // The "Agent"
    while(1) {
        sem_wait(&agent);

        // Randomly generate 2 items
        int combination = rand() % 3;
        if (combination == 0) {
            isMatch = 1;
            isPaper = 1;
        }
        else if(combination == 1) {
            isMatch = 1;
            isTobacco = 1;
        }
        else {
            isTobacco = 1;
            isPaper = 1;
        }

        break;
    }

}