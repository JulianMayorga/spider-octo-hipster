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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "file.h"

//implicit declarations
char* _file_dirpath(char* dir);
char* _file_fullpath(char* dir, char* filename);

//Save buffer to a file on disk
int file_save(char* buffer, char* dir, char* filename) {
  int fd;
  char* dirpath = NULL;
  char* fullpath = NULL;
  //permit reading (S_IRUSR) and writing (S_IWUSR) from the user
  //and reading from group members (S_IRGRP) and others (S_IROTH)
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  dirpath = _file_dirpath(dir);
  if ( -1 == mkdir(dirpath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ) {
    perror("mkdir");
  }

  fullpath = _file_fullpath(dirpath, filename);

  //opens the file "name", either creating it or appending it to 0 if it exists
  fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, mode);
  if ( -1 == fd ) {
    perror("open");
	exit(EXIT_FAILURE);
  }

  //write
  if ( -1 == write(fd, buffer, strlen(buffer)) ) {
    //hacky, but it is a way to return -1 on error
    fd = -1;
    perror("write");	
	exit(EXIT_FAILURE);
  }

  return fd;
}

char* file_to_buffer(const char* filename) {
  char *buffer;
  struct stat file_info;
  int fd;

  if (0 > (fd = open(filename, O_RDONLY))) {
    perror("open");
    buffer = NULL;
	exit(EXIT_FAILURE);
  } else {
    fstat(fd, &file_info);
    //read whole file - EOF
    buffer = (char*)calloc(file_info.st_size, 1);
    if (-1 == read(fd, buffer, file_info.st_size - 1) ) {
      perror("read");
      buffer = NULL;
    }
  }

  close(fd);
  return buffer;
}

char* _file_dirpath(char* dir) {
  static char* sites_dir = "sites/";
  char* dirpath = NULL;

  dirpath = (char*)calloc(strlen(sites_dir) + strlen(dir) + 1, 1);
  //create dir
  strncat(dirpath, sites_dir, strlen(sites_dir));
  strncat(dirpath, dir, strlen(dir));

  return dirpath;
}

char* _file_fullpath(char* dirpath, char* filename) {
  char* fullpath = NULL;

  fullpath = (char*)calloc(strlen(dirpath) + strlen(filename) + 1, 1);
  //form file path
  strncat(fullpath, dirpath, strlen(dirpath));
  strncat(fullpath, filename, strlen(filename));

  return fullpath;
}
