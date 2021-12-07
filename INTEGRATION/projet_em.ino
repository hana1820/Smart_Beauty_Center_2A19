#include <deprecated.h>
#include <SPI.h> // SPI
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>


#define SS_PIN 10
#define RST_PIN 9
    
// Déclaration 
MFRC522 rfid(SS_PIN, RST_PIN); 

// Tableau contentent l'ID
byte nuidPICC[4]; 
char data;
String UID;


const byte TRIGGER = 6;
const byte ECHO = 8;
const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 100;
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);


  digitalWrite(11, LOW);
  pinMode(TRIGGER, OUTPUT);
  digitalWrite(TRIGGER, LOW);
  pinMode(ECHO, INPUT);

   // Init RS232
  Serial.begin(9600);

  // Init SPI bus
  SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init(); 
}

 void loop() 
{

  // put your main code here, to run repeatedly:
  long measure = pulseIn(ECHO, HIGH, MEASURE_TIMEOUT);
  float distance_mm = measure / 2.0 * SOUND_SPEED;
    
 
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;
     // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;
    
  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

Serial.write(nuidPICC[0]);
delay(500);


   if(Serial.available())
  {
     data=Serial.read();
    if(data!='1')
  {
  
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      //digitalWrite(TRIGGER, HIGH);
 
      lcd.init();
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("ACCES REFUSE");
      delay(1000);
      digitalWrite(TRIGGER, LOW);
  }
  
  else
  {
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
    //  digitalWrite(TRIGGER, HIGH);
      delay(300);
      digitalWrite(TRIGGER, LOW);
      lcd.init();
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("MAGIC TOUCH");
      lcd.setCursor(0,1);
      lcd.print("WELCOME...");
  
      delay(1000);
    
  }
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("MAGIC TOUCH");
    lcd.setCursor(0,1);
    lcd.print("SCAN YOUR CARD...");
    
  }

 // RE-INIT RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // S

  digitalWrite(4,LOW);
      digitalWrite(5,LOW);

}
