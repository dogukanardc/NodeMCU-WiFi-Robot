#include <L298N.h>
#include <ESP8266WiFi.h>


//pin definition
#define ENA 14
#define IN1 12
#define IN2 13
#define IN3 15
#define IN4 3
#define ENB 1

//create a motor instance
L298N motorSOL(ENA, IN1, IN2);
L298N motorSAG(ENB, IN3, IN4);

const char* ssid = "**YOUR-WIFI-SSID**";
const char* password = "**YOUR-WIFI-PASSWORD**";

//initial speed
unsigned short theSpeed = 255;
int basla = 0;

WiFiServer server(80);

void setup() {
  motorSOL.setSpeed(theSpeed);
  motorSAG.setSpeed(theSpeed);
  motorSOL.stop();
  motorSAG.stop();
WiFi.begin(ssid, password);
IPAddress ip(192,168,1,15);   
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0);   
WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
server.begin();
}

void loop() {
  wifi();
  if (basla == 1){
    ileri();
 delay(1000);
 dur();
 delay(1000);
 sol();
 delay(1000);
 ileri();
 delay(3000);
 dur();
 delay(1000);
 tamtur();
 delay(750);
 dur();
 delay(500);
 ileri();
 delay(3000);
 dur();
 delay(500);
 sag();
 delay(1000);
 ileri();
 delay(1000);
 dur();
 delay(500);
 tamtur();
 delay(750);
 dur();
 basla = 0;
    }
}

void wifi(){
   WiFiClient client = server.available();
if (!client) {
return;
}
 
// client ın bir data gondermesini bekliyoruz
Serial.println("new client");
while(!client.available()){
delay(1);
}
 
// gelen istekleri okuyoruz
 String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
 
int value = LOW;
if (request.indexOf("/START") != -1) {
  basla = 1;
  client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");

client.print("OK");

delay(1);
client.println("</html>");
Serial.println("Client disonnected");
Serial.println("");
  }
else {
  client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");
 
client.print("Robot Suanda: ");
 
if(value == HIGH) {
client.print("ACIK");
} else {
client.print("KAPALI");
}
client.println("");
client.println("<a href=\"/START\"\"><button>BASLAT </button></a>");
client.println("</html>");
 
delay(1);
Serial.println("Client disonnected");
Serial.println("");
  }
}

void ileri(){
  motorSOL.backward();
  delay(10);
  motorSAG.forward();
}

void geri(){
  motorSOL.forward();
  motorSAG.backward();
}

void tamtur(){
  motorSOL.forward();
  motorSAG.forward();
  }

void sol(){
  motorSOL.forward();
  motorSAG.forward();
  delay(400);
  motorSOL.stop();
  motorSAG.stop();
  }

void sag(){
  motorSOL.backward();
  motorSAG.backward();
  delay(400);
  motorSOL.stop();
  motorSAG.stop();
  }
void dur(){
  motorSOL.stop();
  motorSAG.stop();
  }
