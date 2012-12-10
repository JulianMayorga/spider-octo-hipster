/*
 * @file    net.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing net utilities
 */

#ifndef _NET_

#define _NET_

/* FUNCTIONS */

/*
 * @brief   Fetch url
 *
 * @param   host
 * @param   url to be fetched
 * @return  buffer with url content,
 *          NULL on error
 */
char* net_fetch(char* host, char* url);
char* html_get_start(char* buffer);

#endif
