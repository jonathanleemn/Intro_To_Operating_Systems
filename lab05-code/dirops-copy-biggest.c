// Program to scan a directory for the largest file then make a copy
// of it. Uses stat(), opendir() readdir(), open(), read(), write()
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define NAMELEN 2048
#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  long long max_size = 0;                            // track longest file size and name
  char max_name[NAMELEN] = {};
  struct stat sb;

  DIR *dir = opendir(".");                           // open current directory
  struct dirent *file = NULL;
  while( (file = readdir(dir)) != NULL){             // get a file from the directory
    stat(file->d_name, &sb);                         // use stat to get statistics on it
    printf("%-30s : %6lld bytes\n",                  // show size
           file->d_name, (long long) sb.st_size);
    if(sb.st_size > max_size){                       // if larger than curren biggest file
      max_size = sb.st_size;                         // adopt new largest size
      strncpy(max_name, file->d_name, NAMELEN);      // and name
    }
  }
  closedir(dir);


  printf("Largest file: %s with %lld bytes\n",       // print largest file found
         max_name, max_size);

  char copy_name[NAMELEN];                           // set up name of copy file
  snprintf(copy_name, NAMELEN, "%s.copy", max_name);
  printf("Copying %s to %s\n",max_name,copy_name);

  char buf[BUFSIZE];
  int infd = open(max_name, O_RDONLY);               // open largest for reading
  int flags = O_WRONLY | O_CREAT | O_TRUNC;          // write, create, truncate existing
  // mode_t perms = S_IRUSR | S_IWUSR;                  // user read/write
  mode_t perms = S_IRUSR | S_IWUSR | S_IRGRP;        // // user read/write, group read

  // // Optional: set the permissions to be identical to the original file
  // stat(max_name, &sb);
  // perms = sb.st_mode;

  int outfd = open(copy_name, flags, perms);         // open copy for writing
  int nbytes;
  while( (nbytes = read(infd, buf, BUFSIZE)) > 0){   // read until no bytes left
    // write(outfd, buf, BUFSIZE);                      // buggy write to outfd
    write(outfd, buf, nbytes);                       // correct write
  }
  printf("Copy complete\n");
  close(infd);                                       // close fds
  close(outfd);
  return 0;
}
