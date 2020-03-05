const int MosfetPin = 3;
const int rotationSensor = 5;
/*
const int freq = 5000;
const int Channel = 0;
const int resolution = 16;
*/
void setup() {
  Serial.begin(9600);
  pinMode(rotationSensor, INPUT);
  pinMode(MosfetPin, OUTPUT);
/*
  ledcSetup(Channel, freq, resolution);

  ledcAttachPin(MosfetPin, Channel);
  */
}

void loop() {
  int rotVal = analogRead(rotationSensor);
  Serial.println(rotVal);
  rotVal = rotVal/10;
  int mappedRotVal = map(rotVal,0, 94,0,255);
  analogWrite(MosfetPin, mappedRotVal);
  delay(10);

}
