#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <signal.h>

#define BUFF_SIZE 2048
#define DEFAULT_PORT 16555
#define MAX_LINK 2048

using namespace std;

int sockfd, connfd;

void stopServerRunning(int p){
    close(sockfd);
    cout << "Close server" << endl;
    exit(0);
}

int main(){
    struct sockaddr_in servaddr;
    char buff[BUFF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        cout << "Create socket error(" << errno << "): " << strerror(errno) << endl;
        return errno;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);
    if(bind(sockfd, (struct sockaddr*)& servaddr, sizeof(servaddr)) == -1){
        cout << "Bind error(" << errno << "): " << strerror(errno) << endl;
        return errno;
    }
    
    if(listen(sockfd, MAX_LINK) == -1){
        cout << "Listen error(" << errno << "): " << strerror(errno) << endl;
        return errno;
    }

    cout << "Listening..." << endl;
    signal(SIGINT, stopServerRunning);
    while(1){
        connfd = accept(sockfd, NULL, NULL);
        if(connfd == -1){
            cout << "Accept error(" << errno << "): " << strerror(errno) << endl;
            return errno;
        }
        bzero(buff, BUFF_SIZE);
        recv(connfd, buff, BUFF_SIZE - 1, 0);

        cout << buff << endl;

        send(connfd, buff, strlen(buff), 0);

        close(connfd);
    }

    return 0;
    
}
