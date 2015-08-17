const char ledArduino = 13;
const char ledVermelho = 9;

const unsigned int ledInitialCount = 400;

const char AVAILABLE = '0';
const char BUSY = '1';
const char END = '2';
const char START = '3';
const char REQUEST_STATUS = '4';
const char RESET = '5';
const char SUCCESS = '6';
const char UNKNOWN_COMMAND = '7';

boolean ledArduinoAceso = false;
boolean ledVermelhoAceso = false;

boolean busy = false;

int countArduino = 0;   //repeticoes, deve ser par
int countVermelho = 0;  //repeticoes, deve ser par
int delayTime = 10;     //ms


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps
  pinMode(ledArduino, OUTPUT);      // sets the digital pin as output
  pinMode(ledVermelho, OUTPUT);      // sets the digital pin as output
}

void initialize(){
  countArduino = ledInitialCount;   //repeticoes, deve ser par
  countVermelho = ledInitialCount;  //repeticoes, deve ser par
  digitalWrite(ledArduino, LOW);
  digitalWrite(ledVermelho, LOW);
  ledVermelhoAceso = false;
  ledArduinoAceso = false;
  busy = false;
}

void serialEvent(){
  char comando = Serial.read();
  
  switch (comando){
    case START:
      if(busy){
        Serial.write(BUSY);
      }
      else{
        initialize();
        busy = true;
        Serial.write(SUCCESS);
      }
      break;
      
    case REQUEST_STATUS:
      if(busy){
        Serial.write(BUSY);
      }
      else{
        Serial.write(AVAILABLE);
      }
      break;
    
    case RESET:      
      initialize();
      Serial.write(SUCCESS);
      break;
    
    default:
      Serial.write(UNKNOWN_COMMAND);
      break;
  }
}

void loop()
{    
  if(busy){
    if(countArduino){
      if(!(countArduino % 50))
        ledArduinoAceso = toggleLed(ledArduino, ledArduinoAceso);
      countArduino--;
    }
    if(!countArduino && countVermelho){
      if(!(countVermelho % 50))
        ledVermelhoAceso = toggleLed(ledVermelho, ledVermelhoAceso);
      countVermelho--;
    }
    if(!countArduino && !countVermelho){      
      Serial.write(END);
      busy = false;
    }
  }  
  delay(delayTime);  
}

boolean toggleLed(int led, boolean aceso){
  if(aceso){
    digitalWrite(led, LOW);
  }
  else{
    digitalWrite(led, HIGH);
  }  
  return !aceso;
}
