void IRsignal() // функция деккодированния инфокрасного сигнала
{
  //Serial.println(results.value); // вывод данных в монитор проекта
  switch (results.value)
  {
    case 16736925 :
      vrata = true;
      break;
    case 16754775 :      
       vrata = false;
       break;
    case 16738455:
       svet1 = !svet1;
       break;
    case 16750695 :
       svet2 = !svet2;
       break;
    case 16730805 :
       if (!vrata)
       signaling = !signaling;
       break;
    case 106899537:
       vrata = !vrata;
       break;
    case 16718055:
       Cold=!Cold; 
       break;
    }
   irrecv.resume();
}
