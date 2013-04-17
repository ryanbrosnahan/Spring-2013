#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define numSmokers 6
#define numAgents 3
#define numPushers 3

sem_t agent;
sem_t pusher;
sem_t mutex;

// on the table
sem_t tobacco;
sem_t match;
sem_t paper;

// the items
sem_t tobaccosem;
sem_t matchsem;
sem_t papersem;

int isPaper = 0;
int isMatch = 0;
int isTobacco = 0;

pthread_t smokers[numSmokers];
pthread_t agents[numAgents];
pthread_t pushers[numPushers];


/*-----------------------------------SMOKERS--------------------------*/

// Smoker with paper
void* paperSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        printf("Smoker %d with paper waiting to smoke \n", *(int*)arg);

        // Waiting for the other items
        sem_wait(&papersem);

        // If you get them, smoke
        printf("Smoker %d with paper received other items. Now smoking... \n", *(int*)arg);
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker %d with paper done smoking \n", *(int*)arg);

        // Give back the Agent
        sem_post(&agent);
    }

    printf("Smoker %d has smoked 3 times and is leaving \n", *(int*)arg);

    return NULL;

}

// Smoker with tobacco
void* tobaccoSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        printf("Smoker %d with tobacco waiting to smoke \n", *(int*)arg);

        sem_wait(&tobaccosem);
        printf("Smoker %d with tobacco received other items. Now smoking... \n", *(int*)arg);
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker %d with tobacco done smoking \n", *(int*)arg);

        // Give back the Agent
        sem_post(&agent);
    }

    printf("Smoker %d has smoked 3 times and is leaving \n", *(int*)arg);

    return NULL;
}

// Smoker with match
void* matchSmoker(void* arg) {

    for(int i = 0; i < 4; ++i) {
        printf("Smoker %d with match waiting to smoke \n", *(int*)arg);

        sem_wait(&matchsem);
        printf("Smoker %d with match received other items. Now smoking... \n", *(int*)arg);
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        printf("Smoker %d with match done smoking \n", *(int*)arg);

        // Give back the Agent
        sem_post(&agent);
    }

    printf("Smoker %d has smoked 3 times and is leaving \n", *(int*)arg);

    return NULL;
}


/*-----------------------------------AGENTS--------------------------*/
void* paperTobaccoAgent(void* arg) {
    for(int i = 0; i < 13; ++i) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        sem_wait(&agent);
        sem_post(&tobacco);
        sem_post(&paper);
    }
}

void* matchPaperAgent(void* arg) {
    for(int i = 0; i < 13; ++i) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);

        sem_wait(&agent);
        sem_post(&match);
        sem_post(&paper);
    }
}

void* tobaccoMatchAgent(void* arg) {
    for(int i = 0; i < 13; ++i) {
        nanosleep((struct timespec[]){{0, rand() % 200000000}}, NULL);
        sem_wait(&agent);
        sem_post(&tobacco);
        sem_post(&match);
    }
}


/*-----------------------------------PUSHERS--------------------------*/

void* tobaccoPusher(void* arg) {
    for(int i = 0; i < 7; ++i) {
        sem_wait(&tobacco);
        sem_wait(&mutex);

        // if there is already paper on the table, let the match smoker wake
        if(isPaper) {
            isPaper = 0;
            sem_post(&matchsem);
        }
        // else if there is already matches on the table, let the paper smoker wake
        else if (isMatch) {
            isMatch = 0;
            sem_post(&papersem);
        }

        // otherwise this must be the first item on the table
        else
            isTobacco = 1;

        sem_post(&mutex);
    }
}

void* paperPusher(void* arg) {
    for(int i = 0; i < 7; ++i) {
        sem_wait(&paper);
        sem_wait(&mutex);

        if(isTobacco) {
            isTobacco = 0;
            sem_post(&matchsem);
        }

        else if (isMatch) {
            isMatch = 0;
            sem_post(&tobaccosem);
        }

        else
            isPaper = 1;

        sem_post(&mutex);
    }
}

void* matchPusher(void* arg) {
    for(int i = 0; i < 7; ++i) {
        sem_wait(&match);
        sem_wait(&mutex);

        if(isPaper) {
            isPaper = 0;
            sem_post(&tobaccosem);
        }

        else if (isTobacco) {
            isTobacco = 0;
            sem_post(&papersem);
        }

        else
            isMatch = 1;

        sem_post(&mutex);
    }
}

void initThreads() {

    // IDs for the smokers
    int smokerID[6];
    for(int i = 1; i <= 6; ++i) {
        smokerID[i] = i;
        printf("%d", *(int*)&smokerID[i]);
    }

    // Create threads of smokers
    if(pthread_create(&smokers[0], NULL, paperSmoker, &smokerID[0]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[1], NULL, paperSmoker, &smokerID[1]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[2], NULL, matchSmoker, &smokerID[2]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[3], NULL, matchSmoker, &smokerID[3]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[4], NULL, tobaccoSmoker, &smokerID[4]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&smokers[5], NULL, tobaccoSmoker, &smokerID[5]) == EAGAIN)
        perror("Insufficent resources to create thread\n");

    // IDs for the agents
    int agentID[3];
    for(int i = 1; i <= 3; ++i)
        agentID[i] = i;

    // Create threads of agents
    if(pthread_create(&agents[0], NULL, paperTobaccoAgent, &agentID[0]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&agents[1], NULL, matchPaperAgent, &agentID[1]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&agents[2], NULL, tobaccoMatchAgent, &agentID[2]) == EAGAIN)
        perror("Insufficent resources to create thread\n");

    // IDs for the pushers
    int pusherID[3];
    for(int i = 1; i <= 3; ++i)
        pusherID[i] = i;

    if(pthread_create(&agents[0], NULL, paperPusher, &pusherID[0]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&agents[1], NULL, matchPusher, &pusherID[1]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
    if(pthread_create(&agents[2], NULL, tobaccoPusher, &pusherID[2]) == EAGAIN)
        perror("Insufficent resources to create thread\n");
}

int main() {

    // Initialize the semaphores
    // agent
    sem_init(&agent, 0, 1);
    // smokers
    sem_init(&tobacco, 0, 0);
    sem_init(&match, 0, 0);
    sem_init(&paper, 0, 0);
    // pushers
    sem_init(&papersem, 0, 1);
    sem_init(&matchsem, 0, 1);
    sem_init(&tobaccosem, 0, 1);

    // Seeding the RNG for the agent
    srand(time(NULL));

    initThreads();


    for (int i = 0; i < 6; ++i)
        pthread_join(smokers[i], NULL);

    printf("All threads stopped, exit success\n");

}