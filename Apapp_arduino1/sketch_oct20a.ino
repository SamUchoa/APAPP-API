#include <Stepper.h>
 
const int sensor = A1;
const int button = 3;
bool buttonValue = 1;

const int stepPerRevolution = 512;
 

const int vel = 60;

unsigned long initialTime = 0;
unsigned long finalTime = 0;
unsigned long time = 0; //segundos

const float vLinear = 0.0117602996254682; // 2 * 3.14 * raio * 0,2998500749625187(frequencia) = m/s

float spaceVariation = 0; //metros
float totalSpace = 0;
int readings = 0;


Stepper Stepper(stepPerRevolution, 4, 6, 5, 7);
int ldrValue = 0;
 
void setup() {
  pinMode(sensor, INPUT);
  pinMode(button, INPUT_PULLUP);
  Stepper.setSpeed(vel);
  Serial.begin(9600);
}
 
void loop() {
  buttonValue = digitalRead(button);
  if(!buttonValue){
    spin();
  }
}

void spin(){
  // ldrValue = analogRead(sensor);

  do{
    initialTime = millis();
    Stepper.step(682);
    finalTime = millis();

    time = (finalTime - initialTime) / 1000;
    spaceVariation = vLinear * time;
    totalSpace = totalSpace + spaceVariation;

    readings++;

    ldrValue = analogRead(sensor);
    

    Serial.println("............");
    Serial.println(spaceVariation);
    Serial.println(totalSpace);
    Serial.println(readings);
    Serial.println("............");
    Serial.println(analogRead(sensor));

    delay(1000);
  }while(ldrValue < 100 && totalSpace < 0.5);

  if (totalSpace){
    totalSpace = 0;
    Stepper.step(-682 * readings);
    readings = 0;
  }

  delay(1000);
}