#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#include "ESP8266HTTPClient.h"
#include "WiFiClientSecureBearSSL.h"

class HttpsClient {
  public:
      String GET(String url, const uint8_t fingerprint[20]);
  private: 
};

extern HttpsClient httpsClient;

#endif
