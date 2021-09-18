#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getline(char **lineptr, size_t *n, FILE *stream) {
  char *bufptr = NULL;
  char *p = bufptr;
  size_t size;
  int c;

  if (lineptr == NULL) {
    return -1;
  }
  if (stream == NULL) {
    return -1;
  }
  if (n == NULL) {
    return -1;
  }
  bufptr = *lineptr;
  size = *n;

  c = fgetc(stream);
  if (c == EOF) {
    return -1;
  }
  if (bufptr == NULL) {
    bufptr = malloc(128);
    if (bufptr == NULL) {
      return -1;
    }
    size = 128;
  }
  p = bufptr;
  while (c != EOF) {
    if ((p - bufptr) > (size - 1)) {
      size = size + 128;
      bufptr = realloc(bufptr, size);
      if (bufptr == NULL) {
        return -1;
      }
    }
    *p++ = c;
    if (c == '\n') {
      break;
    }
    c = fgetc(stream);
  }

  *p++ = '\0';
  *lineptr = bufptr;
  *n = size;

  return p - bufptr - 1;
}

int main(void) {
  const char *pwd = "secret";
  char *line = NULL;
  size_t len = 0;
  long int linesize = 0;

  while (1) {
    printf("password:");
    linesize = getline(&line, &len, stdin);
    int rc = strncmp(line, pwd, 6);
    if (rc == 0) {
      printf("Good job!\n");
      break;
    } else {
      printf("wrong pwd!\n");
    }
  }
  return 0;
}
