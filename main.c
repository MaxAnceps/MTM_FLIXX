#include <stdio.h>
#include "list.h"
#include "map.h"
#include "set.h"
#include "user.h"
int main() {
    printf("Hello, World!\n");

    UserStatus userStatus1;
    User Vasilyy =UserCreate(&userStatus1,"Vasilyy",25);
    User Genadyy =UserCreate(&userStatus1,"Genadyy",27);
    printf("%s %s\n",UserGetName(&userStatus1,Vasilyy),UserGetName(&userStatus1,Genadyy));
    printf("%d %d\n",UserGetAge(NULL,Vasilyy),UserGetAge(NULL,Genadyy));
    userStatus1=UserAddFriend(Vasilyy,Genadyy);
    return 0;
}