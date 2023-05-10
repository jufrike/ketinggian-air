
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
#define led1 10
#define led2 9
#define led3 8
#define echoPin 7
#define trigPin 6
#define buzzer  12
long durasi;
int jarakCm;
int air;
String data;
char c;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin (115200);
  mySerial.begin(115200);
  lcd.begin(16,2);
  lcd.clear();
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
pinMode(buzzer, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  lcd.init();
lcd.backlight();
lcd.blink_on();
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
 digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
 digitalWrite (trigPin, LOW);
 durasi = pulseIn (echoPin, HIGH);
 jarakCm= (durasi/2) / 29.1;
 air = 25-jarakCm;
 delay(400);

 if((jarakCm > 15) && (jarakCm<=25)){
  
  digitalWrite (led1, HIGH);
  digitalWrite (led2, LOW);
  digitalWrite (led3, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tinggi Air: ");
  lcd.print(air);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("AMAN");
 }
 if((jarakCm > 6) && (jarakCm<=14)){
  digitalWrite (led1, LOW);
  digitalWrite (led2, HIGH);
  digitalWrite (led3, LOW);
  digitalWrite(buzzer,HIGH);
  tone(12,1500);
  delay(50);
  noTone(12);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tinggi Air: ");
  lcd.print(air);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("WASPADA");
 }
 if((jarakCm > 1) && (jarakCm<=5)){
  digitalWrite (led1, LOW);
  digitalWrite (led2, LOW);
  digitalWrite (led3, HIGH);
  tone(12,1000);
  delay(300);
  noTone(12);
  delay(50);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tinggi Air: ");
  lcd.print(air);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("BAHAYA");
 }
   while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }  
   if (data.length()>0) {
    Serial.println(data);
    if (data == "CEK") {
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
 digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
 digitalWrite (trigPin, LOW);
 durasi = pulseIn (echoPin, HIGH);
 jarakCm= (durasi/2) / 29.1;
 air = 25-jarakCm;
      Serial.println(air);
      mySerial.print(air);
    }
    data= "";
  }

 
  // put your main code here, to run repeatedly:

}
