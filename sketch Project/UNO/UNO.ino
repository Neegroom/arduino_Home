#include <DHT.h>

#include <iarduino_I2C_connect.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>             //библиотека для работы с SPI
#include <Ethernet.h>        //библиотека для работы с Ethernet 
boolean newInfo = 0;        //переменная для новой информации
//MAC адрес вашего Ethernet-модуля, если его у вас нет, введите любой
//или оставьте тот, что в примере
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };   
  
LiquidCrystal_I2C lcd(0x27,16,2);

//указываем IP адрес
//будьте внимательны! IP адрес указывается тот, который вы получили запустив пример DhcpAdressPrinter
IPAddress ip(192,168,0,70);    //пример МОЕГО IP адреса, вы вводите сюда СВОЙ

//инифиализация библиотеки Ethernet server library
EthernetServer server(80);


iarduino_I2C_connect I2C2; // Вы можете указать своё название, вместо I2C2


#define DHTPIN 4 // пин DHT датчика
#define DHTTYPE DHT11 // инициализация датчика

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

void setup()
{
  Wire.setClock(400000);
  Wire.begin();
                    
  //запускаем сервер с указанными ранее MAC и вашим IP
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);

  lcd.init();
  lcd.createChar(1, degree); // Создаем символ под номером 1
  lcd.backlight();
  lcd.setCursor(0,0);
 lcd.print("Hello");
}

void loop()
{
  //принимаем данные, посылаемые клиентом
  EthernetClient client = server.available();
  if(client){                                       //если запрос оканчивается пустой строкой
  boolean currentLineIsBlank = true;                //ставим метку об окончании запроса (дословно: текущая линия чиста)
  while (client.connected()) {                      //пока есть соединение с клиентом
    if (client.available()) {                       //если клиент активен
      char c = client.read();                       //считываем посылаемую информацию в переменную "с"
                                                  
      if(newInfo && c == ' '){                      //если переменная новой информации = 1 и "с", в которой записан запрос, равен пустой строке
        newInfo = 0;                                //то обнуляем переменную поступления новой информации
      }
      
      if(c == '$'){                                 //если переменная "с", несущая отправленный нам запрос, содержит символ $ 
                                                    //(все новые запросы) - "$" подразумевает разделение получаемой информации (символов)
        newInfo = 1;                                //то пришла новая информация, ставим метку новой информации в 1
      }
      
      /************************************************************************************************
      Примечание:
      Символ $ используется как обычный символ, который разделяет 1 от 2
      На практике применяют символ &, который разделяет новые переменные от последующих
      Это использьуется, например, в GET-запросах, которые выглядят подобным образом:
      client.print("GET /controlbar/wp-content/data.php?uid=" + ID + "&type=" + type + "&value=" + value);
      как видите, знак & разделяет значение переменной - ID и переменную type     
      ***************************************************************************************************/
      
                                                     //Проверяем содержание URL - присутствует $1 или $2
      if(newInfo == 1){                              //если есть новая информация
          Serial.println(c);

      

          if(c == '1'){
            Serial.println("1ON");
            I2C2.writeByte(0x01, 0, 1);
            lcd.print(1);
            Serial.println("on");
          }
          if(c == '0'){
            Serial.println("1ON");
            I2C2.writeByte(0x01, 0, 0);
            lcd.print(1);
            Serial.println("on");
          }
          if(c == '2'){
            I2C2.writeByte(0x01, 1, 1);
          }
          if(c == '3'){
            I2C2.writeByte(0x01, 1, 0);
          }
          if(c == '4'){
            I2C2.writeByte(0x01, 2, 1);
          }
          if(c == '5'){
            I2C2.writeByte(0x01, 2, 0);
          }
          if(c == '6'){
            I2C2.writeByte(0x01, 3, 1);
          }
          if(c == '7'){
            I2C2.writeByte(0x01, 3, 0);
          }
          if(c == '6'){
            I2C2.writeByte(0x01, 5, 1);
          }
          if(c == '7'){
            I2C2.writeByte(0x01, 5, 0);
          }
      } 
      
      if (c == '\n') {                              //если "с" равен символу новой строки
        currentLineIsBlank = true;                  //то начинаем новую строку
      } 
      else if (c != '\r') {                         //иначе, если "с" не равен символу возврата курсора на начало строки
        currentLineIsBlank = false;                 //то получаем символ на текущей строке
      }
    
      if (c == '\n' && currentLineIsBlank) {        //выводим HTML страницу
        client.println("HTTP/1.1 200 OK");          //заголовочная информация
        client.println("Content-Type: text/html");
        client.println("Connection: close");  
        client.println("Refresh: 30");              //автоматическое обновление каждые 30 сек
        client.println();
        client.println("<!DOCTYPE HTML>");          //HTML тип документа
        client.println("<html>");                   //открытие тега HTML 
        client.print("<title>SMART HOME</title>");                  //название страницы
        client.print("<H1>SMART HOME</H1>");                        //заголовк на странице
        client.print("<a href=\"/$1\"><button>LIGHT1_ON</button></a>");       //кнопка включить
        client.print("<a href=\"/$0\"><button>LIGHT1_OFF</button></a>");      //кнопка выключить
        client.println("<br />");   
        client.print("<a href=\"/$2\"><button>LIGT2_ON</button></a>");       //кнопка включить
        client.print("<a href=\"/$3\"><button>LIGHT2_OFF</button></a>");      //кнопка выключить 
        client.println("<br />");  
        client.print("<a href=\"/$4\"><button>GATE_ON</button></a>");       //кнопка включить
        client.print("<a href=\"/$5\"><button>GATE_OFF</button></a>");      //кнопка выключить 
        client.println("<br />"); 
        client.print("<a href=\"/$6\"><button>signal system_ON</button></a>");       //кнопка включить
        client.print("<a href=\"/$7\"><button>signal system_OFF</button></a>");      //кнопка выключить  
        client.println("<br />"); 
        client.println("</html>");                  //закрываем тег HTML
        break;                                      //выход
      }
    
    }
    
  }
  delay(1);                                          //время на получение новых данных
  client.stop();                                     //закрываем соеднение 
}

byte j = I2C2.readByte(0x01, 0);
Serial.print(j);
delay(2000);
LCDDHT();
}

void LCDDHT(){
  float h = dht.readHumidity(); // читаем влажность
float t = dht.readTemperature(); // читаем температуру
lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
lcd.print("Hum ="); // Выводим текст
lcd.setCursor(7, 0); // Устанавливаем курсор на 7 символ
lcd.print(h, 1); // Выводим на экран значение влажности
lcd.print("%");
lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки
lcd.print("Temp = "); // Выводим текст, \1 - значок градуса
lcd.setCursor(7, 1); // Устанавливаем курсор на 7 символ
lcd.print(t,1); // Выводим значение температуры
lcd.print("\1C");
}
