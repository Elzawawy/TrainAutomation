/*
 * Main File Runner Code.
 * 
 * Author : Amr Elzawawy
 * Date : 6 December 2018
 */
#include <pthread.h>
#include <stdio.h>
#include "train.h"
/*********** Train Thread Code **************/
void * train_thread(void * args)
{
    train_threadArgs * trainArgs =(struct train_threadArgs*) args;
    station_load_train(trainArgs->station, trainArgs->seatsNum);
    pthread_exit(NULL);
}

/*********** Passenger Thread Code **************/
void * passenger_thread(void * args)
{
    Station* station1=(struct Station*)args;
    station_wait_for_train(station1);
    station_on_board(station1);
    pthread_exit(NULL);
}

void main(void)
{
    //Intialize Local Vraiables needed in program.
    Station station1;
    station_init(&station1);
    int trainThreadNum,passThreadNum;
    //Take input from user.
    printf("Please enter number of Passengers : ");
    scanf("%d",&passThreadNum);
    printf("Please enter number of Trains : ");
    scanf("%d",&trainThreadNum);
    //Intialize Local Variables needed in program after input.
    pthread_t train_threadArr[trainThreadNum],pass_threadArr[passThreadNum];
    train_threadArgs trainArgs[trainThreadNum];
    //Populate Train Thread Arguments
    for(int i=0; i<trainThreadNum;i++)
    {
        printf("Enter Seat Number of Train %d : ",i+1);
        scanf("%d",&trainArgs[i].seatsNum);
        trainArgs[i].station = &station1;
    }

    /************ Thread Handling ***************/
    for (int i = 0; i < passThreadNum; ++i)
        pthread_create(&pass_threadArr[i], NULL, passenger_thread, &station1);
    for (int i = 0; i < trainThreadNum; ++i)
        pthread_create(&train_threadArr[i], NULL, train_thread, &trainArgs[i]);
    for (int i = 0; i < passThreadNum; ++i)
        pthread_join(pass_threadArr[i], NULL);
    for (int i = 0; i < trainThreadNum; ++i)
        pthread_join(train_threadArr[i], NULL);
}