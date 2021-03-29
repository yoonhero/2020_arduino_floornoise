int vibration = 0;
int piezo = 4;
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);
}
void loop() {
  vibration = pulseIn(A0, HIGH, 1000);
  if (vibration > 200) {
    Serial.println("be quiet");
    for (int i = 3; i < numTones; i++) {
      tone(piezo, tones[i]);
      delay(20);
    }
  }
  Serial.println(vibration);
  noTone(piezo);
}
