char ledArduino = 13;
char ledVermelho = 9;

boolean ledArduinoAceso = false;
boolean ledVermelhoAceso = false;

boolean start = false;
boolean finished = true;

int countArduino = 0;   //repeticoes, deve ser par
int countVermelho = 0;  //repeticoes, deve ser par
int delayTime = 500;     //ms


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps
  pinMode(ledArduino, OUTPUT);      // sets the digital pin as output
  pinMode(ledVermelho, OUTPUT);      // sets the digital pin as output
}

void initialize(){
  countArduino = 8;   //repeticoes, deve ser par
  countVermelho = 8;
  start = true;
  finished = false;
}

void serialEvent(){
  char comando = Serial.read();
  
  switch (comando){
    case '1':
      initialize();
      Serial.write("0");
      break;
    case '2':
      if(finished){
        Serial.write("3");
      }
      else if (start){
        Serial.write("1");
      }
      else{
        Serial.write("4");
      }
      break;
  }
}

void loop()
{    
  if(countArduino && start && !finished){
    ledArduinoAceso = toggleLed(ledArduino, ledArduinoAceso);
    countArduino--;
  }
  else if(countVermelho && start && !finished){
    ledVermelhoAceso = toggleLed(ledVermelho, ledVermelhoAceso);
    countVermelho--;
  }
  else if(start && !finished){
    finished = true;
    start = false;
    Serial.write("2");
  }
  
}

boolean toggleLed(int led, boolean aceso){
  if(aceso){
    digitalWrite(led, LOW);
  }
  else{
    digitalWrite(led, HIGH);
  }  
  delay(delayTime);
  return !aceso;
}
