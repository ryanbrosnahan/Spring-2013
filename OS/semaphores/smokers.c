#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define numSmokers 3

// Semaphores for the agent and the three items
sem_t agent;
sem_t tobaccoMatch;
sem_t matchPaper;
sem_t paperTobacco;

// Smoker with paper
void* paperSmoker(void* arg) {
printf("Smoker with paper waiting to smoke\n");
    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with paper waiting to smoke\n");

        sem_wait(&tobaccoMatch);
        printf("Smoker with paper received other items. Now smoking... \n");

        sem_post(&agent);

    }

    return NULL;

}

// Smoker with tobacco
void* tobaccoSmoker(void* arg) {

    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with tobacco waiting to smoke\n");

        sem_wait(&matchPaper);
        printf("Smoker with tobacco received other items. Now smoking... \n");

        sem_post(&agent);
    }
    return NULL;
}

// Smoker with match
void* matchSmoker(void* arg) {

    while(1) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker with match waiting to smoke\n");

        sem_wait(&paperTobacco);
        printf("Smoker with match received other items. Now smoking... \n");

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

    if(pthread_create(&smokers[1], NULL, matchSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");

    if(pthread_create(&smokers[2], NULL, tobaccoSmoker, NULL) == EAGAIN)
        perror("Insufficent resources to create thread\n");


    // The "Agent"
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



        break;
    }

    for (int i = 0; i < numSmokers; ++i)
        pthread_join(smokers[i], NULL);

    printf("All threads stopped, exit success\n");

}