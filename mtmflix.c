#include <stdbool.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "set.h"
#include "list.h"
#include "user.h"
#include "mtmflix.h"
#include "series.h"


struct mtmFlix_t {
    List series;
    List users;
};


static bool mtmFlixStringInvalidName(const char *name);
static int* mtmFlixSeriesFixedAges (int* ages);
static int isBigger (int a, int b);
static int isSmaller (int a, int b);
static bool mtmFlixSeriesExists (MtmFlix mtmFlix,const char * test_name);
static const char* enumToString (Genre genre);
static ListElement ListSeriesCopy (ListElement series);
static void ListSeriesDestroy (ListElement series);
static int ListSeriesCompareByGenreAndName(ListElement series1, ListElement series2);

MtmFlix mtmFlixCreate(){
    MtmFlix mtm_flix = malloc(sizeof(*mtm_flix));
    if (!mtm_flix){
        return NULL;
    }
    mtm_flix->users=NULL;
    mtm_flix->series=NULL;
    return mtm_flix;

}

MtmFlixResult mtmFlixAddSeries(MtmFlix mtmflix, const char* name, int episodesNum, Genre genre, int* ages, int
episodeDuration){
    if (!name){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if (mtmFlixStringInvalidName(name)){
        return MTMFLIX_ILLEGAL_SERIES_NAME;
    }
    if (episodesNum<1){
        return MTMFLIX_ILLEGAL_EPISODES_NUM;
    }
    if (episodeDuration<1){
        return MTMFLIX_ILLEGAL_EPISODES_DURATION;
    }
    if (mtmFlixSeriesExists(mtmflix,name)){
        return MTMFLIX_SERIES_ALREADY_EXISTS;
    }
    SeriesStatus *series_status;
    Series new_series = SeriesCreate(series_status, name, episodesNum, enumToString(genre), mtmFlixSeriesFixedAges(ages),episodeDuration);
    if (*series_status==SERIES_MEMORY_ERROR){
        return MTMFLIX_OUT_OF_MEMORY;
    }

    }



static bool mtmFlixStringInvalidName(const char *name) {
    assert (name);
    if (!strlen(name)){
        return true;
    }
    for (int i = 0; i < strlen(name); i++) {
        if (!((name[i] >= '0') && (name[i] <= '9') || ((name[i] >= 'A') && (name[i]) <= 'Z') ||
              ((name[i] >= 'a') && (name[i]) <= 'z')))
            return true;
    }
    return false;
}

static int* mtmFlixSeriesFixedAges (int* ages){
    if (!ages){
        return NULL;
    }
    int fixed_ages[2];
    fixed_ages[0]=isBigger(ages[0],MTM_MIN_AGE);
    fixed_ages[1]=isSmaller(ages[1],MTM_MAX_AGE);
    int *ptr;
    ptr = fixed_ages;
    return ptr;
}



static int isBigger (int a, int b){
    if (a>b){
        return a;
    }
    return b;
}
static int isSmaller (int a, int b){
    if (a>b){
        return b;
    }
    return a;
}


static bool mtmFlixSeriesExists (MtmFlix mtmFlix,const char * test_name){
    LIST_FOREACH(Series,series,mtmFlix->series){
        if (strcmp(SeriesGetName(series),test_name)==0){
            return true;
        }
    }
    return false;
}

static const char* enumToString (Genre genre){
    const char* str;
    switch (genre) {
        case SCIENCE_FICTION:
            str = "SCIENCE_FICTION";
            break;
        case DRAMA:
            str = "DRAMA";
            break;
        case COMEDY:
            str = "COMEDY";
            break;
        case CRIME:
            str = "CRIME";
            break;
        case MYSTERY:
            str = "MYSTERY";
            break;
        case DOCUMENTARY:
            str = "DOCUMENTARY";
            break;
        case ROMANCE:
            str = "ROMANCE";
            break;
        case HORROR:
            str = "HORROR";
            break;
    }
    return str;
}

static ListElement ListSeriesCopy (ListElement series){
    Series copy = SeriesCreate(NULL,SeriesGetName(series),SeriesGetEpisodeNumber(series),SeriesGetGenre(series),SeriesGetAges(series),SeriesGetEpisodeDuration(series));
    if (!copy){
        return NULL;
    }
    return copy;
}
static void ListSeriesDestroy (ListElement series){
    SeriesDestroy((Series)series);
}
static int ListSeriesCompareByGenreAndName(ListElement series1, ListElement series2){
    int result = strcmp (SeriesGetGenre(series2), SeriesGetGenre(series1));
    if (result==0){
        result = strcmp (SeriesGetName(series2), SeriesGetName(series1));
    }
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void* ListUserCreate(void* user){
    UserStatus status ;
    User copy_of_user=UserCreate(&status,UserGetName(NULL,(User)user),UserGetAge(NULL,(User)user));
    if(copy_of_user==NULL){
        return NULL;
    }
    return (void*)copy_of_user;

}
static void ListUserDestroy(void* user){
    UserStatus status=UserDestroy((User)user);
    ;}
static User GetUserByName (List users_list,char* user_name){
}



static MtmFlixResult AddUserToList (MtmFlix mtmFlix,User user){
    if (mtmFlix->users==NULL){
        List users_list =listCreate(ListUserCreate,ListUserDestroy);
        listInsertFirst(users_list,(void*)user);
        return MTMFLIX_SUCCESS;
    }
    listInsertLast(mtmFlix->users,(User)user);
    return MTMFLIX_SUCCESS;

    ;}


MtmFlixResult mtmFlixAddUser(MtmFlix mtmflix, const char* username, int age){
    if(mtmflix==NULL){
        return MTMFLIX_NULL_ARGUMENT;
    }
    if(mtmFlixStringInvalidName(username)==true)
    {
        return MTMFLIX_ILLEGAL_USERNAME;
    }
    if (GetUserByName((mtmflix->users),username)!=NULL){
        return MTMFLIX_USERNAME_ALREADY_USED;
    }
    UserStatus status;
    User new_user =UserCreate(&status,username,age);
    switch (status) {
        case USER_INCORRECT_AGE: {
            return MTMFLIX_ILLEGAL_AGE;
        }
        case USER_MEMORY_ERROR:{
            return MTMFLIX_OUT_OF_MEMORY;
        }
        case USER_STATUS_OK:{
            return AddUserToList(mtmflix,new_user);

        }


    }
}






