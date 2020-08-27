#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *read_file(char *filename) {
  struct stat st;
  FILE *file;
  char *buffer;
  int size;
  if (stat(filename, &st)) {
    perror(filename);
    exit(1);
  }
  file = fopen(filename, "r");
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);
  buffer = (char *)malloc(sizeof(char) * size);
  memset(buffer, 0, sizeof(char) * size);
  fread(buffer, size-1, sizeof(char), file);
  fclose(file);
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 0;
  }
  char *buffer = read_file(argv[1]);
  printf("%s\n", buffer);
  return 0;
}
