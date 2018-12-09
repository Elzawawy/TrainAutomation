#include <pthread.h>
#include <stdio.h>
#include "train.h"

#define FLAG_UP 1
#define FLAG_DOWN 0
void station_init(Station * station)
{
    station->availableSeatsNum=0;
    station->waitingPassengersNum=0;
    station->trainFlag= FLAG_DOWN;
    pthread_mutex_init(&station->station_mutex , NULL);
    pthread_cond_init(&station->train_in_station, NULL);
    pthread_cond_init(&station->train_loaded,NULL);
    pthread_cond_init(&station->next_train,NULL);
}

void station_load_train(Station *station, int count)
{
    //Try to acquire Station Lock.
    pthread_mutex_lock(&station->station_mutex);
    //While that the flag is held up ! (Another Train in Station)
    while( station->trainFlag == FLAG_UP)
        pthread_cond_wait(&(station->next_train), &(station->station_mutex));

    //static variable to keep track of how many train entered the station.
    static int numOfTrains = 0;
    //Assign available train seats number with the count params.
    station->availableSeatsNum = count;
    //Raise Flag up to indicate my arrival.
    station->trainFlag = FLAG_UP;
    //Increment number of trains state variable.
    numOfTrains++;
    printf("Train %d arrived\n",numOfTrains);

    //Signal all waiting passengers on the train that it has arrived.
    pthread_cond_broadcast(&(station->train_in_station));

    //Wait while the station's availableSeatsNumber and StationWaitingPassengersNumber is not yet full.
    while( (station->availableSeatsNum > 0)  && (station->waitingPassengersNum > 0))
        pthread_cond_wait(&(station->train_loaded),&station->station_mutex);
    //set state variable to false to indicate i am about to leave.
    station->trainFlag = FLAG_DOWN;
    printf("Train %d leaving station with seats left = %d\n",numOfTrains,station->availableSeatsNum);
    //Signal for the next Train to arrive.
    pthread_cond_signal(&(station->next_train));
    //Leave the station.
    pthread_mutex_unlock(&station->station_mutex);
    
}

void station_wait_for_train(Station *station)
{
    pthread_mutex_lock(&station->station_mutex);
    station->waitingPassengersNum++;
    printf("Passenger %d waiting\n",station->waitingPassengersNum);
    while( station->trainFlag == FLAG_DOWN || station->availableSeatsNum == 0) 
        pthread_cond_wait(&(station->train_in_station), &(station->station_mutex));
    printf("Passenger %d boarded\n",station->waitingPassengersNum);
    if(station->waitingPassengersNum > 0)
        station->waitingPassengersNum--;
}

void station_on_board(Station *station)
{
    if(station->availableSeatsNum > 0)
        station->availableSeatsNum--;
    printf("Passenger Seated, Remaining Seats is %d \n",station->availableSeatsNum);
    pthread_cond_signal(&(station->train_loaded));
    pthread_mutex_unlock(&station->station_mutex);
}
