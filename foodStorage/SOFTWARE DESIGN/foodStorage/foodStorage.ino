#include <PID_v1.h>
#include <max6675.h>

//arduino board constants
const int pin[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
/*int LED1 = 9;             // Status LED Pin
int CS = 10;             // CS pin on MAX6675
int SO = 12;              // SO pin of MAX6675
int CLK = 13;             // SCK pin of MAX6675
int units = 2;            // Units to readout temp (0 = raw, 1 = ˚C, 2 = ˚F)
float temperature = 0.0;  // Temperature output variable
*/
double Setpoint ; // will be the desired value
double Input; // temperature sensor
double Output ; //more gas
//PID parameters
double Kp=0, Ki=10, Kd=0; 
 
//create PID instance 
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Initialize the MAX6675 Library for our chip
MAX6675 temp(pin[1],pin[2],pin[3]);


 //gas control
 
int ledPin = 10;      // Connect the pin to Arduino pin 10
int mosfetPin = 2;    // Connect the MOSFeT Gate (first pin on the left, when writing on the chip is facing you) to Arduino pin 2
void setup()
{
  
   for(int i =0;i<16;i++){
   pinMode(pin[i],OUTPUT);  
  }
  Serial.begin(9600);   
  //Turn the PID on
  myPID.SetMode(AUTOMATIC);
  //Adjust PID values
  myPID.SetTunings(Kp, Ki, Kd);
}
 
void loop()
{
  //direction and speed control
  directional_And_Speed_Control(food_Constant[]);
  foodProcessTime(foodConstant[1]);
  //read tempearture reading from the TMP
  Input = map(temp.readCelsius(),0,1025,0,255);
  delay(1000);
  //PID calculation
  myPID.Compute();
  analogWrite(pin[],Output);
  analogWrite(pin[],Output);            
  printData();
  delay(1000);

}

void directional_And_Speed_Control(int foodProcessingInstruction[]){
      //speed determination
      analogWrite(foodProcessingInstruction[1],foodProcessingInstruction[3]);
      analogWrite(foodProcessingInstruction[1],foodProcessingInstruction[3]);
   
      //direction change
      digitalWrite(foodProcessingInstruction[1],foodProcessingInstruction[4]);
      digitalWrite(foodProcessingInstruction[1],foodProcessingInstruction[4]);
      digitalWrite(foodProcessingInstruction[1],foodProcessingInstruction[4]);
      digitalWrite(foodProcessingInstruction[1],foodProcessingInstruction[4]);  
  }
void foodProcessTime(int foodProcessingInstruction[]){
     delay(foodProcessingInstruction[5]); 
  }
void printData(){
      //Write the output as calculated by the PID function
      analogWrite(pin[0],Output); //LED is set to digital 3 this is a pwm pin. 
      //Send data by serial for plotting 
      Serial.print(Input);
      Serial.print(" ");
      Serial.println(Output);
      Serial.print(" ");  
      Serial.println(Setpoint);
      delay(100); 
  }  
 
