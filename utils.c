/*
 * @file    utils.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing utilities for flow execution
 *
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void utils_manage_args(int argc, char **argv, int *number_of_entries_to_read, char *filepath) {
	int option;
	while ((option = getopt(argc, argv, "n:f:")) != -1) {
		switch (option) {
			case 'n':
				printf("Setting number of entries to: %d\n", atoi(optarg));
				*number_of_entries_to_read = atoi(optarg);
				break;
			case 'f':
				printf("Changing file to read to: %s\n", optarg);
				snprintf(filepath, sizeof(filepath), "%s", optarg);
				filepath[strlen(optarg)] = '\0';
				break;
			default:
				printf("USAGE: -n <number of entries to read from file>\n -f <filename>\n");
		}

	}

}
