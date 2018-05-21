//
// Created by max-r on 18-May-18.
//

#include "set.h"
#include "user.h"
#include "malloc.h"
#include "string.h"
#include <fci.h>
#include <stdio.h>

struct user {
    char* name;
    int age;
    Set favorite_series_set;
    Set friend_set;

};
static void* SetUserCopy(void* user){
if (user==NULL){
    return NULL;
}
   return user;
}
static void SetUserDestroy(void* user){

}
static int SetUserAreEqual(void* first_user ,void* second_user ){
    if(((strcmp(UserGetName(NULL,(User)first_user),UserGetName(NULL,(User)second_user)))==0)&&
       UserGetAge(NULL,(User)first_user)==UserGetAge(NULL,(User)second_user)){
        return 0;
        }
         return 1; }
//////////////
static char *UserNameCopy(const char *str) {
    char *copy = malloc(strlen(str) + 1);

    return copy ? strcpy(copy, str) : NULL;
}
static bool  UserAgeIsCorrect(unsigned int user_age){
    if (user_age<=5||user_age>=127){
        return false; }
     return true;
}
static bool  UserNameIsCorrect(char* user_name){ return true;}
static void  ChangeStatusIfNotNull(UserStatus* status,UserStatus status_value){
    if(status!=NULL){
        *status= status_value;
    }
}
/////////////
User UserCreate( UserStatus* status,char* user_name, unsigned int user_age){
    if (UserAgeIsCorrect(user_age)==false) {
        ChangeStatusIfNotNull(status,USER_INCORRECT_AGE);
        return NULL;
    }
    if(UserNameIsCorrect(user_name)==false){
        ChangeStatusIfNotNull(status,USER_INCORRECT_NAME);
        return NULL;
        }
    User new_user = malloc(sizeof(*new_user));
    if (new_user==NULL) {
        ChangeStatusIfNotNull(status,USER_MEMORY_ERROR);
        return NULL;
    }
    new_user->name = UserNameCopy(user_name);

    if (new_user->name==NULL) {
        ChangeStatusIfNotNull(status,USER_MEMORY_ERROR);
        free(new_user);
        return NULL;
    }
    new_user->age=user_age;
    new_user->favorite_series_set=NULL;
    new_user->friend_set=NULL;
    ChangeStatusIfNotNull(status,USER_STATUS_OK);
    return new_user ;
}
UserStatus   UserDestroy(User user){
    if(user==NULL){
        return INVALID_USER;
    }
    setDestroy(user->favorite_series_set);
    setDestroy(user->friend_set);
    free(user->name);
    free(user);
}
char* UserGetName(UserStatus* status,User user){
    if (user==NULL){
       ChangeStatusIfNotNull(status,INVALID_USER);
       return NULL;
    }
    return user->name;
}
int   UserGetAge(UserStatus* status,User user){
    if (user==NULL){
        ChangeStatusIfNotNull(status,INVALID_USER);
        return 0;
    }
    return user->age;
}
Set  UserGetSeriesSet(User user){
    if(user!=NULL){
        return setGetFirst(user->favorite_series_set);
    }
    return NULL;
}
Set   UserGetFriendSet(User user){/////////////////////////////////////////
    if(user!=NULL){
        return setGetFirst(user->friend_set);
    }
    return NULL;
}
UserStatus  UserAddFriend(User user_that_add , User user_to_add){
     if(user_that_add==NULL||user_to_add==NULL){
         return INVALID_USER;
     }
     if (UserGetFriendSet(user_that_add)==NULL){
        Set friends = setCreate(SetUserCopy,SetUserDestroy,SetUserAreEqual);
        user_that_add->friend_set=friends;
        setAdd(user_that_add->friend_set,(void*)user_to_add);
         return USER_STATUS_OK;
        }
     if (setIsIn(user_that_add->friend_set,(void*)user_to_add)==FALSE) {
         setAdd(user_that_add->friend_set, (void *) user_to_add);
         }
         return USER_STATUS_OK;

}
UserStatus  UserDeleteFriend(User user_that_delete, User user_to_delete){
    if(user_that_delete==NULL||user_to_delete==NULL){
        return INVALID_USER;
    }
    if(setIsIn(user_that_delete->friend_set,(void*)user_to_delete)==TRUE){
        setRemove(user_that_delete->friend_set,(void*)user_to_delete);

    }
    return USER_STATUS_OK;
}
void UserPrintFriendlist(User user){
    User print_user= setGetFirst(user->friend_set);
    printf("%s \n",UserGetName(NULL,print_user));
    print_user=setGetNext(user->friend_set);
    while(print_user!=NULL){
        printf("%s \n",UserGetName(NULL,print_user));
        print_user=setGetNext(user->friend_set);
    }


}
