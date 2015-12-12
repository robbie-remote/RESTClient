#ifndef RESTClient_h
#define RESTClient_h

#include <Ethernet.h>


class RESTClient : public EthernetClient {

public:
  virtual int  connect(const char *host, uint16_t port);
  void         send(const              String &name,   int value);
  void         send(const              String &name, float value);
  void         send(const __FlashStringHelper *name,   int value);
  void         send(const __FlashStringHelper *name, float value);


private:
  const char*   my_host;

  void printMAC();
  void printHTTP();
  void printHeaders();

};

#endif
