#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define RESPONSE_SIZE 10240 // Taille du buffer de réponse

// Fonction pour extraire le contenu de la balise <title>
void extract_title(const char *html) {
    char *title_start = strstr(html, "<title>");
    char *title_end = strstr(html, "</title>");

    if (title_start != NULL && title_end != NULL && title_end > title_start) {
        // Avancer le pointeur pour commencer après <title>
        title_start += strlen("<title>");
        // Imprimer le contenu entre <title> et </title>
        printf("Title: ");
        while (title_start < title_end) {
            putchar(*title_start);
            title_start++;
        }
        printf("\n");
    } else {
        printf("No <title> found.\n");
    }
}

// Fonction pour extraire le Content-Length à partir des headers HTTP
int get_content_length(const char *response) {
    char *content_length_str = strstr(response, "Content-Length: ");
    if (content_length_str) {
        content_length_str += strlen("Content-Length: ");
        return atoi(content_length_str);
    }
    return -1;
}

// Fonction pour afficher les headers
void print_headers(const char *response) {
    char *header_end = strstr(response, "\r\n\r\n");
    if (header_end) {
        // Afficher tous les headers
        printf("Headers:\n");
        while (response < header_end) {
            putchar(*response);
            response++;
        }
        printf("\n\n");
    } else {
        printf("No headers found.\n");
    }
}

int main(int argc, char **argv) {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char response[RESPONSE_SIZE];
    struct sockaddr_in serv_addr;
    int bytes_received;
    int total_received = 0;

    if (argc != 3) {
        printf("Usage: %s server_ip port\n", argv[0]);
        exit(1);
    }

    // Initialisation du socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(1);
    }

    // Configuration de l'adresse du serveur
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); // Convertir le port en format réseau
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(1);
    }

    // Connexion au serveur
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Envoi de la requête HTTP GET
    char http_request[BUFFER_SIZE];
    snprintf(http_request, BUFFER_SIZE, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);

    send(sockfd, http_request, strlen(http_request), 0);

    // Lecture de la réponse
    while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
        if (total_received + bytes_received >= RESPONSE_SIZE) {
            printf("Response too large\n");
            break;
        }
        memcpy(response + total_received, buffer, bytes_received);
        total_received += bytes_received;
    }
    response[total_received] = '\0'; // Null-terminate the response

    // Séparation du header et du body
    char *body = strstr(response, "\r\n\r\n");
    if (body) {
        body += 4; // Skip the \r\n\r\n
    }

    // Afficher les headers
    print_headers(response);

    // Afficher la longueur du body
    int content_length = get_content_length(response);
    if (content_length > 0) {
        printf("Content-Length: %d\n", content_length);
    } else {
        printf("Content-Length not found.\n");
    }

    // Extraire et afficher le titre
    if (body) {
        extract_title(body);
    } else {
        printf("No body found.\n");
    }

    // Fermer le socket
    close(sockfd);

    return 0;
}
