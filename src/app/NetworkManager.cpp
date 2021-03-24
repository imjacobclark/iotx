#include "NetworkManager.h"

IPAddress local_IP(192, 168, 1, 136);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

void NetworkManager::connect(const char* ssid, const char* password){
  Serial.println("Network Manager starting...");

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  Serial.println("Activating WiFi Station Mode...");
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Connection failed, aborting network connection.");
      Serial.println();
      Serial.println("Warning, device not connected to a network.");
      return;
  }

  Serial.print("Successfully connected to network with local IP Address: ");
  Serial.println(WiFi.localIP());
}
