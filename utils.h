/*
 * @file    utils.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing utilities for flow execution
 */

#ifndef _UTILS_

#define _UTILS_

/* FUNCTIONS */

/*
 * @brief   Manage arguments
 *
 * @param   argc arguments count
 * @param   argv arguments values
 */
void utils_manage_args(int argc, char **argv, int *number_of_entries_to_read, char *filepath);

#endif
