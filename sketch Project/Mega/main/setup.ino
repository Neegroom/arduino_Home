void setup() {
  
  irrecv.enableIRIn();  // запускаем прием инфракрасного сигнала
  servo1.attach(3);  //указываем пин серво-привода
  servo1.write (135);

  lcd.init();         // Инициализация lcd
  lcd.backlight();        // Включаем подсветку
  lcd.createChar(1, degree);    // Создаем символ под номером 1
  lcd.setCursor(0,0);              // Установка курсора в начало первой строки
  lcd.print("Hum  = 34% ");       // Набор текста на первой строке
  lcd.setCursor(0,1);              // Установка курсора в начало второй строки
  lcd.print("Temp = 28\1C");       // Набор текста на второй строке
  delay(1000);
  lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки 
  lcd.print("Hum  = 34% "); // Выводим текст 
  lcd.setCursor(0, 1); // Устанавливаем курсор в начало 2 строки 
  lcd.print("Temp = 28\1C"); // Выводим текст, \1 - значок градуса
  
  
  Serial.begin (9600);

  pinMode(dsmokePin, INPUT);
  pinMode(redSignalPin, OUTPUT);                //настройка пинов платы
  pinMode(48, OUTPUT);
  pinMode(49, INPUT);
  pinMode(svet1Pin, OUTPUT);
  pinMode(svet2Pin, OUTPUT);
  pinMode(VorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode (EN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (0, OUTPUT);
  pinMode (1, INPUT);
  
  svet1 = B0000000;
  svet2 = 0;

  signaling = 0;

  vrata = 0;
  
 // Ethernet.begin(mac, ip);
//  server.begin();

  Wire.begin(0x01); // инициируем подключение к шине I2C в качестве ведомого (slave) устройства, с указанием своего адреса на шине.
  I2C2.begin(REG_Array);// инициируем возможность чтения/записи данных по шине I2C, из/в указываемый массив
  
}
