/*
  REST Client Example

 This sketch connects to a website (http://www.robbie-remote.com)
 using an Arduino Ethernet shield or board and the Ethernet library.

 Data is sent in HTTP query args as Internet Of Things (IOT) messages.
 After sending, browse to http://www.robbie-remote.com to see your data.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 17 Oct 2015
 by Robert Cuthbertson <robbie@robbie-remote.com>
 This code was copied from the Ethernet Library Web Client example
 originally by these authors:
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>
#include <RESTClient.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Use DNS to find the server IP. Static server IP doesn't reduce sketch size.
// The server name is also used in the HTTP headers.
char server[] = "www.robbie-remote.com";

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 177);

// Initialize the REST Client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
RESTClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }

  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    // Send a sensor name (needs URL encoding) and value (integer or float).
    // This name 'My Arduino Sensor' and value '13' are just examples.
    // Put your sensor name and data here.
    client.send( F("My%20Arduino%20Sensor"), 13 );
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

