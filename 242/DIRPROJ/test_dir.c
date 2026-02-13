#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    char dir_name[100];
    char inf[100];

    printf("Enter directory name: ");
    scanf("%s", dir_name);

    DIR *dir_ptr = opendir(dir_name);

    if (dir_ptr == NULL) {
        printf("Error: Unable to open directory '%s'\n", dir_name);
        return 1;
    }

    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        printf("%s\n", dirent_ptr->d_name);

        if (strcmp(dirent_ptr->d_name + strlen(dirent_ptr->d_name) - 3, ".in") == 0) {
            strcpy(inf, dirent_ptr->d_name);
        }
    }

    closedir(dir_ptr);

    printf("Input file: %s\n", inf);

    return 0;
}
//PROBABLY NOT THE SAME AS WHAT DYM WANTS