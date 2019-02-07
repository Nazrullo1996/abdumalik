#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2     // вывод, к которому подключается датчик
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme; // I2C

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x3F,16,2);  // Устанавливаем дисплей
void setup()
{
    Serial.begin(9600);
  dht.begin();
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("Nazrullo");
  lcd.setCursor(0, 1);
  lcd.print("Tester");
    if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
    }
}
void loop()
{
delay(250);

// считывание температуры или влажности занимает примерно 250 мс!
  // считанные показания могут отличаться от актуальных примерно на 2 секунды (это очень медленный датчик)
  float h = dht.readHumidity();
  // Считывание температуры в цельсиях
  float t = dht.readTemperature();

  // проверяем, были ли ошибки при считывании и, если были, начинаем заново
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  lcd.clear();
  //выводим информацию в Монитор последовательного порта
  lcd.setCursor(0, 0);
  lcd.print(h);
  lcd.print("%");
  lcd.print(" ");
  lcd.print(bme.readPressure()/133.3);
  lcd.print("mm");
  lcd.setCursor(0, 1);
  lcd.print(t);
  lcd.print("C");
  lcd.print(" ");
  lcd.print( bme.readTemperature());
  lcd.print("C");
}

  //*************************************
  // Устанавливаем курсор на вторую строку и нулевой символ.
  //lcd.setCursor(0, 1);
  // Выводим на экран количество секунд с момента запуска ардуины
 // lcd.print(millis()/1000);
//}
