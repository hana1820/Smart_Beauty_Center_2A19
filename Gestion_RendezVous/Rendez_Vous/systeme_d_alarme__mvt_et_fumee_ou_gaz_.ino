#define LED_R 2
#define LED_B 3
#define LED_V 9
#define BUZZER 5
#define CAPTEUR_MVT 7
#define CAPTEUR_FUMEE 10

char data;
byte k;

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
  k+=10;
  digitalWrite(LED_R,LOW);
  digitalWrite(BUZZER,LOW);
  analogWrite(LED_B,k);

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
      for(byte j=0;j<11;j++)
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
      for(byte i=0;i<6;i++)
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
