#define BOOST14V    10
#define CE          16

void setup() {
    pinMode(BOOST14V, OUTPUT);
    pinMode(CE, OUTPUT);

    digitalWrite(BOOST14V, LOW);
    digitalWrite(CE, HIGH);

    digitalWrite(BOOST14V, HIGH);

    delay(2000);

    digitalWrite(CE, LOW);
    delayMicroseconds(100);
    digitalWrite(CE, HIGH);
    delayMicroseconds(100);

    digitalWrite(BOOST14V, LOW);

}

void loop() {

}