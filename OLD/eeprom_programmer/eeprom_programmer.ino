#define OE            15
#define CE            14
#define SHIFT_CLK     3
#define SHIFT_LATCH   4
#define SHIFT_DATA    2
#define D01           5
#define D02           6
#define D03           7
#define D04           8
#define D05           9
#define D06           10
#define D07           11
#define D08           12

void setup() {
  // Initialize the shift register pins
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);

  digitalWrite(OE, LOW);
  digitalWrite(CE, LOW);
  digitalWrite(SHIFT_CLK, LOW);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_DATA, LOW);

  for (int i = D01; i <= D08; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  Serial.begin(115200);

  //writeEEPROM(0xFFF5, 0x4);
  //readEEPROM(0xFFF5);

  while(!Serial.available()){}
  char c = Serial.read();

  if (c == 'P') { 
    printContents();
  } 
  else if (c == 'W') {
    writeEEPROM(0xFFF1, 0x4);
  }


}

void loop() {
}

void setAddress(unsigned int address) {
  byte highByte = address >> 8;
  byte lowByte = address;

  // Shift out the low byte first, then the high byte
  digitalWrite(SHIFT_LATCH, LOW);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, lowByte);
  shiftOut(SHIFT_DATA, SHIFT_CLK, LSBFIRST, highByte);
  digitalWrite(SHIFT_LATCH, HIGH);
}

byte readEEPROM(unsigned int address) {
  for (int pin = D01; pin <= D08; pin++) {
    pinMode(pin, INPUT);
  }

  setAddress(address);

  byte data = 0;
  for (int pin = D08; pin >= D01; pin -= 1) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

void writeEEPROM(unsigned int address, byte data) {
  digitalWrite(CE, HIGH);
  delay(2);
  
  digitalWrite(OE, HIGH);
  delay(1000);

  ////////////////////////////////////////////

  setAddress(address);

  for (int pin = D01; pin <= D08; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }
  delay(5);

  // Pulse CE
  digitalWrite(CE, LOW);
  delayMicroseconds(100);
  digitalWrite(CE, HIGH);
  delayMicroseconds(100);

  for (int pin = D01; pin <= D08; pin++) {
    pinMode(pin, INPUT_PULLUP);
  }

  ////////////////////////////////////////////

  delay(1000);
  digitalWrite(OE, LOW);
  delay(2);
  digitalWrite(CE, LOW);
  
}

void printContents() {
  for (unsigned long base = 0; base <= 0xFFF0; base += 16) {
    byte data[16];
    for (unsigned long offset = 0; offset < 16; offset++) {
      data[offset] = readEEPROM(base + offset);
    }
    Serial.write(data, 16); // Send 16 bytes of data
  }

  Serial.write("EOFEOF");  // Send an End-Of-Transmission signal
  Serial.end();
}