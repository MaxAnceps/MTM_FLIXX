//
// Created by Lior on 19/05/2018.
//

#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include "series.h"
#include "list.h"

struct series_t{
    char* name;
    int episodes_num;
    char* genre;
    int ages[2];
    int episodes_dur;
};

static char *SeriesStringCopy(const char *str);

Series SeriesCreate (SeriesStatus* status, const char* name, int episodes_num, const char* genre, int* ages, int episode_duration){
    if ((!name)||(!ages)||(!genre)){
        *status = SERIES_NULL_ARGUMENT;
        return NULL;
    }

    Series new_series = malloc(sizeof(*new_series));
    if (!new_series){
        *status = SERIES_MEMORY_ERROR;
        return NULL;
    }

    new_series->name = SeriesStringCopy(name);
    if (!new_series->name){
        *status = SERIES_MEMORY_ERROR;
        free (new_series);
        return NULL;
    }

    new_series->genre = SeriesStringCopy(genre);
    if (!new_series->genre){
        *status = SERIES_MEMORY_ERROR;
        free(new_series->name);
        free (new_series);
        return NULL;
    }

    new_series->ages[0] = ages[0];
    new_series->ages[1] = ages[1];
    new_series->episodes_dur = episode_duration;
    new_series->episodes_num = episodes_num;
    if (!new_series->genre) {
        *status = SERIES_OK;
    }
    return new_series;
}

void SeriesDestroy (Series series){
    if (!series){
        return;
    }
    free (series->name);
    free (series->genre);
    free (series);
}

static char *SeriesStringCopy(const char *str) {
    char *copy = malloc(strlen(str) + 1);

    return copy ? strcpy(copy, str) : NULL;
}

char* SeriesGetName (Series series){
    if (!series){
        return NULL;
    }
    return series->name;
}


char* SeriesGetGenre (Series series){
    if (!series){
        return NULL;
    }
    return series->genre;
}

int SeriesGetEpisodeNumber (Series series){
    if (!series){
        return -1;
    }
    return series->episodes_num;
}

int SeriesGetEpisodeDuration (Series series){
    if (!series){
        return -1;
    }
    return series->episodes_dur;
}

int* SeriesGetAges (Series series){
    if (!series){
        return NULL;
    }
    return series->ages;
}

ListElement ListSeriesCopy (ListElement series){
    Series copy  = SeriesCreate(NULL,SeriesGetName(series),SeriesGetEpisodeNumber(series),SeriesGetGenre(series),SeriesGetAges(series),SeriesGetEpisodeDuration(series));
    if (!copy){
        return NULL;
    }
    return copy;
}