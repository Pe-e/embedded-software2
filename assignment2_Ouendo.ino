#include <Ticker.h>
#define RED 12
#define GREEN 25
#define BUTTON_1 34
#define SQUARE_INPUT 27 //SQUARE WAVE
#define DC_INPUT 35  //POTENTIOMETER

//
Ticker Tasks;   //INIT TICKER FOR CYCLIC EXECUTION 
//     -----------------------TASKS PERIODS-----------------------
int task1_period = 17;
int task2_period = 200;
int task3_period = 1000;
int task4_period = 42;
int task5_period = 42;
int task6_period = 100;
int task7_period = 333;
int task8_period = 333;
int task9_period = 5000;
//     -----------------------RESULTS TO DISP-----------------------

int freqResult = 0;
int analogValue = 0;
int errorCode; 
int buttonState;
int avgAnalog = 0;
int analogs[4] = {0,0,0,0};
//     -----------------------COUNTERS---------------------
int count = 0;
int timing = 0;
//     -----------------------SETUP---------------------
void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(SQUARE_INPUT,INPUT);
  pinMode(DC_INPUT,INPUT);
  Serial.begin(115200);
  Tasks.attach_ms(1, Watchdog); //STICK EXECUTION TASK EVERY 1 MS TO THE TICKER
}

void loop() {}

void Watchdog(){
  
  timing++;  // INCREASE EVERY MS
  //----------------------CONDITIONS CHECKING THE TIMING OF THE TASKS----------
  if(timing % task1_period == 0){
    //Serial.println("Task1");
    task1();
    
  }
  
  if(timing % task2_period == 0){
    //Serial.println("Task2");
    buttonState = task2();
  }
  
  
  if(timing % task3_period == 0){
    //Serial.println("Task3");
    freqResult = task3();
  }

  
  
  
  
  if(timing % task4_period == 0){
    //Serial.println("Task4");
    analogValue = task4();
  }

  
  
  
  if(timing % task5_period == 0){
    //Serial.println("Task5");
    avgAnalog = task5();
  }
  
  
  
  if(timing % task6_period == 0){
    //Serial.println("Task6");
    task6();
  }
  
  
  if(timing % task7_period == 0){
    //Serial.println("Task7");
    errorCode = task7();
  }
  
  
  
  if(timing % task8_period == 0){
    //Serial.println("Task8");
    task8();
  }
  
  
  if(timing % task9_period == 0){
    //Serial.println("Task9");
    task9();
  }
  
  
  
  
  
  

}

void task1() {
  

  digitalWrite(GREEN, HIGH);
  delayMicroseconds(50); // Block pulse up
  digitalWrite(GREEN, LOW); // Block pulse down 
  


}

int task2(){
   return digitalRead(BUTTON_1);  //RETURN STATE OF THE BUTTON
}
    


int task3(){
  int highInput = pulseIn(SQUARE_INPUT,HIGH);  //HIGH PULSE PERDIOD uS
  int lowInput = pulseIn(SQUARE_INPUT,LOW);     //LOW PULSE PERIOD uS
  int totalInput = highInput + lowInput; //WHOLE SIGNAL PERIOD
  int frequency=1000000/totalInput;  // CALCUL FREQUENCY IN HZ (1/PERIOD(uS)) * 1000000
  return frequency;
    
  }
int task4(){
   return analogRead(DC_INPUT);   //READ ANALOG VALUE OF INPUT
}
 
int task5(){
  int sum = 0;
  if(count == 0 || count % 4 == 0) //UPDATE VALUES IN THE ARRAY 
    analogs[0] = analogValue;
  else if(count == 1 || count % 4 == 1) //UPDATE VALUES IN THE ARRAY 
    analogs[1] = analogValue;
  else if(count == 2 || count % 4 == 2) //UPDATE VALUES IN THE ARRAY 
    analogs[2] = analogValue;
  else
    analogs[3] = analogValue;
  count++;  // COUNT THE NUMBER OF VALUE ANALOG RETURNED TO GET THE 4 LAST VALUES WITH MODULO 4 CONDITION

  for(int i=0;i<4;i++){
    sum += analogs[i]; //SUM THE VALUES OF THE ARRAY
  }
  if(count<4)
    return sum/count;    //CALCULATE AVG IF NUMBER OF VALUE IN THE ARRAY IS UNDER 4
  else
    return sum/4;       //CALCULATE AVG IN THE ARRAY
    
  
  
  
  
}


void task6(){
  for(int i=0;i<1000;i++)
    __asm__ __volatile__ ("nop");
    
}
int task7(){
  int error=0;
  if(avgAnalog > 4095/2)
    error = 1;
  return error;
    
    
}
void task8(){
   digitalWrite(RED, errorCode); //IF ERROR LED SWITCH ON
}

void task9(){
  Serial.println("bs:"+String(buttonState)+ //PRINT RESULTS
                  ",F:"+ String(freqResult)+ 
                  ",analog:"+String(analogValue)+ 
                  ",avg:"+String(avgAnalog)+ 
                  ",error:"+String(errorCode));
   
  }
