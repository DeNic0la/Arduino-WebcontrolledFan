const int MosfetPin = 5;
const int rotationSensor = 39;

const int freq = 5000;
const int Channel = 0;
const int resolution = 16;

void setup() {
  Serial.begin(115200);
  pinMode(rotationSensor, INPUT);
  pinMode(MosfetPin, OUTPUT);

  ledcSetup(Channel, freq, resolution);

  ledcAttachPin(MosfetPin, Channel);
  
}

void loop() {
  int rotVal = analogRead(rotationSensor);
  Serial.println(rotVal);
  
  rotVal = rotVal/10;
  int mappedRotVal = map(rotVal,0, 409,0,255);
  ledcWrite(Channel, mappedRotVal);
  delay(30);

}
