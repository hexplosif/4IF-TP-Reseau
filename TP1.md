## TP1 - Programmation avec des Sockets en C

### Exercice 1

Fallait juste lire

### Exercice 2

```bash
$ ./socket_client_RFC 129.6.15.30 37
client starting
Time: Tue Oct 22 16:02:31 2024
```

### Exercice 3

Ca marche

### Exercice 4

```bash
$ ./socket_client_http 142.250.179.206 80
Headers:
HTTP/1.1 301 Moved Permanently
Location: http://www.google.com/
Content-Type: text/html; charset=UTF-8
Content-Security-Policy-Report-Only: object-src 'none';base-uri 'self';script-src 'nonce-FvEd1oSGE6ast5JZeTisTQ' 'strict-dynamic' 'report-sample' 'unsafe-eval' 'unsafe-inline' https: http:;report-uri https://csp.withgoogle.com/csp/gws/other-hp
Date: Tue, 22 Oct 2024 14:04:10 GMT
Expires: Thu, 21 Nov 2024 14:04:10 GMT
Cache-Control: public, max-age=2592000
Server: gws
Content-Length: 219
X-XSS-Protection: 0
X-Frame-Options: SAMEORIGIN
Connection: close

Content-Length: 219
No <title> found.
```

C'est vraiment pourri cette question

### Exercice 5

```bash
$ ./pasnmap 192.168.122.1
Scanning ports on 192.168.122.1...
Port 22 is open
Port 53 is open
Port 111 is open
Port 22443 is open
Port 32886 is open
Port 52206 is open
Port 53558 is open
```