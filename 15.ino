#include <Wire.h>               // Для I2C (нужен для MPU6050 и GyverOLED)
#include <GyverOLED.h>          // Новая библиотека для OLED
#include <Adafruit_MPU6050.h>   // Драйвер для MPU6050
#include <Adafruit_Sensor.h>    // Единая библиотека сенсоров Adafruit

// --- Объекты ---
// Создаем объект дисплея (для 128x64, по I2C)
GyverOLED<SSD1306_128x64, OLED_I2C> oled;

// Создаем объект MPU6050
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600); // Запускаем Монитор порта для отладки

  // --- Инициализация MPU6050 ---
  Serial.println("Ishchem MPU6050...");
  if (!mpu.begin(MPU6050_I2CADDR_DEFAULT)) { // 0x68
    Serial.println("MPU6050 ne naiden!");
    while (1) {
      delay(10); // Бесконечный цикл, если датчик не найден
    }
  }
  Serial.println("MPU6050 naiden!");

  // --- Инициализация OLED дисплея ---
  oled.init(); // Инициализируем дисплей
  Serial.println("OLED naiden!");

  oled.clear();  // Очищаем
  oled.update(); // Обновляем (показываем пустой экран)
}

void loop() {
  // 1. Создаем "контейнеры" для хранения данных с датчиков
  sensors_event_t a, g, temp; // a - акселерометр, g - гироскоп, temp - температура

  // 2. Получаем новые данные со всех датчиков MPU6050
  mpu.getEvent(&a, &g, &temp);

  // 3. Очищаем дисплей (буфер)
  oled.clear();

  // --- 4. Рисуем данные Акселерометра (верхняя половина экрана) ---
  oled.setScale(1); // Маленький шрифт (1 = 6x8 пикселей)

  // GyverOLED использует setCursor(КОЛОНКА, СТРОКА) для текста
  oled.setCursor(0, 0); // (0, 0) - 1-я строка
  oled.print("Akselerometr (m/s^2):");

  oled.setCursor(0, 1); // (0, 1) - 2-я строка
  oled.print("X: "); oled.print(a.acceleration.x, 1); // 1 знак после запятой

  oled.setCursor(0, 2); // (0, 2) - 3-я строка
  oled.print("Y: "); oled.print(a.acceleration.y, 1);

  oled.setCursor(0, 3); // (0, 3) - 4-я строка
  oled.print("Z: "); oled.print(a.acceleration.z, 1);

// --- 5. Рисуем данные Гироскопа (нижняя половина экрана) ---

// Текст акселерометра занял 4 строки (0, 1, 2, 3).
// Начинаем выводить гироскоп со строки 4.
oled.setCursor(0, 4); // (0, 4) - 5-я строка
oled.print("Giroskop (rad/s):"); // Данные гироскопа - это скорость вращения
                                 // Библиотека Adafruit возвращает их в рад/сек

oled.setCursor(0, 5); // (0, 5) - 6-я строка
oled.print("X: "); oled.print(g.gyro.x, 2); // 2 знака после запятой

oled.setCursor(0, 6); // (0, 6) - 7-я строка
oled.print("Y: "); oled.print(g.gyro.y, 2);

oled.setCursor(0, 7); // (0, 7) - 8-я (последняя) строка
oled.print("Z: "); oled.print(g.gyro.z, 2);

// 6. ОБЯЗАТЕЛЬНО: Выводим все, что нарисовали, на экран
  oled.update();

  // 7. Выводим все данные в Монитор порта для отладки
  Serial.print("Ax:"); Serial.print(a.acceleration.x);
  Serial.print(" Ay:"); Serial.print(a.acceleration.y);
  Serial.print(" Az:"); Serial.print(a.acceleration.z);
  Serial.print(" | Gx:"); Serial.print(g.gyro.x);
  Serial.print(" Gy:"); Serial.print(g.gyro.y);
  Serial.print(" Gz:"); Serial.print(g.gyro.z);
  Serial.println();

  // 8. Небольшая пауза
  delay(100); // Обновляем экран примерно 10 раз в секунду
}
