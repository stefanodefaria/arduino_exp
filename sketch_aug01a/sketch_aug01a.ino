const char ledArduino = 13;
const char ledVermelho = 9;

const unsigned int ledTime = 4000; //milliseconds
const unsigned int taskInterval = 10; //milliseconds

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
const int totalBlinkChange = 8;
const int totalBlinkTime = (int) ledTime/totalBlinkChange;

boolean busy = false;

int countArduino = 0;   //repeticoes, deve ser par
int countVermelho = 0;  //repeticoes, deve ser par


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps
  pinMode(ledArduino, OUTPUT);      // sets the digital pin as output
  pinMode(ledVermelho, OUTPUT);      // sets the digital pin as output
}

void reset(){
  digitalWrite(ledArduino, LOW);
  digitalWrite(ledVermelho, LOW);
  ledVermelhoAceso = false;
  ledArduinoAceso = false;
  busy = false;
}

void initialize(){
  countArduino = (int) ledTime / taskInterval;   //repeticoes, deve ser par
  countVermelho = (int) ledTime / taskInterval;  //repeticoes, deve ser par
  busy = true;
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
      reset();
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
      if(!(countArduino % (int)(totalBlinkTime / taskInterval)))
        ledArduinoAceso = toggleLed(ledArduino, ledArduinoAceso);
      countArduino--;
    }
    if(!countArduino && countVermelho){
      if(!(countVermelho % (int)(totalBlinkTime / taskInterval)))
        ledVermelhoAceso = toggleLed(ledVermelho, ledVermelhoAceso);
      countVermelho--;
    }
    if(!countArduino && !countVermelho){
      busy = false;
      Serial.write(END);
    }

    delay(taskInterval);
  }
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
