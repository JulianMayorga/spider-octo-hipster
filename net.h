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
 * @return  page content on success,
 *          NULL on error
 */
void net_fetch(char* host, char* url);

#endif
