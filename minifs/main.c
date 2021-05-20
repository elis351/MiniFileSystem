#include <stdio.h>
#include <string.h>

#include "mfs_cli.h"

int main(int argc, char * argv[]) {
  if (argc < 2) {
    run_cli();
  } else if (strcmp(argv[1], "-s") == 0) {
    run_server_cli();
  } else {
    printf("Wrong args\n");
  }
  return 0;
}
