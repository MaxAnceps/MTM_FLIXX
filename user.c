//
// Created by max-r on 18-May-18.
//

#include "set.h"
#include "list.h"
#include "user.h"
#include "malloc.h"
#include "string.h"
#include <stdbool.h>
struct user {
    char* name;
    int age;
    List favorite_series;
    Set friend_list;

};
static void* SetUserCopy(void* user){
if (user==NULL){
    return NULL;
}
    User derefernced_user = (User)user;
    User new_user= UserCreate(NULL,UserGetName(NULL,derefernced_user),UserGetAge(NULL,derefernced_user));
    return (void*)new_user;
}
static void SetUserDestroy(void* user){
    UserDestroy((User)user);
}
static int SetUserAreEqual(void* first_user ,void* second_user ){
    if(((strcmp(UserGetName(NULL,(User)first_user),UserGetName(NULL,(User)second_user)))==0)&&
       UserGetAge(NULL,(User)first_user)==UserGetAge(NULL,(User)second_user)){
        return 0;
        }
         return 1;
}
//////////////
static char *UserNameCopy(const char *str) {
    char *copy = malloc(strlen(str) + 1);

    return copy ? strcpy(copy, str) : NULL;
}
static bool  UserAgeIsCorrect(unsigned int user_age){
    if (user_age<1){
        return false; }
     return true;
}
static bool  UserNameIsCorrect(char* user_name){ return true;}
static void  ChangeStatusIfNotNull(UserStatus* status,UserStatus status_value){
    if(status!=NULL){
        *status= status_value;
    }
}

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
    new_user->favorite_series=NULL;
    new_user->friend_list=NULL;
    ChangeStatusIfNotNull(status,USER_STATUS_OK);
    return new_user ;
}
void   UserDestroy(User user){}
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
List  GetUserSeriesList(User user);
Set   DriverGetFriendList(User user){
    if(user!=NULL){
        return user->friend_list;
    }
    return NULL;
}
UserStatus  UserAddFriend(User user_that_add , User user_to_add){
     if(user_that_add==NULL||user_to_add==NULL){
         return INVALID_USER;
     }
     if (DriverGetFriendList(user_that_add)==NULL){
        Set friends = setCreate(SetUserCopy,SetUserDestroy,SetUserAreEqual);
        user_that_add->friend_list=friends;
        setAdd(user_that_add->friend_list,(void*)user_to_add);
         return USER_STATUS_OK;
        }
    setAdd(user_that_add->friend_list,(void*)user_to_add);



}
void  UserDeleteFriend(User user_that_delete, User user_to_delete);
