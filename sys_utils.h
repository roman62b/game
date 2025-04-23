/*
Small API for easy compilation on Windows and GNU/Linux
*/

#ifndef SYS_UTILS_H_INCLUDED
#define SYS_UTILS_H_INCLUDED

// clear conlose from text
void sys_console_clear(void);

// print content of file
// print_file("path/to/file");
void sys_print_file(const char *path); // const char path[]

// ???
void sys_get_data_path(char *data_path, const char *data_file);

#endif // SYSAPI_H_INCLUDED