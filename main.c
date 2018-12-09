#include <pthread.h>
#include "train.h"
void * train_thread(void * args)
{
    Station* station1=(struct Station*) args;
    station_load_train(station1,10);
    pthread_exit(NULL);
}
void * passenger_thread(void * args)
{
    Station* station1=(struct Station*)args;
    station_wait_for_train(station1);
    station_on_board(station1);
    pthread_exit(NULL);
}
int main()
{
    Station station1;
    station_init(&station1);
    pthread_t trains[5], passengers[50];
    for (int i = 0; i < 50; ++i)
        pthread_create(&passengers[i], NULL, passenger_thread, &station1);
    for (int i = 0; i < 5; ++i)
        pthread_create(&trains[i], NULL, train_thread, &station1);
    for (int i = 0; i < 10; ++i)
        pthread_join(passengers[i], NULL);
    for (int i = 0; i < 5; ++i)
        pthread_join(trains[i], NULL);
    return 0;
}