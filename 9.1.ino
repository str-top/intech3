const int piezoPin = 8;
const int buttonPin = 7;

/*
NOTE_INDEX — номер ноты

0  = B3  (Си)
1  = C4  (До)
2  = C#4 (До диез)
3  = D4  (Ре)
4  = D#4 (Ре диез)
5  = E4  (Ми)
6  = F4  (Фа)
7  = F#4 (Фа диез)
8  = G4  (Соль)
9  = G#4 (Соль диез)
10 = A4  (Ля)
11 = Bb4 (Си бемоль)
12 = B4  (Си)
13 = C5  (До)
*/

const int NOTE_INDEX = 0;   // студент выбирает свою ноту

int notes[] = {
  247, // 0  B3  Си
  262, // 1  C4  До
  277, // 2  C#4 До#
  294, // 3  D4  Ре
  311, // 4  D#4 Ре#
  330, // 5  E4  Ми
  349, // 6  F4  Фа
  370, // 7  F#4 Фа#
  392, // 8  G4  Соль
  415, // 9  G#4 Соль#
  440, // 10 A4  Ля
  466, // 11 Bb4 Си♭
  494, // 12 B4  Си
  523  // 13 C5  До
};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(buttonPin) == LOW) {
    tone(piezoPin, notes[NOTE_INDEX]);
  } 
  else {
    noTone(piezoPin);
  }

}
