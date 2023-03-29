#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 2048
#define SERVER_IP "192.168.102.131"
#define SERVER_PORT 16555

using namespace std;

int main(){
    struct sockaddr_in servaddr;
    char buff[BUFF_SIZE];
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        cout << "Create socket error(" << errno << "): " << strerror(errno) << endl;
        return errno;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);
    if(connect(sockfd, (struct sockaddr *)& servaddr, sizeof(servaddr)) == -1){
        cout << "Connet error(" << errno <<"): " << strerror(errno) << endl;
        return errno;
    }
    cout << "Please input:" << endl;
    cin >> buff;
    send(sockfd, buff, strlen(buff), 0);
    bzero(buff, BUFF_SIZE);
    recv(sockfd, buff, BUFF_SIZE, 0);
    cout << buff << endl;
    close(sockfd);

    return 0;

}
