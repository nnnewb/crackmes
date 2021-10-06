#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(char **pLine, size_t *n, FILE *stream) {
  char *buffer = NULL;
  size_t idx = 0;
  size_t size;
  int c;

  if (pLine == NULL) {
    return -1;
  }
  if (stream == NULL) {
    return -1;
  }
  if (n == NULL) {
    return -1;
  }
  buffer = *pLine;
  size = *n;

  c = fgetc(stream);
  if (c == EOF) {
    return -1;
  }
  if (buffer == NULL) {
    buffer = malloc(128);
    if (buffer == NULL) {
      return -1;
    }
    size = 128;
  }
  while (c != EOF) {
    if (idx > (size - 1)) {
      size = size + 128;
      buffer = realloc(buffer, size);
      if (buffer == NULL) {
        return -1;
      }
    }
    buffer[idx] = (char)c;
    idx++;
    if (c == '\n') {
      break;
    }
    c = fgetc(stream);
  }

  buffer[idx] = '\0';
  *pLine = buffer;
  *n = size;

  return (int)(idx - 1);
}

int main(void) {
  const char *pwd = "secret";
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("password:");
    get_line(&line, &len, stdin);
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
