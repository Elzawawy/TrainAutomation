#include <pthread.h>
#include "train.h"

void station_init(Station * station)
{
    pthread_mutex_init(&station->station_lock , NULL);
}

void station_load_train(Station *station, int count)
{
    pthread_mutex_lock(&station->station_lock);
}

void station_wait_for_train(Station *station)
{
    pthread_mutex_lock(&station->station_lock);
}

void station_on_board(Station *station)
{

}