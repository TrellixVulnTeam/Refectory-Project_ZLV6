#include <SPI.h>
#include <RFID.h>
#include <SoftwareSerial.h>
RFID rfid(10,9); //SS veya SDA pini, RST pini
SoftwareSerial Serial0 (7,8); //RX TX

int buzzerPIN=8;
int greenPIN=3;
int redPIN=7;

int serNum[5];
bool access;
String cardName="";

String cardNames[10]=
{
  "Student",
  "White",
  "Blue"
};

int cards[][10] = 
{
  {2,24,147,151,30},
  {117,181,29,43,246},
  {134,132,68,20,82}
};

bool PassedList[10] ={false,false,false,false,false,false,false,false,false,false};

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial0.begin(9600);
  Serial.println("System Started");
  SPI.begin();
  rfid.init();
  pinMode(buzzerPIN,OUTPUT);
  pinMode(redPIN,OUTPUT);
  pinMode(greenPIN,OUTPUT);
}

void loop() 
{
char str[4];
 int value=1234; //this would be much more exciting if it was a sensor value
  
  itoa(value, str, 10); //Turn value into a character array
  Serial0.write(str, 4);
  
  access=false;
  if(rfid.isCard())
  {
    if(rfid.readCardSerial())
    {
      bool isValidANDisPassed=false;
      for(int i = 0; i < sizeof(cards); i++)
      {
        for(int j = 0; j < sizeof(rfid.serNum); j++ )
        {
          if(rfid.serNum[j] != cards[i][j]) 
          {
             access = false;
             break;
          } 
          else 
          {
             access = true;
          }
        }
        
        if(access)
        {
          cardName=cardNames[i];
          if(PassedList[i])
          {
            isValidANDisPassed=true;
          }
          else
          {
            isValidANDisPassed=false;
            PassedList[i]=true;
          }
          break;
        }
      }
      
      if(!access)
      {
        Serial.println("Not allowed!"); 
      }
      else
      {
        if(isValidANDisPassed)
        {
           Serial.println("PASSED BEFORE");
           
           
           
           
           
           
           /* for (int i = 0; i < 6; i++){ // playa rejection sound
      int fail_noteDuration = 1000/fail_noteDurations[i];
      tone(buzzerPIN, fail_melody[i],fail_noteDuration);
      int fail_pauseBetweenNotes = fail_noteDuration * 1.30;
      delay(fail_pauseBetweenNotes);
        noTone(buzzerPIN);
      delay(500);*/

        //for (int i = 0; i < 12; i++)
        //{ // play welcome sound
          //int access_noteDuration = 1000/access_noteDurations[i];
          //tone(buzzerPIN, access_melody[i],access_noteDuration);
         // int access_pauseBetweenNotes = access_noteDuration * 1.30;
          //delay(access_pauseBetweenNotes);
          //noTone(buzzerPIN);
       // }
        }
        else 
        {
          Serial.println("Welcome!"+cardName); 
          Serial0.print(cardName);
        }
      }
    }
  }
  
      
     rfid.halt();
    delay(1000);
}












/*

int access_melody[] = {NOTE_G4,0,NOTE_A4,0, NOTE_B4,0,NOTE_A4,0,NOTE_B4,0, NOTE_C5,0};
int access_noteDurations[] = {8,8,8,8,8,4,8,8,8,8,8,4};
int fail_melody[] = {NOTE_G2,0,NOTE_F2,0,NOTE_D2,0};
int fail_noteDurations[] = {8,8,8,8,8,4};
*/


 /*Serial.print(rfid.serNum[0]);
      Serial.print(" ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" ");
      Serial.print(rfid.serNum[4]);
      Serial.println("");*/
      







/*if(rfid.isCard())
  {
    if(rfid.readCardSerial())
    {
      Serial.print("Kart ID: ");
      Serial.print(rfid.serNum[0],HEX);      
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.println(rfid.serNum[4],HEX);

         
      Serial0.write(rfid.serNum[0]);      
      Serial0.write(rfid.serNum[1]);
      Serial0.write(rfid.serNum[2]);
      Serial0.write(rfid.serNum[3]);
      Serial0.write(rfid.serNum[4]);
    }
    rfid.halt();
  }
  delay(500);*/



/*


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 

*/
