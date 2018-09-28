//selocoman 2

// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "RTClib.h"
RTC_DS1307 rtc;

char dds[7][12] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};

#define DHTPIN 6     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//DS1307 rtc(4, 5);

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

byte termometro[8] = {     //icone de termometro
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte umidade[8] = {        //icone de gota para umidade
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};
void setup(){

 lcd.begin (16,2);
 dht.begin();
 rtc.begin();
 lcd.createChar(1,termometro);
 lcd.createChar(2,umidade);

  if (! rtc.isrunning()) {// se o RTC não estiver funcionando
    Serial.println("RTC não estava funcionando"); //imprimir no serial a condição
    rtc.adjust(DateTime(__DATE__, __TIME__)); //sincroniza com o horário do computador
  }
}
 
void loop()
{
  DateTime now = rtc.now();

  //Imprimindo data
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.setCursor(4, 0);
  if(now.day() < 10){ //padronizando o elemento DIA com 2 digitos
    lcd.print("0");
  }
  lcd.print(now.day());
  lcd.print("/");
  if(now.month() < 10){ //padronizando o elemento MES com 2 digitos
    lcd.print("0");
  }
  lcd.print(now.month());
  lcd.print("/");
  lcd.print((now.year())-2000); //padronizando o elemento ANO com 2 digitos
  lcd.setCursor(11, 0);
//  lcd.print(now.dayOfWeek());

  //Imprimindo a hora
  lcd.setCursor(5, 1);
  if(now.hour() < 10){ //padronizando o elemento HORA com 2 digitos
   lcd.print("0");
  }
  lcd.print(now.hour());
  lcd.print(":");
  if(now.minute() < 10){ //padronizando o elemento MINUTO com 2 digitos
   lcd.print("0");
  }
  lcd.print(now.minute());
//  lcd.print(":");
//  if(now.second() < 10){ //padronizando o elemento SEGUNDO com 2 digitos
//    lcd.print("0");
//  }
//  lcd.print(now.second());

  delay(2500);

  //Imprimindo Umidade
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.write(2); //simbolo de umidade
  lcd.setCursor(7,0);
  lcd.print(dht.readHumidity(),0);
  lcd.print("%");

  //imprimindo a Temperatura
  lcd.setCursor(5,1);
  lcd.write(1); // simbolo de temperatura
  lcd.setCursor(7,1);
  lcd.print(dht.readTemperature(),0);
  lcd.print((char)223); //simbolo de "graus" º 
  lcd.print("C");
  delay(2500);
}
