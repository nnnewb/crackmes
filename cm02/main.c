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

size_t r_trim(char *str, size_t len) {
  size_t slen = strnlen(str, len);
  for (int i = slen - 1; i >= 0; i--) {
    if (str[i] == ' ' || str[i] == '\n' || str[i] == '\r') {
      str[i] = '\0';
    } else {
      break;
    }
  }
  return strnlen(str, len);
}

char *calculate(char *username, const size_t username_len) {
  const size_t input_buf_len = 8;
  char *input_buf = malloc(input_buf_len);
  for (size_t i = 0; i < input_buf_len; i++) {
    input_buf[i] = 0x52 + (char)i;
  }

  memcpy_s(input_buf, input_buf_len, username, username_len);

  for (size_t i = 0; i < input_buf_len; i++) {
    input_buf[i] ^= 0x25;
  }

  const size_t output_buf_len = 17;
  char *output_buf = malloc(output_buf_len);

  for (size_t i = 0; i < input_buf_len; i++) {
    sprintf_s(&output_buf[i * 2], output_buf_len - i * 2, "%02x", input_buf[i]);
  }

  output_buf[16] = 0;
  free(input_buf);
  return output_buf;
}

int main(void) {
  while (1) {
    char *username = NULL;
    size_t username_len = 0;
    char *serial = NULL;
    size_t serial_len = 0;
    size_t linesize = 0;

    printf("username:");
    linesize = getline(&username, &username_len, stdin);
    username_len = r_trim(username, linesize);
    if (username_len > 8) {
      free(username);
      puts("username less than 8 letter");
      continue;
    } else if (username_len == 0) {
      free(username);
      continue;
    }

    printf("serial:");
    linesize = getline(&serial, &serial_len, stdin);
    serial_len = r_trim(serial, linesize);
    if (serial_len != 16) {
      free(username);
      free(serial);
      puts("serial has 16 letters");
      continue;
    }

    char *correct = calculate(username, username_len);
    int rc = strncmp(serial, correct, 16);
    if (rc == 0) {
      free(correct);
      puts("Good job!");
      break;
    } else {
      puts("wrong pwd!");
    }
    free(username);
    free(serial);
    free(correct);
  }
  return 0;
}