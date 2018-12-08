#ifndef TRAIN_H_
#define TRAIN_H_

typedef struct Station 
{
    pthread_mutex_t train_lock;
    
}Station;

void station_init(Station * station);
void station_load_train(Station *station, int count);
void station_wait_for_train(Station *station);
void station_on_board(Station *station);

#endif