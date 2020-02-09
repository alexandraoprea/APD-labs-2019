#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @author cristian.chilipirea
 *
 * Create files using
 * dd if=/dev/urandom of=1.txt bs=1024 count=104800
 * dd if=/dev/urandom of=2.txt bs=1024 count=104800
 */
int N;
int P;
int NReps;
char* buff1;
char* buff2;
int* threadIds;
pthread_t* threads;

void getArgs(int argc, char** argv)
{
    if (argc < 4)
    {
        printf("Not enough paramters: ./program N NReps P\n");
        exit(1);
    }

    N       = atoi(argv[1]);
    NReps   = atoi(argv[2]);
    P       = atoi(argv[3]);
}

void finalise()
{
    if (buff1 != NULL)
    {
        free(buff1);
    }

    if (buff2 != NULL)
    {
        free(buff2);
    }

    if (threads != NULL)
    {
        free(threads);
    }

    if (threadIds != NULL)
    {
        free(threadIds);
    }
}

void init()
{
    int i;

    buff1 = malloc(N * sizeof(*buff1));
    if (buff1 == NULL)
    {
        printf("Malloc failed for the buffer.");
        exit(1);
    }

    buff2 = malloc(N * sizeof(*buff2));
    if (buff2 == NULL)
    {
        printf("Malloc failed for the buffer.");
        finalise();
        exit(1);
    }

    threads = malloc(P * sizeof(*threads));
    if (threads == NULL)
    {
        printf("Malloc failed for threads.\n");
        finalise();
        exit(1);
    }

    threadIds = malloc(P * sizeof(*threadIds));
    if (threadIds == NULL)
    {
        printf("Malloc failed for thread ids.\n");
        finalise();
        exit(1);
    }
}

void* parReadFiles(void* arg)
{
    int i;
    FILE *in;

    int tid = *(int*)arg;

    if (tid == 0)
    {
        in = fopen("1.txt", "rb");

        for (i = 0; i != NReps; ++i)
        {
            fread(buff1, sizeof(*buff1), N, in);
            fseek(in, 0, SEEK_SET);
        }

        if (P == 1)
        {
            FILE* in2 = fopen("2.txt", "rb");

            for (i = 0; i != NReps; ++i)
            {
                fread(buff2, sizeof(*buff2), N, in2);
                fseek(in, 0, SEEK_SET);
            }
        }
    } else
    {
        in = fopen("2.txt", "rb");

        for (i = 0; i != NReps; ++i)
        {
            fread(buff2, sizeof(*buff1), N, in);
            fseek(in, 0, SEEK_SET);
        }
    }
}

int main(int argc, char** argv)
{
    int i;

    getArgs(argc, argv);
    init();

    for (i = 0; i != P; ++i)
    {
        threadIds[i] = i;

        pthread_create(threads + i, NULL, parReadFiles, threadIds + i);
    }

    for (i = 0; i != P; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    finalise();
    
    return 0;
}
