/*
 * @file    file.c
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing file utilities
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "file.h"

//Save buffer to a file on disk
int file_save(char* buffer, char* name) {
  int fd;
  //permit reading (S_IRUSR) and writing (S_IWUSR) from the user
  //and reading from group members (S_IRGRP) and others (S_IROTH)
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  //opens the file "name", either creating it or appending it to 0 if it exists
  fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
  if ( -1 == fd ) {
    perror("open");
  }

  //write
  if ( -1 == write(fd, buffer, strlen(buffer)) ) {
    //hacky, but it is a way to return -1 on error
    fd = -1;
    perror("write");
  }

  return fd;
}
