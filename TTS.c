#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_USER 100
#define MAX_LENGTH 50

struct user
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
};
typedef struct user usr;

void inputPassword(char password[]){
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if(ch == '\r'){
            password[i] = 0;
            printf("\n");
            break;
        }
        else if (ch == '\b')
        {
            if (i > 0) {
            i--;
            printf("\b \b");
            }
        }
        else if ( i < MAX_LENGTH - 1) //biar ada slot buat \0 kalo gk nanti eror
        {
            password[i] = ch;
            i++;
            printf("*");
        }
        
    }
    
}

bool regis(usr users[],int *userCount){
    if (*userCount >= MAX_USER)
    {
        return 0;
    }
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    printf("Masukkan username baru: ");
    fgets(username,MAX_LENGTH,stdin);
    username[strcspn(username, "\n")] = '\0';
    
    for (int i = 0; i < *userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            printf("Username sudah ada! \n");
            return 0;
        }
        
    }
    
    printf("Masukkan password baru: ");
    inputPassword(password);
    password[strcspn(password, "\n")] = '\0';

    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);
    (*userCount)++;

    return 1;
}

bool login(usr users[], int *userCount){
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    printf("Masukkan username: ");
    fgets(username,MAX_LENGTH,stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Masukkan password: ");
    inputPassword(password);
    for (int i = 0; i < *userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            return 1;
        }
    }
    return 0;
    
}

int main(){
    usr users[MAX_USER];
    int userCount = 0;
    int i = 0;
    int milih;
    while (i <=5)
    {
        regis(users, &userCount);
        i++;
        /* code */
    }
    
     return 0;
}
