#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0);
Servo window;
Servo door;
#define LED 13
#define LED2 5
#define buzzer 12
#define relay 11
#define fan1 10
#define fan2 9
int photocell =0;
int steam =0 ;
int gas=0;
char data;
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Smart Home");
  window.attach(8);
  window.write(90);
  door.attach(9);
  door.write(0);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()>0){
    data = Serial.read();
  }

  if( data == 'a'){
    digitalWrite(LED,HIGH);
    newLine("Lights on");
  }
  else if(data == 'b'){
    digitalWrite(LED,LOW);
    newLine("Lights off");
  }
  else if( data == 'p'){
    digitalWrite(LED2,HIGH);
    newLine("Lights 2 on");
  }
  else if(data == 'q'){
    digitalWrite(LED2,LOW);
    newLine("Lights 2 off");
  }
  else if( data == 'e'){
    digitalWrite(buzzer,HIGH);
    newLine("Buzzer is on");
  }
  else if ( data == 'g'){
    digitalWrite(buzzer,LOW);
    newLine("Buzzer is off");
  }
  else if (data == 'f'){
    digitalWrite(buzzer,HIGH);
    newLine("Buzzer is on");
  }
  else if (data == 'c'){
    digitalWrite(relay,HIGH);
    newLine("Relay is on");
  }
  else if (data == 'd'){
    digitalWrite(relay,LOW);
    newLine("Relay is off");
  }
  else if ( data == 'r'){
    digitalWrite(fan1,HIGH);
    digitalWrite(fan2,LOW);
    newLine("Fan is on");
  }
  else if ( data == 's'){
    digitalWrite(fan1,LOW);
    digitalWrite(fan2,LOW);
    newLine("Fan is off");
  }
  else if ( data == 'h'){
    photocell = analogRead (A1);
    newLine("PC:"+photocell);
    if(photocell<900){
      window.write(180);
    }
    else{
      window.write(60);
    }
  }
  else if ( data == 'n'){
    window.write(180);
    newLine("Window is open");
  }
  else if ( data == 'o'){
    window.write(60);
    newLine("Window is off");
  }
  else if (data=='l'){
    door.write(110);
    newLine("Door is open");
  }
  else if(data=='m'){
    door.write(0);
    newLine("Door is closed");
  }
  else if ( data == 'k'){
    steam = analogRead(A2);
    newLine("Steam:"+steam);
    if(steam > 900){
      door.write(0);
      window.write(60);
    }
  }
  else if (data =='S'){
    newLine("Sensor is off");
  }
  else if (data == 'i'){
    gas = analogRead(A0);
    newLine("Gas:"+gas);    
    if(gas>450){
      digitalWrite(buzzer,HIGH);
      delay(500);
    }
    else{
      digitalWrite(buzzer,LOW);
    }
  }
}

void newLine(String word){
  lcd.cursor(0,1);
  lcd.print(word);
  lcd.setBacklight(1)
  delay(500);
  lcd.setBacklight(0);
  delay(500);  
}
