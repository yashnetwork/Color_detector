
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#define s0 11       //Module pins wiring
#define s1 12
#define s2 9
#define s3 10
#define out 8

int data,r,g,b;        //This is where we're going to stock our values
bool red,green,blue,white,black,yellow,cyan,magenta;
void setup() 
{
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
 lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("COLOUR DETECTOR");

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
   
}

void loop()                  //Every 2s we select a photodiodes set and read its data
{

   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red value= "); 
   GetData();                   //Executing GetData function to get the value
r=data;
Serial.print(r); 
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue value= ");
   GetData();
b=data;
Serial.print(b); 
   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   GetData();
g=data*0.65;
   Serial.print(g); 
      lcd.setCursor(0, 1);
if(r<b&r<g&r>5)   lcd.print("      RED       ");
else if(r<b&g<b&b>8)   lcd.print("     YELLOW     ");
else if(b<r&b<g&b>5)   lcd.print("      BLUE      ");

else if(g<r&g<b&g&g>5) lcd.print("      GREEN     ");

else if(r<7&b<7&g<7)   lcd.print("      WHITE     ");
else if(r>25&b>25&g>25)lcd.print("      BLACK     ");

   Serial.println();
   delay(2000);
}

void GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
            //The higher the frequency the lower the duration
   delay(20);
}
