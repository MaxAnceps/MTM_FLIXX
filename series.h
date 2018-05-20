#ifndef SERIES_H_
#define SERIES_H_

#include "list.h"

typedef struct series_t * Series;

typedef enum seriesStatus {
    SERIES_OK,
    SERIES_MEMORY_ERROR,
    SERIES_NULL_ARGUMENT,

} SeriesStatus;

Series SeriesCreate (SeriesStatus* status, const char* name, int episodes_num, const char* genre, int* ages, int episode_duration);
void SeriesDestroy (Series series);
char* SeriesGetName (Series series);
char* SeriesGetGenre (Series series);
int SeriesGetEpisodeNumber (Series series);
int SeriesGetEpisodeDuration (Series series);
int* SeriesGetAges (Series series);
ListElement ListSeriesCopy (ListElement series);

#endif /* SERIES_H_ */
