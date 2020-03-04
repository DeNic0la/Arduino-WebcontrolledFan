const int MosfetPin = 5;
const int rotationSensor = 39;

const int freq = 5000;
const int Channel = 0;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  pinMode(rotationSensor, INPUT);
  pinMode(MosfetPin, OUTPUT);

  ledcSetup(Channel, freq, resolution);

  ledcAttachPin(MosfetPin, Channel);
  
}

void loop() {
  Serial.println(analogRead(rotationSensor));
  int rotVal = analogRead(rotationSensor);
  int mappedRotVal = map(rotVal,0, 4095,0,255);
  ledcWrite(Channel, mappedRotVal);
  delay(30);

}
