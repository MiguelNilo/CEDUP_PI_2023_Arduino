//---Bibliotecas---//
#include <LiquidCrystal.h>
#include <Servo.h>

//--Variáveis--//
#define senalTemp A0
#define lamp 7
#define senalUmid A1
#define faucet 9
#define ventilador 10
Servo servol;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tempAnalog;
int umidAnalog;

//--Lista de Funções--//
void dadosLCD();
void delayLamp();

void setup(){
  lcd.begin(16,2);
  Serial.begin(9600);
  servol.attach(9);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop(){
  tempAnalog = analogRead(senalTemp);
  umidAnalog = analogRead(senalUmid);
  int temp = map(tempAnalog, 358, 20, 125, -41);
  int umid = map(umidAnalog, 1023, 0, 0, 190);
  dadosLCD();

  if (umid <= 45){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Irrigando...");
    delay(1000);
    servol.write(90);
    delay(10);
    lcd.clear();
  }

  else{
    servol.write(10);
    delay(10);
  }

  if (temp <= 25){
    digitalWrite(lamp, HIGH);
    digitalWrite(ventilador, LOW);
  }

  if (temp > 25 && temp < 36){
    if (lamp == true){
      delayLamp();
    }
    else{
      digitalWrite(lamp, LOW);
    }
  }

  if (temp >= 36){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Ventilando...");
    delay(1000);
    lcd.clear();
    digitalWrite(lamp, LOW);
    digitalWrite(ventilador, HIGH);
  }
}

//--Funções--//
void dadosLCD(){
  int temp = map(tempAnalog, 350, 20, 125, -41);
  int umid = map(umidAnalog, 1023, 0, 0, 190);
  Serial.println(temp);
  Serial.println(umid);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Umid:");
  lcd.print(umid);
  lcd.print("%");
  delay(1000);
}

void delayLamp(){
  delay(5000);
  digitalWrite(lamp, LOW);
}

