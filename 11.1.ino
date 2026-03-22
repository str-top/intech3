// --- Пины ---
// Подключаем пины управления драйвером
const int DIR_PIN = 5;    // Пин Направления (DIR)
const int STEP_PIN = 6;   // Пин Шага (STEP)
const int ENABLE_PIN = 12; // Пин Включения (EN) - LOW = включен
const int BUTTON_PIN = 2; // Пин кнопки

// --- Настройки мотора ---
// У NEMA 17 в Wokwi 200 шагов на полный оборот (1.8 градуса/шаг)
const int STEPS_PER_REV = 200;

// --- Глобальные переменные ---
bool currentDirection = HIGH; // Текущее направление (HIGH = по часовой, LOW = против)

void setup() {
  Serial.begin(9600); // Для отладки
  Serial.println("Stepper A4988 Test");

  // Настраиваем пины драйвера как выходы
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Настраиваем пин кнопки как вход с подтяжкой
  // (Кнопка подключается между пином D2 и GND)
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Включаем драйвер (подаем LOW на EN)
  // Если подать HIGH, мотор не будет вращаться
  digitalWrite(ENABLE_PIN, LOW);

  // Устанавливаем начальное направление
  digitalWrite(DIR_PIN, currentDirection);
}

void loop() {
  // --- Обработка нажатия кнопки ---

  bool reading = digitalRead(BUTTON_PIN); // Считываем состояние кнопки

    // И если произошло именно НАЖАТИЕ (было HIGH, стало LOW)
    if (reading == LOW) {

      Serial.println("Knopka nazhata!");

      // 1. Меняем направление
      currentDirection = !currentDirection; // Инвертируем (true -> false, false -> true)

      // 2. Устанавливаем новое направление на драйвере
      digitalWrite(DIR_PIN, currentDirection);

      Serial.print("Napravlenie: ");
      Serial.println(currentDirection ? "PO chasovoi" : "PROTIV chasovoi");

      // 3. Делаем 200 шагов (1 оборот)
      Serial.println("Vraschaem...");
      for (int i = 0; i < STEPS_PER_REV; i++) {
        // Генерируем импульс (шаг): HIGH -> LOW
        digitalWrite(STEP_PIN, HIGH);
        // Задержка определяет скорость вращения. Чем меньше, тем быстрее.
        delayMicroseconds(500);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(500);
      }
      Serial.println("Gotovo!");
    }
}
