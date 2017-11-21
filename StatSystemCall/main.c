#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Function which prints all *fd parameter information
void printStat(char *fd){

    struct stat sb;

    stat(fd, &sb);


    printf("File type:                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break; // Comment this line out with Windows OS
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break; // Comment this line out with Windows OS
    default:       printf("unknown?\n");                break;
    }

    printf("I-node number:            %ld\n", (long) sb.st_ino);

    printf("Mode:                     %lo (octal)\n",
           (unsigned long) sb.st_mode);

    printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
           (long) sb.st_uid, (long) sb.st_gid);

    printf("Preferred I/O block size: %ld bytes\n",  // Comment this line out with Windows OS
           (long) sb.st_blksize);                    // Comment this line out with Windows OS
    printf("File size:                %lld bytes\n",
           (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",       // Comment this line out with Windows OS
           (long long) sb.st_blocks);                // Comment this line out with Windows OS

    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));


}

int main(int argc, char *argv[])
{
    int MAX_LEN = 256;

    char *str1=malloc(sizeof(char)*MAX_LEN);
    char *exit = "exit";

    while( 1 ) {

        printf("Exit by typing 'exit' \n");
        printf("Enter path: ");
        fgets(str1, MAX_LEN, stdin);
        printf("\n");
        strtok(str1, "\n");

        DIR *d;
        struct dirent *dir;
        d = opendir(str1);

        if (d)
        {

            while ((dir = readdir(d)) != NULL)
            {

                char * str2 = dir->d_name;

                printf("Filename: ");
                printf(str2);
                printf("\n");
                printf("\n");

                char * str3 = (char *) malloc(1 + strlen(str1)+ strlen(str2) );
                strcpy(str3, str1);
                strcat(str3, str2);
                printStat(str3);


                printf("\n");
                printf("--------------------------------------- \n");
            }

            closedir(d);
        }
    else if (strcmp(exit, str1) == 0) {
        break;
    }
        else{
            printf("Directory not found \n");
        }
    }
    return 0;
}
