#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char* ssid = "Teste";
const char* password = "teste123";

const int int1 = 13; // Pino do LED 1
const int int2 = 12; // Pino do LED 2
const int int3 = 27;
const int int4 = 25;

AsyncWebServer server(80);

const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <title>Controle de LEDs</title>
        <style>
            body { 
                font-family: Arial, sans-serif; 
                text-align: center; 
                margin: 0;  /* Remove qualquer margem da página */
                height: 100vh;  /* Faz o body ocupar 100% da altura da tela */
                display: flex;   /* Define o display como flex */
                justify-content: center;  /* Centraliza os elementos horizontalmente */
                align-items: center;  /* Centraliza os elementos verticalmente */
                background-color: #f0f0f0;  /* Adiciona uma cor de fundo clara */
            }

            .container { 
                display: flex;  /* Flexbox */
                flex-direction: column;  /* Coloca os botões em colunas */
                align-items: center;  /* Centraliza os botões dentro da container */
                gap: 20px;  /* Espaçamento entre as linhas */
            }
            
            .row { 
                display: flex;
                justify-content: center;  /* Alinha os botões na horizontal dentro da linha */
                gap: 20px;  /* Espaçamento entre os botões */
            }

            button {
                padding: 20px 40px;
                font-size: 20px;
                color: white;
                border: none;
                cursor: pointer;
                border-radius: 5px;
                background-color: #007BFF; /* Azul */
                transition: background-color 0.3s ease;  /* Suaviza a transição de cor */
            }

            button:hover {
                background-color: #0056b3;  /* Cor de fundo ao passar o mouse */
            }

            /* Botões de posição específica */
            .normal { 
                background-color: #007BFF;  /* Azul */
            }

            .row.centered {
                justify-content: space-between;  /* Distribui os botões uniformemente */
                width: 80%;  /* Aumenta a largura para os botões do centro */
            }

            /* Responsividade: para telas menores, os botões são redimensionados */
            @media (max-width: 600px) {
                button {
                    font-size: 16px;
                    padding: 15px 30px;
                }

                .container {
                    gap: 10px;  /* Reduz o espaçamento entre as linhas em telas pequenas */
                }
            }
        </style>
    </head>

    <body>

        <div class="container">
            <div class="row">
                <button id="up" class="normal" onclick="handleAction('up')">C</button>
            </div>

            <div class="row">
                <button id="left" class="normal" onclick="handleAction('left')">E</button>
                <button id="center" class="normal" onclick="handleAction('center')">O</button>
                <button id="right" class="normal" onclick="handleAction('right')">D</button>
            </div>

            <div class="row">
                <button id="down" class="normal" onclick="handleAction('down')">B</button>
            </div>
        </div>

        <script>
            // Função para alternar os LEDs conforme a direção
            function handleAction(direction) {
                // Exibe qual int foi acionado e envia os pedidos HTTP
                switch (direction) {
                    case 'up':
                        alert('INTs 1 e 3 foram acionados');
                        toggleLED(1, 'on');
                        toggleLED(3, 'on');
                        toggleLED(2, 'off');
                        toggleLED(4, 'off');
                        break;
                    case 'down':
                        alert('INTs 2 e 4 foram acionados');
                        toggleLED(2, 'on');
                        toggleLED(4, 'on');
                        toggleLED(1, 'off');
                        toggleLED(3, 'off');
                        break;
                    case 'left':
                        alert('INT 2 foi acionado');
                        toggleLED(1, 'on');
                        toggleLED(2, 'off');
                        toggleLED(3, 'off');
                        toggleLED(4, 'off');
                        break;
                    case 'right':
                        alert('INT 3 foi acionado');
                        toggleLED(3, 'on');
                        toggleLED(1, 'off');
                        toggleLED(2, 'off');
                        toggleLED(4, 'off');
                        break;
                    case 'center':
                        alert('Todos foram zerados');
                        toggleLED(1, 'off');
                        toggleLED(2, 'off');
                        toggleLED(3, 'off');
                        toggleLED(4, 'off');
                        break;
                }
            }

            // Função para fazer o HTTP request de acionamento dos LEDs
            function toggleLED(int, state) {
                fetch('/int' + int + '/' + state)
                    .then(response => response.text())
                    .catch(error => console.error('Erro ao acionar o LED:', error));
            }
        </script>
    </body>
</html>

)rawliteral";

void setup() {
    Serial.begin(115200);

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
        request->send(200, "text/html", html);
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
