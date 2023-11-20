#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include "netdb.h"
#include "arpa/inet.h"
#include <fcntl.h> // for file operations
#include <errno.h> // for error handling
#include <stdbool.h> // for boolean type

#define PORT 6969

int main() {
    int serverDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    char buffer[100], file[1000];
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(PORT);
    connect(serverDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    while (1) {
        printf("File name : ");
        scanf("%s", buffer);

        // Check if the file exists on the server
        int fileExists = access(buffer, F_OK);

        if (fileExists == 0) {
            // Send the file name to the server
            send(serverDescriptor, buffer, strlen(buffer) + 1, 0);

            printf("%s\n", "File Output : ");
            recv(serverDescriptor, &file, sizeof(file), 0);
            printf("%s", file);
        } else {
            printf("Error: File '%s' does not exist on the server.\n", buffer);
        }
    }

    return 0;
}
