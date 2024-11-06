#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char* ssid = "Teste";
const char* password = "teste123";

const int led1Pin = 26; // Pino do LED 1
const int led2Pin = 27; // Pino do LED 2

AsyncWebServer server(80);

const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Controle de LEDs</title>
    <style>
        body { font-family: Arial; 
        text-align: center; 
        margin-top: 50px; }
        
        button { padding: 10px 20px; 
        font-size: 20px; }
    </style>
</head>
<body>
    <h1>Controle de LEDs</h1>
    <h2>LED 1</h2>
    <button onclick="toggleLED(1, 'on')">Ligar</button>
    <button onclick="toggleLED(1, 'off')">Desligar</button>
    <h2>LED 2</h2>
    <button onclick="toggleLED(2, 'on')">Ligar</button>
    <button onclick="toggleLED(2, 'off')">Desligar</button>

    <script>
        function toggleLED(led, state) {
            fetch('/led' + led + '/' + state)
                .then(response => response.text())
                .then(data => alert(data));
        }
    </script>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);

    // Inicializa os pinos dos LEDs
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);

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
        request->send(200, "text/html", html);
    });

    server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(led1Pin, HIGH);
        request->send(200, "text/plain", "LED 1 ligado");
    });

    server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(led1Pin, LOW);
        request->send(200, "text/plain", "LED 1 desligado");
    });

    server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(led2Pin, HIGH);
        request->send(200, "text/plain", "LED 2 ligado");
    });

    server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(led2Pin, LOW);
        request->send(200, "text/plain", "LED 2 desligado");
    });

    // Inicia o servidor
    server.begin();
}

void loop() {
    // O loop pode permanecer vazio, pois o servidor é assíncrono
}
