void loop() {
  if (signaling)
  {
    /*lcd.setCursor(0,0);              // Установка курсора в начало первой строки
    lcd.print("SIGNALING       ");       // Набор текста на первой строке
    lcd.setCursor(0,1);
    lcd.print ("                 ");
    */    
    digitalWrite(redSignalPin, HIGH);
    
    if(digitalRead(VorPin))
    {
      digitalWrite (buzzerPin, HIGH);
      //lcd.println ("Attac");
    }
    else
    {
      digitalWrite (buzzerPin, LOW);        
    }
  }
  else 
  {
   // digitalWrite(buzzerPin, LOW);
    digitalWrite(redSignalPin, LOW);
    if (digitalRead(dsmokePin)){ 
     // if (millis() - DHTtimer > 2000){
        //LCDDHT();
       // DHTtimer = millis();
     // }
    }
   
    switch (vrata)
    {
      case true: 
        servo1.write (5);
        break;
                  
      case false:
        servo1.write (137);
        break;
    }
    
    if(svet1 == true)
    {
      digitalWrite(svet1Pin, HIGH);
    }
    else 
    {
      digitalWrite(svet1Pin, LOW);
    }
         
    if(svet2 == true)
    {
      digitalWrite(svet2Pin, HIGH);
    }
    else 
    {
      digitalWrite(svet2Pin, LOW);
    }
    
    if (Cold == true)
    {
      Colding();
    }
    else
    {
      digitalWrite (IN2, LOW);
      digitalWrite (IN1, LOW);
    }
   
   digitalWrite (buzzerPin, LOW); 
  }
      
    if (irrecv.decode(&results)) // если данные пришли, используем функцию работы с сигналом
    {
      IRsignal();
    }

  /*while (analogRead(smokePin)>1000) // аналоговое чтение данных с датчика дыма
  {
    Serial.println ("!!!GAS!!!");
    
    lcd.setCursor(0, 0);              // Установка курсора в начало первой строки
    lcd.print ("GAS!!!                          ");
    lcd.setCursor(0, 1);
    lcd.print ("                 ");
    
    digitalWrite(buzzerPin, HIGH);
  }
  while (!digitalRead(12)) // цифровое чтение данных с датчика дыма
  {
    digitalWrite (buzzerPin, HIGH);
    Serial.println ("!!!GAS!!!");
    
    lcd.setCursor(0, 0);              // Установка курсора в начало первой строки
    lcd.print ("GAS!!!                       ");
    lcd.setCursor(0, 1);
    lcd.print ("                 ");
     
  }*/
  
  COMCheck(); 
  for(int i = 0; i<5; i++){
    Serial.println(REG_Array[i]);
  }
  Serial.println("|||||||||||||||||||||");
}
