/*

Основной файл проекта

*/




//#include <MFRC522.h>
//#include <SPI.h>

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#include <Wire.h>
#include <iarduino_I2C_connect.h>    // подключаем библиотеку для соединения arduino по шине I2C

#include <Servo.h>

//#include <boarddefs.h>

#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

//#include <EEPROMex.h>

#include <Ethernet.h>        //библиотека для работы с Ethernet 

////////////////////////////////////////////////////////////////////

byte     REG_Array[5];  //массив данных доступа I2C


#define smokePin  A1 // пин датчика дыма
#define dsmokePin 12
#define redSignalPin 13
//#define SS_PIN    53 // пин для работы с домофонным замком
//#define RST_PIN   5 // пин для работы с домофонным замком
#define buzzerPin 11 //  пин динамика
#define VorPin    7
#define svet1Pin  23 // пин света в левой комнате
#define svet2Pin  22 // пин света в правой комнате
#define DHTPIN    4 // пин DHT датчика
#define DHTTYPE   DHT11 // инициализация датчика
#define IN1       8 // пин для работы с драйвером моторов 
#define IN2       9 // пин для работы с драйвером моторов
#define EN1       10

//int temperature;

//unsigned long DHTtimer = millis();



//boolean svet1;
#define  svet1  REG_Array[0]

//boolean svet2;
#define  svet2 REG_Array[1]

//boolean vrata;
#define  vrata REG_Array[2]

//boolean Cold = false;
#define  Cold REG_Array[3]

//boolean signaling;
#define  signaling REG_Array[4]

boolean newInfo = 0;        //переменная для новой информации

//DHT dht(DHTPIN, DHTTYPE);
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

//byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };     //MAC adress
//IPAddress ip(192,168,0,70); //указываем IP адрес    
//EthernetServer server(80);  //инифиализация библиотеки Ethernet server library

Servo servo1; // объявляем переменную servo типа "servo1"
IRrecv irrecv(2); // указываем пин, к которому подключен IR приемник
decode_results results;

LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея
void COMCheck();
void Colding();
void IRsignal();
//void LCDDHT();
void MOV();


iarduino_I2C_connect I2C2;      // объявляем переменную для работы c библиотекой iarduino_I2C_connect

void setup();
void loop();
