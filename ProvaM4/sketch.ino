#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 2 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int pinoBotao = 18;  // Pino do botão
int estadoBotao = 0;  // Variável de estado do botão
bool botaoFoiPressionado = false;

const int pinoLDR = 4;  // Pino do LDR
int limiteLDR = 600;


void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(pinoBotao, INPUT); // Inicializa o pino do botão como input
  pinMode(pinoLDR, INPUT);

  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() == WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  /// Verifica estado do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  if (WiFi.status() == WL_CONNECTED) { // Se o ESP32 estiver conectado à Internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

    if (httpResponseCode > 0) {
      Serial.print("Código Resposta HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Erro: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  else {
    Serial.println("WiFi Desconectado");
  }
}
void escuro() {
  digitalWrite(led_verde, LOW); //garante que o led verde esteja desligado
  digitalWrite(led_vermelho, LOW); //garante que o led vermelho esteja desligado
  digitalWrite(led_amarelo, HIGH); //liga o led amarelo

  delay(1000); // intervalo de um segundo
  digitalWrite(led_amarelo, LOW);//desliga o amarelo

  delay(1000);//intervalo de 1 segundo
  digitalWrite(led_amarelo, HIGH);//liga o amarelo
}

void claro(){
        //
  digitalWrite(led_vermelho, LOW);//garante que o vermelho esteja desligado
  digitalWrite(led_amarelo, HIGH);//liga o amarelo
  digitalWrite(led_verde, LOW);//garante que o vermelho esteja desligado
 
  //2s com o sinal no amarelo
  delay(2000);
 
  // apaga o amarelo e liga o vermelho
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, HIGH);
  // 5s com o sinal vermelho
  delay(5000);  
 
  // apaga o vermelho e liga o verde
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_verde, HIGH);

  // 3 segundos com o sinal verde
  delay(3000);

  }
void loop() {
  delay(3000);//garante que os leds estejam desligados ao iniciar

  int ldrstatus = analogRead(pinoLDR);
  if (ldrstatus >= limiteLDR) {
    Serial.print("Está escuro, modo escuro");
    escuro();//chama a função do modo escuro

  } else {
    Serial.print("Está claro, modo claro");
    claro();//chama a função do modo claro
  }
}
