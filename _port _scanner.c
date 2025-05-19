// simple_port_scanner.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int scan_port(const char *ip, int port) {
    int sock;
    struct sockaddr_in target;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 0;
    }

    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    target.sin_addr.s_addr = inet_addr(ip);

    // Attempt connection
    int result = connect(sock, (struct sockaddr*)&target, sizeof(target));
    close(sock);

    return (result == 0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP> <max_port>\n", argv[0]);
        return 1;
    }

    const char *target_ip = argv[1];
    int max_port = atoi(argv[2]);

    printf("Scanning %s from port 1 to %d...\n", target_ip, max_port);

    for (int port = 1; port <= max_port; port++) {
        if (scan_port(target_ip, port)) {
            printf("Port %d is OPEN\n", port);
        }
    }

    printf("Scan complete.\n");
    return 0;
}




#bash
gcc simple_port_scanner.c -o portscanner
./portscanner 192.168.1.1 1000

#for example output

./portscanner 127.0.0.1 100


Scanning 127.0.0.1 from port 1 to 100...
Port 22 is OPEN
Port 80 is OPEN
Scan complete.
