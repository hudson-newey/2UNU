#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <crypt.h>
#include <pwd.h>
#include "passwd.h"

#define MAX_USERID_LENGTH 32
#define MAX_PASSWORD_LENGTH 128

char *currentUsername()
{
    char username[MAX_USERID_LENGTH];
    cuserid(username);
}

void getPassword(char *password)
{
    struct termios old, new;
    int i = 0;
    char ch;

    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while (1)
    {
        ch = getchar();

        if (ch == '\n' || i >= MAX_PASSWORD_LENGTH - 1)
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 127 && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else
        {
            password[i] = ch;
            i++;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

int chpasswd(const char *username, const char *new_password)
{
    FILE *passwd_file = fopen("/etc/shadow", "r+");

    char line[4096];

    while (fgets(line, sizeof(line), passwd_file) != NULL)
    {
        if (strstr(line, username) != NULL)
        {

            long pos = ftell(passwd_file);
            fseek(passwd_file, pos - strlen(line), SEEK_SET);
            fprintf(passwd_file, "%s:%s", username, new_password);
            break;
        }
    }

    fclose(passwd_file);

    return 0;
}

int changeSystemPassword(const char *username, const char *newPassword)
{
    struct passwd *user_info;

    user_info = getpwnam(username);

    if (user_info == NULL)
    {
        fprintf(stderr, "User not found.\n");
        return 1;
    }

    char *encrypted_password = crypt(newPassword, user_info->pw_passwd);

    if (encrypted_password != NULL)
    {
        user_info->pw_passwd = encrypted_password;
        if (chpasswd(user_info->pw_name, encrypted_password) == 0)
        {
            printf("Password changed successfully.\n");
        }
        else
        {
            fprintf(stderr, "Failed to change the password.\n");
        }
    }
    else
    {
        fprintf(stderr, "Failed to encrypt the new password.\n");
    }

    return 0;
}

int changePasswordPrompt()
{
    const char *username = currentUsername();

    printf("Changing password for %s.\n", username);
    printf("Current Password:");

    char currentPassword[MAX_PASSWORD_LENGTH];
    getPassword(currentPassword);

    printf("\nNew password:");
    char newPassword[MAX_PASSWORD_LENGTH];
    getPassword(newPassword);

    printf("\nRetype password:");
    char newPasswordConfirmation[MAX_PASSWORD_LENGTH];
    getPassword(newPasswordConfirmation);

    printf("\n");

    if (strcmp(newPassword, newPasswordConfirmation) != 0)
    {
        printf("Sorry, passwords do not match.\n");
        printf("passwd: Authentication token manipulation error\n");
        printf("passwd: password unchanged\n");
        return 10;
    }

    printf("passwd: password updated successfully\n");

    return changeSystemPassword(username, newPassword);
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "--version") == 0)
        {
            printf("%s\n", version);
            return 0;
        }
        else if (strcmp(argv[1], "--help") == 0)
        {
            printf("%s\n", helpDocs);
            return 0;
        }

        printf("Changing password for other users is not currently supported\n");
        return 1;
    }

    return changePasswordPrompt();
}
