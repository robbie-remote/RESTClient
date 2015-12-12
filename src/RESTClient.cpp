
#include "RESTClient.h"
#include <utility/w5100.h>


int RESTClient::connect(const char *host, uint16_t port)
{
    my_host = host;
    return EthernetClient::connect(host, port);
}

void RESTClient::printMAC() {
  uint8_t mac[6];
  W5100.getMACAddress( mac );
  for (int i = 0; i < 5; i++) {
    print(mac[i], HEX);
    print(F(":"));
  }
  print(mac[5], HEX);
}

void RESTClient::printHTTP() 
{
    // Send an HTTP request:
    print(F("GET /?IOTMessage&mac="));
    printMAC();
    print(F("&name="));
}

void RESTClient::printHeaders()
{
    println(F(" HTTP/1.1"));

    print(F("Host: "));
    println(my_host);

    print(F("User-Agent: RESTClient/1.0 Arduino/"));
    #if   defined (__AVR_ATmega32U4__)
        println(F("atmega32u4"));
    #elif defined (__AVR_ATmega1280__)
        println(F("atmega1280"));
    #elif defined (__AVR_ATmega2560__)
        println(F("atmega2560"));
    #elif defined (__AVR_ATmega328P__)
        println(F("atmega328p"));
    #elif defined (__AVR_ATmega168__)
        println(F("atmega168"));
    #elif defined (__AVR_ATmega8__)
        println(F("atmega8"));
    #else
        println(F("unknown"));
    #endif

    println(F("Connection: close"));
    println();
}

void RESTClient::send(const String &name, int value)
{
    printHTTP();
    print(name);
    print(F("&value="));
    print(value);
    printHeaders();
}

void RESTClient::send(const String &name, float value)
{
    printHTTP();
    print(name);
    print(F("&value="));
    print(value);
    printHeaders();
}

void RESTClient::send(const __FlashStringHelper *name, int value)
{
    printHTTP();
    print(name);
    print(F("&value="));
    print(value);
    printHeaders();
}

void RESTClient::send(const __FlashStringHelper *name, float value)
{
    printHTTP();
    print(name);
    print(F("&value="));
    print(value);
    printHeaders();
}
