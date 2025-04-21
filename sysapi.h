/*
Small API for easy compilation on Windows and GNU/Linux
*/

#ifndef SYSAPI_H_INCLUDED
#define SYSAPI_H_INCLUDED

// clear conlose from text
int console_clear(void);

// print content of file
// print_file("path/to/file");
int print_file(const char *path); // const char path[]

#endif // SYSAPI_H_INCLUDED