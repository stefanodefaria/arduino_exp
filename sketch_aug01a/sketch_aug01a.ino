char ledArduino = 13;
char ledVermelho = 9;

boolean ledArduinoAceso = false;
boolean ledVermelhoAceso = false;

boolean start = false;
boolean finished = false;

int countArduino = 8;   //repeticoes, deve ser par
int countVermelho = 8;  //repeticoes, deve ser par
int delayTime = 500;     //ms


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps
  pinMode(ledArduino, OUTPUT);      // sets the digital pin as output
  pinMode(ledVermelho, OUTPUT);      // sets the digital pin as output
}

void serialEvent(){
  char comando = Serial.read();
  
  Serial.write("Comando: ");
  Serial.write(comando);
  Serial.write("\n");
  
  switch (comando){
    case '1':
      start = true;
      Serial.write("Operacao iniciada");
      break;
    case '2':
      if(finished){
        Serial.write("Terminado");
      }
      else if (start){
        Serial.write("Em andamento");
      }
      else{
        Serial.write("Nao iniciado");
      }
      break;
  }
  Serial.write("\n");
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
    Serial.write("Terminou agora\n");
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
