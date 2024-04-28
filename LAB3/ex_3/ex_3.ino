const int OUTPUT_LED = 13;
int inBuffer;

void setup () {
    pinMode(OUTPUT_LED, OUTPUT);
    Serial.begin(9600);
}

void loop () {
    if (Serial.available()) {
        inBuffer = Serial.read();

        if (inBuffer % 2 == 0) {
            digitalWrite(OUTPUT_LED, HIGH);
        } else {
            digitalWrite(OUTPUT_LED, LOW);
        }
    }
}
