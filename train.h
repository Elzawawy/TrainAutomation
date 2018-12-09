/*
 * Train Module to Control Station Functions and Struct Object. 
 * 
 * Author : Amr Elzawawy
 * Date : 6 December 2018
 */

#ifndef TRAIN_H_
#define TRAIN_H_

//Station Object Definition.
typedef struct Station 
{
    int waitingPassengersNum;
    int availableSeatsNum;
    int trainFlag;
    pthread_mutex_t station_mutex;
    pthread_cond_t train_in_station;
    pthread_cond_t train_loaded;
    pthread_cond_t next_train;
}Station;

//Arguments type for a train thread.
typedef struct train_threadArgs
{
    int seatsNum;
    Station * station;
}train_threadArgs;

//Initalize a station object to start usage.
void station_init(Station * station);
//Load a Train into a station.
void station_load_train(Station *station, int count);
//Add a Passenger to wait in station.
void station_wait_for_train(Station *station);
//Check the boarding of Passenger and accomdate a seat.
void station_on_board(Station *station);

#endif