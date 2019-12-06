void COMCheck() // функция чтения данных COM-порта и их декодинга и обработки
{
  switch (Serial.parseInt()){
    case 11:
      svet1 = true;
      break;
    case 21:
      svet2 = true;
      break;
    case 31:
      vrata = true;
      break;
    case 41:
      Cold = true;
      break;
    case 10:
      svet1 = false;
      break;
    case 20:
      svet2 = false;
      break;
    case 30:
      vrata = false;
      break;
    case 40:
      Cold = false;
      break;
    case 81:
      signaling = true;
      break;
    case 80:
      signaling = false;
      break;
  }
}
