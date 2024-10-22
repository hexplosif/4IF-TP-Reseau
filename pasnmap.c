#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define START_PORT 1
#define END_PORT 65535

void scan_ports(const char *ip_address) {
    int sockfd;
    struct sockaddr_in target;
    int port;

    printf("Scanning ports on %s...\n", ip_address);

    for (port = START_PORT; port <= END_PORT; port++) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Socket creation error");
            exit(1);
        }

        // Configuration de l'adresse de la cible
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, ip_address, &target.sin_addr);

        // Tentative de connexion pour voir si le port est ouvert
        if (connect(sockfd, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("Port %d is open\n", port);
        }

        close(sockfd);
    }
}

int main(int argc, char *argv[]) {
    struct hostent *he;
    struct in_addr **addr_list;
    char ip_address[100];

    if (argc != 2) {
        printf("Usage: %s <hostname or IP address>\n", argv[0]);
        exit(1);
    }

    // Résolution de l'hôte s'il s'agit d'un nom de domaine
    if ((he = gethostbyname(argv[1])) != NULL) {
        addr_list = (struct in_addr **)he->h_addr_list;
        strcpy(ip_address, inet_ntoa(*addr_list[0]));
    } else {
        // Sinon, on utilise l'adresse IP directement
        strcpy(ip_address, argv[1]);
    }

    // Lancement du scan des ports
    scan_ports(ip_address);

    return 0;
}
