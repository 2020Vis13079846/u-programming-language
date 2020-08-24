#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  struct stat st;
  FILE *file;
  char *buffer;
  int size;
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }
  if (stat(argv[1], &st)) {
    perror(argv[1]);
    return 1;
  }
  file = fopen(argv[1], "r");
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);
  buffer = (char *)malloc(sizeof(char) * size);
  memset(buffer, 0, sizeof(char) * size);
  fread(buffer, size-1, sizeof(char), file);
  fclose(file);
  printf("%s\n", buffer);
  return 0;
}
