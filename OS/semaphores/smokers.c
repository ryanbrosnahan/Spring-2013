#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define numSmokers 6

// Semaphores for the agent and the three items
sem_t agent;
sem_t tobaccoMatch;
sem_t matchPaper;
sem_t paperTobacco;

// Smoker with paper
void* paperSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        puts("Smoker with paper waiting to smoke");

        // Waiting for the other items
        sem_wait(&tobaccoMatch);

        // If you get them, smoke
        puts("Smoker with paper received other items. Now smoking...");
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        puts("Smoker with paper done smoking");

        // Give back the Agent
        sem_post(&agent);
    }

    return NULL;

}

// Smoker with tobacco
void* tobaccoSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        puts("Smoker with tobacco waiting to smoke");

        sem_wait(&matchPaper);
        puts("Smoker with tobacco received other items. Now smoking...");
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        puts("Smoker with tobacco done smoking");

        // Give back the Agent
        sem_post(&agent);
    }
    return NULL;
}

// Smoker with match
void* matchSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        puts("Smoker with match waiting to smoke");

        sem_wait(&paperTobacco);
        puts("Smoker with match received other items. Now smoking...");
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        puts("Smoker with match done smoking");

        // Give back the Agent
        sem_post(&agent);
    }
    return NULL;

}

int main() {

    // Initialize the semaphores
    sem_init(&agent, 0, 1);
    sem_init(&tobaccoMatch, 0, 0);
    sem_init(&matchPaper, 0, 0);
    sem_init(&paperTobacco, 0, 0);

    // Seeding the RNG for the agent
    srand(time(NULL));

    // Create threads of smokers
    pthread_t smokers[numSmokers];
    if(pthread_create(&smokers[0], NULL, paperSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[1], NULL, paperSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[2], NULL, matchSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[3], NULL, matchSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[4], NULL, tobaccoSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[5], NULL, tobaccoSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");

    // The "Agent" will run an arbitrary 20 times before exiting. This could be
    // an infinite loop.
    while(1) {
        sem_wait(&agent);

        // Randomly generate 2 items
        int combination = rand() % 3;

        if (combination == 0)
            sem_post(&tobaccoMatch);

        else if(combination == 1)
            sem_post(&matchPaper);

        else
            sem_post(&paperTobacco);

    }

    for (int i = 0; i < numSmokers; ++i)
        pthread_join(smokers[i], NULL);

    printf("All threads stopped, exit success\n");

}