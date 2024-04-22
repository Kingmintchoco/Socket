#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char* argv[]){
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    cout << addr1 << "\n";
    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr == INADDR_NONE) 
        cout << "Error\n";
    else
        cout << "Network ordered integer addr: " << conv_addr << "\n\n";
        
    cout << addr2 << "\n";
    conv_addr = inet_addr(addr2);
    if(conv_addr == INADDR_NONE)
        cout << "Error\n";
    else
        cout << "Network ordered integer addr: " << conv_addr << "\n";
    
    return 0;
}