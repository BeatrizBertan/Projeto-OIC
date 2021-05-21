#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];   

const char* ssid = "********"; // Nome da Rede Wi-fi
const char* password = "**********"; // Senha da Rede Wi-fi
const char* mqtt_server = "broker.mqtt-dashboard.com"; // Broker MQTT

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
int value = 0; 

#include <pitches.h> //Biblioteca toneMelody - /examples/02.Digital/toneMelody/pitches.h

// Melodia do Buzzer Passivo
// Array da melodia
int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// Duração das notas
int durations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

int songLength = sizeof(melody)/sizeof(melody[0]);

// Declaração das variáveis
int buzzer = D2; // Porta Digital do Buzzer
int rele = D3; // Porta Digital do Relé
int gasSensor = A0; // Porta Analógica do Sensor de Gás
int limitSensor = 500; // Limite máximo do Nível do Sensor de Gás

void setup() {
  // Iniciando as variáveis
  pinMode(buzzer, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(gasSensor, INPUT);
  Serial.begin(9600);  

  // Iniciando conexão com wi-fi e mqtt
  setup_wifi();  

  client.setServer(mqtt_server, 1883);   
  client.setCallback(callback);         
}

// Configuração Wi-fi
void setup_wifi() {                          
  delay(10);                                                                                 
  Serial.println("");                                                                           
  Serial.print("Conectando com ");              
  Serial.println(ssid);                                                   

  WiFi.begin(ssid, password);               

  while (WiFi.status() != WL_CONNECTED) {     
    delay(500);                                                                
    Serial.print(".");                  
  }                  

  Serial.println("");    
  Serial.println("WiFi conectado");         
  Serial.println("IP: ");         
  Serial.println(WiFi.localIP()); 
}

// Define mensagens de retorno para o MQTT com seus tópicos
void callback(char* topic, byte* payload, unsigned int length) {                            
  Serial.print("Mensagem recebida [");                                                  
  Serial.print(topic);                                                                    
  Serial.print("] ");                                                                 
  for (int i = 0; i < length; i++) {                             
    Serial.print((char)payload[i]);
  }
  Serial.println("");                             
  if ((char)payload[0] == 'R') {                                                                 
    digitalWrite(rele, LOW);                            
    snprintf (msg, MSG_BUFFER_SIZE, "Lâmpada ligada");                                
    Serial.print("Publica mensagem: ");                   
    Serial.println(msg);                                
    client.publish("projeto/lamp", msg); // publica msg para o tópico projeto/lamp                    
  }
  Serial.println("");                                  
  if ((char)payload[0] == 'r') {                  
    digitalWrite(rele, HIGH);                      
    snprintf (msg, MSG_BUFFER_SIZE, "Lâmpada desligada");
    Serial.print("Publica mensagem: ");                             
    Serial.println(msg);                                               
    client.publish("projeto/lamp", msg); // publica msg para o tópico projeto/lamp               
  }
}

// Função de reconexão com MQTT
void reconnect() {                                                        
  while (!client.connected()) {                        
    Serial.print("Aguardando conexão MQTT...");  
    String clientId = "ESP8266Client";                                       
    clientId += String(random(0xffff), HEX);            
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");  
      client.subscribe("projeto/publisher");
    } else {       
      Serial.print(" falhou, rc = "); 
      Serial.print(client.state());
      Serial.println(" tente novamente em 5s"); 
      delay(5000);
    }
  }
}

// Laço de repetição do código
void loop() {
  int analogSensor = analogRead(gasSensor); // Variável de Leitura do Sensor de Gás
  if (isnan(analogSensor)){
    Serial.println("Erro na leitura do gás!");   
  }
  else {                              
    Serial.print("Nível de Gás: "); 
    Serial.println(analogSensor); 
    sprintf(msg,"%d",analogSensor); 
    client.publish("projeto/gas", msg); // Retorno quantitativo do Sensor para o MQTT                                          
  }
  if (analogSensor > limitSensor){ // Consição de Detecção de Gás acima do Limite Máximo
    digitalWrite(rele, HIGH);
    for (int thisNote = 0; thisNote < songLength; thisNote++){ // Acionamento do Buzzer                                                                                     
      snprintf (msg, MSG_BUFFER_SIZE, "Lâmpada desligada");
      Serial.print("Publica mensagem: ");                             
      Serial.println(msg);                                               
      client.publish("projeto/lamp", msg); // Desligamento da Lâmpada     
      int duration = 1000/ durations[thisNote];
      tone(buzzer, melody[thisNote], duration);
      // pause entre as notas
      int pause = duration * 1.3;
      delay(pause);
      // parar o buzzer
      noTone(buzzer);
      }
   }else{
  noTone(buzzer); // Caso não detecte gás, o buzzer permanece desligado
 }
 delay(200);

  // Condição para reconexão do MQTT, caso desconecte
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
