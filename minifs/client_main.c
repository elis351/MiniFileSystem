#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  printf("You are now in Mini File System.\n");

  printf("\n\n"
         "You can do here:\n"
         "create_mfs mfs_name --- create new mfs file\n"
         "select mfs_name --- select current mfs file\n"
         "ls [dir_name] --- list of file in directory\n"
         "pwd --- show current path\n"
         "mkdir dir_name --- creating new directory\n"
         "cd dir_name --- change current directory\n"
         "rm file_name [r] --- remove file or directory (only with r flag!)\n"
         "load path_host path_mfs --- load file from host to mfs\n"
         "store path_mfs path_host --- store file from mfs to host\n");


  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in addr;
  inet_aton("127.0.0.1", &(addr.sin_addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(7795);

  int connection = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  if (0 > connection) {
    close(sock);
    return -1;
  }


  printf("$ ");

  char * line = NULL;
  size_t line_len = 0;

  char answer[4096];

  while (getline(&line, &line_len, stdin)) {
    write(sock, line, line_len);

    int read_bytes = read(sock, answer, 4096);

    if (read_bytes < 4096) answer[read_bytes] = '\0';
    printf("%s", answer);

    printf("\n");
    printf("$ ");
    fflush(stdout);
  }

  shutdown(sock, SHUT_RDWR);
  close(sock);

  return 0;
}
