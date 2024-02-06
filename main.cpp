#include <iostream>
#include "addressbook.pb.h"
#include "udpConnector.h"

int main() {
    udpConnector obj;
    for(int i = 0 ; i<20 ; i++){
        obj.sendMsg(i);
        obj.rcvMes();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
