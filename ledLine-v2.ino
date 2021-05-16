/* 
 * Используется лента RGBW (с отдельным белым каналом)
 * Питание arduino NANO взято с драйвера шагового мотора L298N
 *  
 */
#define GREENPIN 10 //D3
#define REDPIN 3 //D5
#define BLUEPIN 6 //D6
#define WHITEPIN 9 //D9
#define MOTIONPIN 4 //D4
 
#define FADESPEED 25     // чем выше число, тем медленнее будет fade-эффект

int motionLast, motionOff = 0;
  
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);
  pinMode(MOTIONPIN, INPUT);
}
  
  
void loop() {
  if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn();} //Если есть движение, включить белый
  else {
    motionOff = motionOff + 1; //Иначе добавляем +1 к количеству повторов смены цветов
    if (motionOff < 10) LedBlink(); //Если количество смены цветов меньше 10 то меняем цвета.
    else {//motionLast //Если 10 и больше - выключаем ленту.
      motionOff = 101; // Заглушка от переполнения переменной.
      analogWrite(GREENPIN, 255);
      analogWrite(REDPIN, 255);
      analogWrite(BLUEPIN, 255);
      analogWrite(WHITEPIN, 255);
    }
  }
}


void LedBlink(){
  int r, g, b, motion;
  
  analogWrite(WHITEPIN, 255);
  analogWrite(REDPIN, 0); //v2 Устанавливаем цвета для бесшовного включения.
  analogWrite(GREENPIN, 0); //v2 Устанавливаем цвета для бесшовного включения.
  
  // fade от голубого к фиолетовому
  for (r = 0; r < 256; r++) {
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade от фиолетового к красному
  for (b = 255; b > 0; b--) {
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade от красного к желтому
  for (g = 0; g < 256; g++) { 
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  // fade от желтого к зеленому
  for (r = 255; r > 0; r--) { 
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade от зеленого к зеленовато-голубому
  for (b = 0; b < 256; b++) { 
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade от зеленовато-голубого к голубому
  for (g = 255; g > 0; g--) { 
    //motion = Serial.read();
    if (digitalRead(MOTIONPIN) == HIGH) {WhiteOn(); return;}
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  }   
}

void WhiteOn(){ //Включение белого цвета.
  motionOff = 0; //Сбрасываем счетсик повторов смены цветов
  analogWrite(GREENPIN, 255); //Выключаем зеленый
  analogWrite(REDPIN, 255); //Выключаем Красный
  analogWrite(BLUEPIN, 255); //Выключаем синий
  analogWrite(WHITEPIN, 0); //Включаем белый
}
