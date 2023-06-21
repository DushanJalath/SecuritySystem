#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

const char* ssid = "abc";
const char* password = "11112222";
String parameterValue;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);

        int parameterStart = request.indexOf("1");  // Adjust "parameter=" length
        int parameterEnd = request.indexOf(" ", parameterStart);

        // Extract the parameter value
        parameterValue = request.substring(parameterStart, parameterEnd);

        Serial.print("Parameter value: ");
        Serial.println(parameterValue);
        // Here, you can process the request and perform actions accordingly

        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        client.println("<html><body><h1>Request received</h1></body></html>");

        break;
      }
    }

    // client.stop();
    // Serial.println("Client disconnected");
  }
}

String returnValue(){
  return parameterValue;
}