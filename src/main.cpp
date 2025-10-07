#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

const char* ssid = "Teste";
const char* password = "teste123";

const int int1 = 13; 
const int int2 = 12;
const int int3 = 27;
const int int4 = 26;

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    // Monta o sistema de arquivos SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Erro ao montar o SPIFFS");
        return;
    }

    // Inicializa os pinos dos LEDs
    pinMode(int1, OUTPUT);
    pinMode(int2, OUTPUT);
    pinMode(int3, OUTPUT);    
    pinMode(int4, OUTPUT);


    digitalWrite(int1, LOW);
    digitalWrite(int2, LOW);
    digitalWrite(int3, LOW);
    digitalWrite(int4, LOW);

    // Conecta ao WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    // Define as rotas do servidor
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->send(SPIFFS, "/index.html", "text/html"); 
    });

    //Acionamentos int1
    server.on("/int1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int1, HIGH);
        request->send(200, "text/plain", "int 1 ligado");
    });

    server.on("/int1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int1, LOW);
        request->send(200, "text/plain", "int1 desligado");
    });


    //Acionamentos int2
    server.on("/int2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int2, HIGH);
        request->send(200, "text/plain", "int2 ligado");
    });

    server.on("/int2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int2, LOW);
        request->send(200, "text/plain", "int2 desligado");
    });


    //Acionamentos int3
    server.on("/int3/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int3, HIGH);
        request->send(200, "text/plain", "int3 ligado");
    });

    server.on("/int3/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int3, LOW);
        request->send(200, "text/plain", "int3 desligado");
    });

    //Acionamentos int4
    server.on("/int4/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int4, HIGH);
        request->send(200, "text/plain", "int4 ligado");
    });

    server.on("/int4/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(int4, LOW);
        request->send(200, "text/plain", "int4 desligado");
    });

    // Inicia o servidor
    server.begin();
}

void loop() {
    // O loop pode permanecer vazio, pois o servidor é assíncrono
}
