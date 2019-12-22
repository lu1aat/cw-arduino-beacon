#define DEBUG true

//
// CONFIGURACIONES
//
const int OUT_PIN = 13;           // PIN salida de audio
const int SLEEP_SEC = 60;         // Segundos entre transmision y transmision
char MESSAGE[] = "CQ DE N0CAL";   // Mensaje a modular, solo caracteres en mayuscula de la A a la Z y numeros.

//
// AUDIO
//
const int toneFreqHz = 716;       // Frecuencia del tono
const int toneDurationMs = 150;   // Duracion del tono

// Envia tonos largos o cortos a un PIN
void toneSend(int pin, bool toneLong) {
  if (!toneLong) {
    tone(pin, toneFreqHz, toneDurationMs);
    delay(toneDurationMs);
    noTone(pin);
  } else {
    tone(pin, toneFreqHz, toneDurationMs * 3);
    delay(toneDurationMs * 3);
    noTone(pin);
  }
}

//
// MORSE
//
const int cwToneSpacingMs = 100;      // Tiempo entre tonos (en milisengundos)
const int cwSymbolSpacingMs = 400;    // Tiempo entre simbolos (en milisengundos)
const int cwWordSpacingMs = 1000;     // Tiempo entre palabras (en milisengundos)

// 0-9 group is ASCII 48-57 located fom 25 to 35
// A-Z group is ASCII 65-90 located from 0 to 25
int cwSymbols[][5] = {
  {1, 2},             // 0  A
  {2, 1, 1, 1},       // 1  B
  {2, 1, 2, 1},       // 2  C
  {2, 1, 1},          // 3  D
  {1},                // 4  E
  {1, 1, 2, 1},       // 5  F
  {2, 2, 1},          // 6  G
  {1, 1, 1, 1},       // 7  H
  {1, 1},             // 8  I
  {1, 2, 2, 2},       // 9  J
  {2, 1, 2},          // 10 K
  {1, 2, 1, 1},       // 11 L
  {2, 2},             // 12 M
  {2, 1},             // 13 N
  {2, 2, 2},          // 14 O
  {1, 2, 2, 1},       // 15 P
  {2, 2, 1, 2},       // 16 Q
  {1, 2, 1},          // 17 R
  {1, 1, 1},          // 18 S
  {2},                // 19 T
  {1, 1, 2},          // 20 U
  {1, 1, 1, 2},       // 21 V
  {1, 2, 2},          // 22 W
  {2, 1, 1, 2},       // 23 X
  {2, 1, 2, 2},       // 24 Y
  {2, 2, 1, 1},       // 25 Z
  {2, 2, 2, 2, 2},    // 26 0
  {1, 2, 2, 2, 2},    // 27 1
  {1, 1, 2, 2, 2},    // 28 2
  {1, 1, 1, 2, 2},    // 29 3
  {1, 1, 1, 1, 2},    // 30 4
  {1, 1, 1, 1, 1},    // 31 5
  {2, 1, 1, 1, 1},    // 32 6
  {2, 2, 1, 1, 1},    // 33 7
  {2, 2, 2, 1, 1},    // 34 8
  {2, 2, 2, 2, 1}     // 35 9
};

void cwTx(char message[]) {
  // Iter over message characters
  for(byte i = 0; i < strlen(message); i++) {
    // Check for SPACE, DEC 32
    if(message[i] == 32) {
      delay(cwWordSpacingMs);
      continue;
    }

    // Calculate charcter position in symbol table
    int symbolIndex = 0;
    int symbolShift = 65;
    if (message[i] < 58) {
        symbolShift = 22;
    }
    symbolIndex = message[i] - symbolShift;

    if(DEBUG) {
      // Current character
      Serial.write("Character: ");
      Serial.println(message[i]);
      Serial.write("Character DEC: ");
      Serial.println(message[i], DEC);
    }
    
    Serial.write("Position in symbol table:");
    Serial.println(symbolIndex);

    // Get symbols for this character and send tone to OUT_PIN
    for(byte ii = 0; ii < 5; ii++) {
      int symbol = 0;
      symbol = cwSymbols[symbolIndex][ii];
      Serial.println(symbol);
      if(symbol == 1) {
        toneSend(OUT_PIN, 0);
      } else if (symbol == 2) {
        toneSend(OUT_PIN, 1);
      } else {
        continue;
      }
      delay(cwToneSpacingMs);
    }

    // Delay between each character of the message
    delay(cwSymbolSpacingMs);
    if(DEBUG) {
      Serial.println("---");
    }
  }
  
}

//
// Setup
//
void setup() {
  // Debug mode
  if(DEBUG) {
    Serial.begin(9600);
    Serial.println("SETUP");
  }
  
  // Set pinOut as OUTPUT 
  pinMode(OUT_PIN, OUTPUT);
}


//
// Loop
//
void loop() {
  // Tonos de prueba, descomentar las siguientes 3 lineas
  // toneSend(OUT_PIN, 0);            // Envia PUNTO/DOT "."
  // delay(toneDurationMs + 100);     
  // toneSend(OUT_PIN, 1);            // Envia RAYA/DASH "-"
  // delay(3000);                     // Espera 3 segundos

  // TX
  cwTx(MESSAGE);
  
  // Sleep
  if(DEBUG) {
    Serial.println("------- SLEEP ---------");
  }
  delay(SLEEP_SEC * 1000);
}
