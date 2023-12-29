#ifndef __LEDIS_UTIL_H__
#define __LEDIS_UTIL_H__

/**
 * Wrapper functions for
 * read/write into
 * frame buffer
 */

/**
 * Send response to client
 * with given file descriptor
 */
void ledis_respond(char *, int);

/**
 * get request / response
 */
const char* ledis_obtain();

#endif //__LEDIS_UTIL_H__
