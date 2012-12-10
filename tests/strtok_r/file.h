/*
 * @file    file.h
 *
 * @author  Marcelo Romagnoli
 * @author  Julian Mayorga
 */

/*
 * Description: Library providing file utilities
 */

#ifndef _FILE_

#define _FILE_

/* FUNCTIONS */

/*
 * @brief   Save buffer to a file on disk
 *
 * @param   buffer to save
 * @param   dir to save the file
 * @param   filename of the new file
 * @return  0 on success,
 *         -1 on error
 */
int file_save(char* buffer, char* dir, char* filename);
char* file_to_buffer(const char* filename);

#endif
