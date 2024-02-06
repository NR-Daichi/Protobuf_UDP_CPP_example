//
// Created by nr_daichi on 05.02.24.
//

#include "udpConnector.h"
#include <errno.h>

char rcv_buffer[1024];
char send_buffer[1024];

udpConnector::udpConnector() {
    // set up reciever
    memset(&clientaddr, 0, sizeof(clientaddr));

    /** --------------- **/
    /** set up receiver **/
    /** -------------  **/
    sockfd_rcv = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_rcv< 0){
        std::cout<<"[udpConnector:Error] socket creation failed" <<std::endl;
        exit(EXIT_FAILURE);
    }

    memset(&serveraddre, 0, sizeof(serveraddre));
    serveraddre.sin_family = AF_INET; // iPv4;
    serveraddre.sin_port = htons(my_port);
    serveraddre.sin_addr.s_addr = inet_addr(my_addr);
    //    serveraddre.sin_addr.s_addr = INADDR_ANY;

    int rev = bind(sockfd_rcv, (const struct sockaddr *)&serveraddre, sizeof(serveraddre));
    if(rev < 0){
        std::cout<<"[udpConnector::Error] "<<rev<<"  bind failed "<< errno <<std::endl;
        exit(EXIT_FAILURE);
    }


    /** --------------- **/
    /** set up sender  **/
    /** -------------  **/
    sockfd_snd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_snd< 0){
        std::cout<<"[udpConnector:Error] socket creation failed" <<std::endl;
        exit(EXIT_FAILURE);
    }

    memset(&sendingTo, 0, sizeof(sendingTo));
    sendingTo.sin_family = AF_INET;
    sendingTo.sin_port = htons(peer_port);
    sendingTo.sin_addr.s_addr = inet_addr(peer_addr);

}

void udpConnector::rcvMes() {
    tutorial::Person::PhoneNumber phone_number;
    int data;
    socklen_t len;
    len = sizeof(clientaddr);
    data = recvfrom(sockfd_rcv, (char *)rcv_buffer, sizeof(rcv_buffer), 0, (struct sockaddr *) &clientaddr, &len);
    /** data is the length of buffer and rcv_buffer is point to the message **/

    if(data > 0 ){
        phone_number.ParseFromString(rcv_buffer);
        std::cout<<"[receve message] number: "<<phone_number.number()<<std::endl;
    }
}

void udpConnector::sendMsg(int &num) {
    //encode message
    tutorial::Person person;
    std::string number = "123";
    tutorial::Person::PhoneNumber phone_number;// = person.add_phones();
    phone_number.set_number(number);
    phone_number.set_type(tutorial::Person::PHONE_TYPE_HOME);
    phone_number.set_number(std::to_string(num));

    std::string array;
    phone_number.SerializeToString(&array);

    int buffer_length=strlen(array.c_str());

    int sent_byte = sendto(sockfd_snd, array.data(), strlen(array.c_str()), 0, (const struct sockaddr *)&sendingTo, sizeof(sendingTo));
    if(sent_byte != buffer_length){
        std::cout<<"[udpConnector::Error] sending message failure "<<errno<<std::endl;
        exit(EXIT_FAILURE);
    }
}


