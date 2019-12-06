#include <DHT.h>
#include <Wire.h>   
#include <LiquidCrystal_I2C.h>
#include <iarduino_I2C_connect.h> 

#define DHTPIN    4 // пин DHT датчика
#define DHTTYPE   DHT11 // инициализация датчика

iarduino_I2C_connect I2C2;        // объявляем переменную для работы c библиотекой iarduino_I2C_connect

DHT dht(DHTPIN, DHTTYPE);
byte degree[8] = // кодируем символ градуса
{
B00111,
B00101,
B00111,
B00000,
B00000,
B00000,
B00000,
};

LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея

unsigned long DHTtimer;

void setup() {
  
  Wire.setClock(400000);            // устанавливаем скорость передачи данных по шине I2C = 400кБит/с
  Wire.begin();
  lcd.init();         // Инициализация lcd
  lcd.backlight();        // Включаем подсветку
  lcd.createChar(1, degree);    // Создаем символ под номером 1
  lcd.setCursor(0,0);              // Установка курсора в начало первой строки
  lcd.print("Hello");       // Набор текста на первой строке
  lcd.setCursor(0,1);              // Установка курсора в начало второй строки
  lcd.print("World!!!");       // Набор текста на второй строке
  delay(1000);
  DHTtimer = millis();

  pinMode(DHTPIN, INPUT);
}

void loop() {
  if (millis() - DHTtimer > 2000){
    LCDDHT();
    DHTtimer = millis();
  }
  
}

void LCDDHT() // функция чтения данных датчика в теплице и вывода данных на экран
{
  float h = dht.readHumidity();  // читаем влажность
  float t = dht.readTemperature();  // читаем температуру
  lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки 
  lcd.print("Hum  = "); // Выводим текст 
  lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ 
  lcd.print(h, 1); // Выводим на экран значение влажности 
  lcd.print("%");
  lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки 
  lcd.print("Temp = "); // Выводим текст, \1 - значок градуса 
  lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ 
  lcd.print(t,1); // Выводим значение температуры 
  lcd.print("\1C");
}
