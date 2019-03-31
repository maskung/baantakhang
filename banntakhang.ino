
//Motor Pins
int EN_A = 9;      //กำหนดขาสำหรับเปิดมอเตอร์ตัวที่ 1
int IN1 = 8;       //ขาควบคุมมอเตอร์ตัวที่ 1 IN1
int IN2 = 7;       //ขาควบคุมมอเตอร์ตัวที่ 1 IN2

// Rain Pin
#define RainPin A2  //ขาที่ต่อกับเซนเซอร์น้ำฝน


// Switch
int FswPin = 2;
int BswPin = 3;

int FswVal = 0;
int BswVal = 0;

//Enable pin for second motor
//Initializing variables to store data
int motor_speed;
int RainVal = 0;

void setup ( ) {
 int error;
  
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);

  pinMode(FswPin, INPUT_PULLUP);  
  pinMode(BswPin, INPUT_PULLUP);
                       
}
void loop () 
{

    Serial.println("");
   
    RainVal = analogRead(RainPin);
    FswVal = digitalRead(FswPin);
    BswVal = digitalRead(BswPin);
    
    Serial.print("Rain Value = ");
    Serial.println(RainVal);
    Serial.print("Fsw Value = ");
    Serial.println(FswVal);
    Serial.print("Bsw Value = ");
    Serial.println(BswVal);


    //ให้หลังคาเปิดเมื่อฝนไม่ตก
    if(  (RainVal < 400) && (FswVal == 0) && (BswVal == 1))
    {
      motor_speed = map(50, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EN_A, motor_speed);
      while(1)
      {
        FswVal = digitalRead(FswPin);
        BswVal = digitalRead(BswPin);
        if((FswVal == 1) && (BswVal ==0))
        {           
           analogWrite(EN_A, 0); 
           break;
        }
        delay(10);
      }
      
    }

    //ให้หลังคาปิดเมื่อฝนตก
    if( (RainVal > 400) && (FswVal == 1) && (BswVal == 0))
    {
      motor_speed = map(50, 400, 0, 0, 255);   //Mapping the values to 0-255 to move the motor
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EN_A, motor_speed);
      while(1)
      {
        FswVal = digitalRead(FswPin);
        BswVal = digitalRead(BswPin);
        if((FswVal == 0) && (BswVal == 1))
        {           
           analogWrite(EN_A, 0); 
           break;
        }
        delay(10);
      }
      
    }

    delay(1000);
  }

  
