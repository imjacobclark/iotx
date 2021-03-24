#include "HttpsClient.h";

String HttpsClient::GET(String url, const uint8_t fingerprint[20]){
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint);

  HTTPClient https;

  if (https.begin(*client, url)) {
    String payload;
    int httpCode = https.GET();

    if (httpCode > 0) {
      payload = https.getString();
    }

    https.end();

    return payload;
  } else {
    return "";
  }
}
