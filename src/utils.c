#include "utils.h"

char *strdup(const char *src) {
	if(src == NULL) return NULL;
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}

char* get_now_as_str() {
  time_t current_time;
  char* timeString = calloc(11, sizeof (char));

  time(&current_time);
  struct tm* time_info = localtime(&current_time);

  strftime(timeString, 11, "%d/%m/%Y", time_info);
  return timeString;
}