/*
 * @file    net.c
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing net utilities
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

#include "net.h"

#define HTTP_PORT "80"

//implicit declarations
int connect_inet_socket(char* host, int* socket_fd);

/* Fetch url */
char* net_fetch(char* host, char* url) {
  int socket_fd, rwerr = 1, size = 0;
  char* request, buf[16];
  char* content = NULL;
  char* tmp;
  //connect to inet socket
  if ( 0 != connect_inet_socket(host, &socket_fd) ) {
    perror("connect inet socket");
  }
  //now we have an established connection
  //initialize with zeros the GET request
  //TODO replace ugly 53 with a constant
  request = calloc(53+strlen(host)+strlen(url),1);

  sprintf(request, "GET %s HTTP/1.1\nHost: %s\nUser-agent: simple-http client\n\n", url, host);
  //write to the socket the GET request
  if ( 0 > write(socket_fd, request, strlen(request)) ) {
    perror("write");
  }

  //disable write on the socket
  shutdown(socket_fd, SHUT_WR);

  while ( rwerr > 0 )
  {
    //read the socket
    rwerr = read(socket_fd, buf, 16);
    if (rwerr > 0 ) {
      //add "read" number of bytes to result integer
      size += rwerr;
      tmp = (char*)realloc(content, size);
      if ( tmp != NULL ) {
        content = tmp;
        //concatenate read bytes to content buffer
        memcpy(content + size - rwerr, buf, rwerr);
      } else {
        free(content);
        perror("realloc");
      }
    }
    /*if ( 0 > write(1, buf, rwerr) ) {
      perror("write");
      content = NULL;
      }
      */
  }

  close(socket_fd);
  content = html_get_start(content);
  return content;
}

/* Connect to socket */
int connect_inet_socket(char* host, int* socket_fd) {
  struct addrinfo *result, hints;
  char port[6];
  int to_return = 0;

  //fill port with zeros
  memset(port, 0, 6);
  //set port
  strncpy(port, HTTP_PORT, 2);

  //fill hints structure with zeros
  memset(&hints, 0, sizeof(struct addrinfo));

  //set INET address to unspecified (IPv4 or IPv6)
  hints.ai_family = AF_UNSPEC;
  //set socket type to SOCK_STREAM (TCP/IP)
  hints.ai_socktype = SOCK_STREAM;

  //convert host text representation to structured binary format (getaddrinfo)
  if ( 0 != getaddrinfo(host, port, &hints, &result)) {
    perror("getaddrinfo");
    to_return = -1;
  }

  //create socket
  *socket_fd = socket(result->ai_family,SOCK_STREAM,0);

  if ( *socket_fd < 0 ) {
    perror("socket");
    to_return = -1;
  }

  if ( connect(*socket_fd, result->ai_addr, result->ai_addrlen) == -1) {
    perror("connect");
    to_return = -1;
  }

  return to_return;
}

/* Remove HTTP header from a buffer */
char* html_get_start(char* buffer) {
  static char * end_of_header =  "\r\n\r\n";
  char *html_start = NULL;
  char* htmlcontent;

  //Detect the beginning of html content
  htmlcontent = strstr(buffer, end_of_header);
  if ( htmlcontent != NULL ) {
    //remove end_of_header
    htmlcontent += sizeof(end_of_header);
    //set html_start at html_content
    html_start = htmlcontent;
  } else {
    html_start = NULL;
  }

  return html_start;
}
