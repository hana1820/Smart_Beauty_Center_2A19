#define LED_R 7
#define LED_B 9
#define LED_V 12
#define BUZZER 13
#define CAPTEUR_MVT 4
#define CAPTEUR_FUMEE 2

char data;
byte x;

void setup()
{
  pinMode(CAPTEUR_MVT,INPUT);
  pinMode(CAPTEUR_FUMEE,INPUT);
  pinMode(LED_V,OUTPUT);
  pinMode(LED_R,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(BUZZER,OUTPUT);
 
  Serial.begin(9600);
}

void loop()
{
  x+=10;
  digitalWrite(LED_R,LOW);
  digitalWrite(BUZZER,LOW);
  analogWrite(LED_B,x);

  if(digitalRead(CAPTEUR_FUMEE)==0)
  {
    Serial.print('3');
    for(byte j=0;j<50;j++)
    {
    digitalWrite(BUZZER,HIGH);
    digitalWrite(LED_V,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    digitalWrite(LED_V,LOW);
    delay(50);
    }
  }
  
  while(data=='0')
  {
    if(Serial.available())
    data=Serial.read();

    digitalWrite(LED_B,LOW);

    if(digitalRead(CAPTEUR_MVT)==HIGH)
    {
      Serial.print('2');
      for(byte j=0;j<10;j++)
      {
      digitalWrite(BUZZER,HIGH);
      digitalWrite(LED_R,HIGH);
      delay(500);
      digitalWrite(BUZZER,LOW);
      digitalWrite(LED_R,LOW);
      delay(500);
      }
    }
    
    if(digitalRead(CAPTEUR_FUMEE)==0)
    {
      Serial.print('3');
      for(byte j=0;j<50;j++)
      {
      digitalWrite(BUZZER,HIGH);
      digitalWrite(LED_V,HIGH);
      delay(50);
      digitalWrite(BUZZER,LOW);
      digitalWrite(LED_V,LOW);
      delay(50);
      }
  }
  }
  delay(50);
  
  if(Serial.available())
  {
    data=Serial.read();
    
    if(data=='0')
    {
      for(byte i=0;i<5;i++)
      {
        digitalWrite(LED_B,HIGH);
        delay(500);
        digitalWrite(LED_B,LOW);
        delay(500);
      }
      Serial.print('4');
    }
  }
}
