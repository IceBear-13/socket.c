#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#define HTML_FILE "index.html"
#define BUFFER_SIZE 1024


void handle_html(int client_fd, const char* filename){
  char buffer[BUFFER_SIZE]; // buffer overflow lmao
  struct stat file_stat;
  int file_fd, bytes_read;
  char *http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

  // Open the HTML file
  file_fd = open(filename, O_RDONLY);
  if(file_fd < 0){
    char* not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
    write(client_fd, not_found, strlen(not_found));
    return;
  }

  // Get file size
  fstat(file_fd, &file_stat);

  // Send HTTP header
  write(client_fd, http_header, strlen(http_header));

  // Send file content
  while ((bytes_read = read(file_fd, buffer, BUFFER_SIZE)) > 0) {
    write(client_fd, buffer, bytes_read);
  }
    
  close(file_fd);

}
