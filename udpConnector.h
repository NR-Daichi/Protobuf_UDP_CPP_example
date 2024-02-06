//
// Created by nr_daichi on 05.02.24.
//

#ifndef LEGROB_CPP_STATE_ESTIMATOR_UDP_CONNECTOR_H
#define LEGROB_CPP_STATE_ESTIMATOR_UDP_CONNECTOR_H

#include <netinet/in.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>


#include <stdio.h>
#include <string.h>

#include "addressbook.pb.h"

#define MAXLINE 1024;

class udpConnector {
public:
    udpConnector();
//private:
    // cliant: send, Server: recieve
    int sockfd_rcv, sockfd_snd;

    struct sockaddr_in clientaddr, serveraddre, sendingTo;
    const char* my_addr = "192.168.1.244";
    const char* peer_addr = "192.168.1.244";
    uint32_t my_port = 4242;
    uint32_t peer_port = 4242;

    void rcvMes();
    void sendMsg(int &num);


};


#endif //LEGROB_CPP_STATE_ESTIMATOR_UDP_CONNECTOR_H
