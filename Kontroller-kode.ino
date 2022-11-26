#include <LiquidCrystal_I2C.h> // Bibliotek for LCD-skjerm
#include <WiFi.h>              // Bibliotek for wifi-komandoer
#include <PubSubClient.h>      // Bibliotek for kommunikasjon med rasberry pi

#define BUTTON_PINUP 33       // GIOP33 pin tilknyttet bla-opp-knapp
#define BUTTON_PINDOWN 27     // GIOP37 pin tilknyttet bla-ned-knapp
#define BUTTON_PINSELECT 32   // GIOP32 pin tilknyttet velg-knapp

LiquidCrystal_I2C lcd(0x27, 16, 2); // Setter oppløsningen til LCD-skjermen


// Variabler brukt i koden:
int lastStateUP = LOW;                  // Den forrige verdien av knapp bla-opp
int currentStateUP;                     // Den nåværende verdien av knapp bla-opp
int lastStateDOWN = LOW;                // osv...
int currentStateDOWN;                   // 
int lastStateSELECT = LOW;              //  
int currentStateSELECT;                 // ...
int teller = 1;                         // Denne brukes til å bla opp og ned i menyen
int valg = 0;                           // Denne har bare to verdier, PÅ (1) eller AV (0). - 
                            // - Den brukes til å sjekke om man har trykken inn VALG-knappen  
int ruller = 0;                         // 
int rom;                                // 

// Variabler for kommunikasjon med rasberry pi:
const char* ssid = "RPI_G_19";          // Setter SSID-verdien til internettet
const char* password = "";              // Setter passordet til internettet
const char* mqtt_server = "10.42.0.1";  // Setter ip-adressen til internettet
WiFiClient espClient;                   
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


// Funksjon for å printe en streng mindre enn 17 bokstaver til LCD-skjerm:

void print_to_line(String message, int line, bool clear_screen) { 
  lcd.setCursor(0,line);                                          
  if (clear_screen == 1) {
    lcd.clear();
  }
  lcd.print(message);
}

// Funksjon for å lyse opp LED og printe romvalg til LCD:

void ROMVALG(int valg, int teller) {
   String tellerStr = String(teller);
   if (valg == 1 && ruller == 0){
    
    rom = teller;                                           // Lagrer romvalget
    ruller = 1;                                             // Denne sier at du når har valgt rom, og vil velge en tid                                           
    
    print_to_lcd("Rom " + String(teller) + " er valgt");
    delay(1000);
    reset_lcd2();
    
   }
        
   else if (valg == 1 && ruller == 1){
    ruller = 0;
    print_to_lcd("Tid " + tid() + ":00" + " er    valgt");
    String tellerStr = String(rom) +";" + tid();
    client.publish("python_mqtt/test", tellerStr.c_str());
    delay(1000);
    reset_lcd();
    teller = 1;
   }
}


// Funksjon for å printe strenger opp til størrelse 32 på LDC-skjerm:

void print_to_lcd(String message) {
  int message_length = message.length();
  String line1 = "";
  String line2 = "";

  if (message_length < 16) {
    for (int i = 0; i < message_length; i++) {
      line1 = line1 + message[i];
    }
  }
  else {
    for (int i = 0; i <= message_length; i++) {
      if (i < 16) {
        line1 = line1 + message[i];
      }
      else if (i < message.length()) {
        line2 = line2 + message[i];
      }
    }
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}


// Funksjon for å resette lcd-skjermen til romvalg:
void reset_lcd() {
  teller = 1;
  lcd.clear();
  print_to_line("Velg rom: ", 0, 1);                  // Printer "Select room" til lcd-skjerm 
  print_to_line("[" + String(teller) + "]", 1, 0);    // Printer startrom til lcd-skjermen
}


// Funksjon for å resette lcd-skjermen til tidvalg:
void reset_lcd2() {
  teller = 1;
  lcd.clear();
  print_to_line("Velg tid: ", 0, 1);                   // Printer "Select room" til lcd-skjerm 
  print_to_line("[" + tid()+ ":00" + "]", 1, 0);       // Printer starttid til lcd-skjermen
}

// Funksjon for tidsinkrement:
String tid() {
  switch (teller) {
    case 1:
    return "15";
    case 2:
    return "30";
    case 3:
    return "45";
    case 4:
    return "60";
  }
}




void setup() {
  
  lcd.init();                                         // Stater lcd-skjermen
  lcd.backlight();                                   
  reset_lcd();                                        // ...
  
  pinMode(BUTTON_PINUP, INPUT_PULLUP);                // Setter alle pinoutsa til pull_up modus 
  pinMode(BUTTON_PINDOWN, INPUT_PULLUP);              //
  pinMode(BUTTON_PINSELECT, INPUT_PULLUP);            // Pull_up pinnene vil være HIGH når knappen ikke er trykket inn, og LOW når den er
  
  Serial.begin(115200); 

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Kode som skal ittereres:
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  
  currentStateUP = digitalRead(BUTTON_PINUP);                   // Leser av verdiene til hver pin (HIGH eller LOW)
  currentStateDOWN = digitalRead(BUTTON_PINDOWN);               //
  currentStateSELECT = digitalRead(BUTTON_PINSELECT);           // ...
  
  
  delay(30);

  if (lastStateSELECT == HIGH && currentStateSELECT == LOW){    // Hvis valg-knappen er trykket:
    valg = 1;                                                   // Setter valg til PÅ (1)

  }
  
  if (lastStateUP == HIGH && currentStateUP == LOW){            // Hvis opp-knappen er trykket:
    
    if (teller < 4) {                                           // Avgjør hvilken vei telleren skal telle
      teller += 1;
    }
    else
      teller = 1;

    print_to_line("        ", 1, 0);                            // Resetter linje 2 i skjermen
    
    if (ruller == 0) {
      print_to_line("[" + String(teller) + "]", 1, 0);          // Printer oppdatert romnummer til lcd-skjerm
    }
    else if (ruller == 1) {
      print_to_line("[" + tid() + ":00" + "]", 1, 0);           // Printer oppdatert tid til lcd-skjerm
    }
  }
  

  if (lastStateDOWN == HIGH && currentStateDOWN == LOW){        // Hvis ned-knappen er trykket:
    
    if (teller > 1) {                                           // Avgjør hvilken vei telleren skal telle
      teller -= 1;
    }
    else
      teller = 4;

    print_to_line("        ", 1, 0);                            // Nullstiller linje 2 i skjermen

    if (ruller == 0) {
      print_to_line("[" + String(teller) + "]", 1, 0);          // Printer oppdatert romnummer til lcd-skjerm
    }
    else if (ruller == 1) {
      print_to_line("[" + tid() + ":00" + "]", 1, 0);           // Printer oppdatert tid til lcd-skjerm
    } 
  }
  
  ROMVALG(valg, teller);
  
  lastStateUP = currentStateUP;                 // Nullstiller alle varibalnene før koden kjøres på nytt
  lastStateDOWN = currentStateDOWN;             // osv ...
  lastStateSELECT = currentStateSELECT;         //
  valg = 0;                                     // ...
}  
