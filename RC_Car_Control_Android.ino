

#include <ESP8266WiFi.h>
#include <Servo.h>
Servo servo_1;
const char* ssid = "asad";
const char* password = "141331044";

WiFiServer server(80);

void putar_30(void)
{   
  servo_1.write(0);
  delay(500);  
   
}
void putar_60(void)
{
   servo_1.write(90);
  delay(500);
  
}
void putar_90(void)
{
   servo_1.write(180);
  delay(500);
  
}

void left_f(void)
{
   digitalWrite(D5, 255);
   digitalWrite(D6, 0);
}
void right_f(void)
{
   digitalWrite(D5, 0);
   digitalWrite(D6, 255);
}
void forward(void)
{
      digitalWrite(D7, 255);

      digitalWrite(D8, 0);
}
void backward(void)
{
    digitalWrite(D7, 0);
   digitalWrite(D8, 255);
}

void move_forward(void)
{
  forward();
}
void move_backward(void)
{
  backward();
}

void move_left(void)
{
  left_f();
  forward();
}

void move_right(void)
{
  right_f();
  forward();
}
void move_putar_30(void)
{
  putar_30();
  
}
void move_putar_60(void)
{
  putar_60();
  
}
void move_putar_90(void)
{
  putar_90();
  
}
void stop_all_now(void)
{
    digitalWrite(D5, 0);
   digitalWrite(D6, 0);
    digitalWrite(D7, 0);
   digitalWrite(D8, 0);
   
}




void setup() {

  Serial.begin(115200);
  delay(10);
  servo_1.attach(16);
  servo_1.write(0);
 
  
  delay(0);
  
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  

 stop_all_now();

   WiFi.begin(ssid, password);



 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
    
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  }
 Serial.println("");
 Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
Serial.println("Server started");

  // Print the IP address

 Serial.println(WiFi.localIP());








}

void loop()
{
// stop_all_now();

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
//  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
//  Serial.println(req);
  client.flush();
  
  // Match the request
  int val=0;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else if (req.indexOf("/gpio/2") != -1)
    val = 2;
  else if (req.indexOf("/gpio/3") != -1)
    val = 3;
  else if (req.indexOf("/gpio/4") != -1)
    val = 4;
  else if (req.indexOf("/gpio/5") != -1)
    val = 5;
  else if (req.indexOf("/gpio/6") != -1)
    val = 6;
  else if (req.indexOf("/gpio/7") != -1)
    val = 7; 
  else {
   // Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request


  

  if(val==1) move_forward();
  if(val==2) move_backward();
  if(val==3) move_left();
  if(val==4) move_right();
  if(val==5) move_putar_30();
  if(val==6) move_putar_60();
  if(val==7) move_putar_90();
  if(val==0) stop_all_now();
  if ((val<=0) || (val>=8))
  stop_all_now();
  val=0;
  
 // digitalWrite(LED_BUILTIN, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);

}
























/*
  
 move_forward();
 delay(1000);
  move_backward();
  delay(1000);
  move_left();
  delay(1000);
  move_right();
  delay(1000);
 
 
   
}*/
