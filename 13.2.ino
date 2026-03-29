// --- Пины ---
const int LIGHT_SENSOR_PIN = A4; // Пин для аналогового выхода (AO) LDR-модуля
const int RELAY_PIN = 7;         // Пин D7 для управления реле (IN)
const int LED_PIN = 3;           // Пин D3 для светодиода (в силовой цепи)
const int RESISTOR_PIN = 4;      // Пин D4 для резистора (в силовой цепи)

// --- Настройки ---
// Порог срабатывания. Подбирается экспериментально, глядя в Монитор порта.
const int DARKNESS_THRESHOLD = 600;

// Задаем константы для инверсной логики реле
// (Модуль в Wokwi включается при подаче LOW)
const int RELAY_STATE_ON = LOW;
const int RELAY_STATE_OFF = HIGH;

void setup() {
  // Запускаем Монитор порта для отладки
  Serial.begin(9600);
  Serial.println("Avtomaticheskiy fonar' (Rele)");

  // Настраиваем пин реле как ВЫХОД
  pinMode(RELAY_PIN, OUTPUT);

  // Устанавливаем реле в ВЫКЛЮЧЕННОЕ состояние при старте
  // (Подаем HIGH, так как логика инверсная)
  digitalWrite(RELAY_PIN, RELAY_STATE_OFF);

}

void loop() {
  // 1. Считываем значение с датчика света (0-1023)
  int lightValue = analogRead(LIGHT_SENSOR_PIN);

  // 2. Выводим значение в Монитор порта
  Serial.print("Znachenie sveta (AO): ");
  Serial.println(lightValue);

  // 3. Принимаем решение
  if (lightValue > DARKNESS_THRESHOLD) {
    // Стало ТЕМНО
    Serial.println("Temno. VKLYUCHAEM rele (podem LOW).");
    digitalWrite(RELAY_PIN, RELAY_STATE_ON); // Включаем реле (подаем LOW)

  } else {
    // Стало СВЕТЛО
    Serial.println("Svetlo. VIKLYUCHAEM rele (podem HIGH).");
    digitalWrite(RELAY_PIN, RELAY_STATE_OFF); // Выключаем реле (подаем HIGH)

  }

  // 4. Ждем немного, чтобы не "дребезжать"
  delay(500); // Проверяем каждые полсекунды
}
