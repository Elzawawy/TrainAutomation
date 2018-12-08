#ifndef TRAIN_H_
#define TRAIN_H_

typedef struct Station 
{
    int waitingPassengersNum;
    int availableTrainSeatNum;
    pthread_mutex_t station_lock;
    pthread_cond_t train_in_station;
    pthread_cond_t train_loaded;

    
}Station;

void station_init(Station * station);
void station_load_train(Station *station, int count);
void station_wait_for_train(Station *station);
void station_on_board(Station *station);

#endif