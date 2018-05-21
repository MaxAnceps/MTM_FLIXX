//
// Created by max-r on 18-May-18.
//

#ifndef MTM_FLIX_USER_H
#define MTM_FLIX_USER_H

typedef struct user * User;

#include"set.h"
#include "list.h"
#include"mtmflix.h"

typedef enum userStatus {
    USER_STATUS_OK,
    USER_INCORRECT_NAME,
    USER_INCORRECT_AGE,
    USER_MEMORY_ERROR,
    INVALID_USER} UserStatus;


User UserCreate( UserStatus* status,char* user_name, unsigned int user_age);
UserStatus UserDestroy(User user);
char* UserGetName(UserStatus* status,User user);
int   UserGetAge(UserStatus* status,User user);
Set  UserGetSeriesSet(User user);
Set  UserGetFriendSet(User user);
UserStatus  UserAddFriend(User user_that_add , User user_to_add);
UserStatus  UserDeleteFriend(User user_that_delete, User user_to_delete);
//void UserAddFavoriteSeries(User user,Sereies series );
//void UserDeleteSeriesFromFavorites(User user,Series series);
void UserPrintFriendlist(User user);///////////////

#endif /* MTM_FLIX_USER_H */