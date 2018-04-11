#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <SPI.h>
#include <MFRC522.h>
#define FIREBASE_HOST "refectory-project.firebaseio.com"
#define FIREBASE_AUTH "A3d2huLQjpoRU8FsAhSPqju2doXfWw8DgWEcRWZ9"
#define WIFI_SSID "Elif-Apart-K2"
#define WIFI_PASSWORD ""
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
const int buttonPIN=A0;

void PostConnectionInfo()
{
  HTTPClient http;
  http.begin("http://192.168.0.1/login");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("username=elif&password=apart");
}

int currentID=-1;
int valuesOfButtons[6][2]={{1022,945},{600,495},{390,300},{290,250},{240,200},{190,140}};

String thisDay="1";
String thisMonth="1";
String thisYear="2017";

const int numberOfChoices=5;

// Yemek Menusundeki elemanlar seçilirse ilgili item true olacak.
bool choices[]={false,false,false,false,false};
char choiceChars[]={'+','-'};

// Yemek menülerinin elemanları burada tutulur.
String menuItems[]=
{
  /*0*/ "Domates C.",
  /*1*/ "Orman K.",
  /*2*/ "Makarna",
  /*3*/ "Pilav",
  /*4*/ "Yogurt"
};

// currentID sayesinde card isimlerini çekebiliyoruz.
String cardNames[10]=
{
  "Enes ŞANAL",
  "Emirhan ÖZSOY",
  "Enes İDRİSOĞLU",
  "Serap TURGUT",
  "Oğuzhan KARAHAN",
  "Cemil DEMİR"
};

// currentID sayesinde card numaralaranı çekebiliyoruz.
String cards[10] = 
{
  {"75 B5 1D 2B"},
  {"86 84 44 14"},
  {"82 E8 95 97"},
  {"75 9F D1 64"},
  {"02 18 93 97"},
  {"C2 CC 94 97"}  
};

  int optionals[]={2,3};  
  String getChoiceChar(bool chosen)
  {
    if(chosen) return String(choiceChars[0]);
    return String(choiceChars[1]);
  }
  
bool cardOkumaYazdirildi=false;
  void SerialPrintln()
  {
    Serial.println("********************************\n");
    for(int i=0;i<numberOfChoices;i++)
    {
      Serial.println("\t"+getChoiceChar(choices[i])+" "+String(i+1)+"."+menuItems[i]);
    }
    Serial.println("\n********************************\n");
  }
  
  bool SendData()
  { 
    bool tmp=false;
    for(int i=0;i<numberOfChoices;i++)
    { 
      tmp=tmp||choices[i];
    }
    if(!tmp) return false;
    
    
    String code="";
    for(int i=0;i<numberOfChoices;i++)
    { 
      code+=String(choices[i]);
    }
    
    Serial.println("Data Send => "+code);

    String tmpStr="Processes/"+thisYear+"/"+thisMonth+"/"+thisDay+"/"+cards[currentID];

    
    Firebase.setString(tmpStr, code);
    //Firebase.setString("Processes/2017/11/21/"+cards[currentID], code);
    currentID=-1;
    cardOkumaYazdirildi=false;
    return true;
  }
  
  void Reset()
  {
    for(int i=0;i<numberOfChoices;i++) choices[i]=false;
    SerialPrintln();
  }
  
  void SetOptions(int index)
  {
     if(index==5)
      {
        if(SendData())
        {
          Reset();
        }
        else
        {
         for(int i=0;i<50;i++) Serial.println();
          Serial.println("Lütfen Yemek Seçiniz.");
        }
        delay(500);
        return;
      }
      
     if(index==optionals[0] && choices[optionals[1]])
     {
       choices[index]=true;
       choices[optionals[1]]=false;
     }
     else if(index==optionals[1] && choices[optionals[0]])
     {
       choices[index]=true;
       choices[optionals[0]]=false;
     }
     else choices[index]=!choices[index];
     SerialPrintln();
  }
  
  
void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.println("Connected to: " + String(WIFI_SSID));
  Serial.println("Local IP: " + WiFi.localIP());
  Serial.println("Posting Username and Password ");
  PostConnectionInfo();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
  HTTPClient http;
  http.begin("http://time.jsontest.com/");
  int httpCode = http.GET();
  if(httpCode > 0) 
  {
    if(httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      String dateString = payload.substring(86,96);
      String tmp=dateString;
      
      String month=dateString.substring(0,2);
      dateString=tmp;
      thisMonth=month;
      
      String day=dateString.substring(3,5);
      dateString=tmp;
      thisDay=day;
      
      String year=dateString.substring(6,10);
      dateString=tmp;
      thisYear=year;

      /*Serial.println(day);
      Serial.println(month);
      Serial.println(year);*/

      /*String query="Menus/";
      query.concat(year);
      query.concat("/");
      query.concat(month);
      query.concat("/");
      query.concat(day);
      query.concat("/");



      String tmpQuery=query;
      query.concat(1);
      Serial.println(query);
      Serial.println(Firebase.getString(query));*/

      
     
      menuItems[0] = Firebase.getString("Menus/"+year+"/"+month+"/"+day+"/1");
      menuItems[1] = Firebase.getString("Menus/"+year+"/"+month+"/"+day+"/2");
      menuItems[2] = Firebase.getString("Menus/"+year+"/"+month+"/"+day+"/3");
      menuItems[3] = Firebase.getString("Menus/"+year+"/"+month+"/"+day+"/4");
      menuItems[4] = Firebase.getString("Menus/"+year+"/"+month+"/"+day+"/5");

      /*Serial.println(menuItems[0]);
      Serial.println(menuItems[1]);
      Serial.println(menuItems[2]);
      Serial.println(menuItems[3]);
      Serial.println(menuItems[4]);*/

    } 
  }
  
  http.end();
  Serial.println("Firebase Account Connecting... ");
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(buttonPIN,INPUT);
  Serial.println("System Started");
}

 void buttonControl()
  {
    int value=analogRead(buttonPIN);
    if(value>50)
    {
       value=analogRead(buttonPIN);
       while(analogRead(buttonPIN)>50)
       { 
          
       } 
       for(int i=0;i<6;i++)
       if(value<=valuesOfButtons[i][0] && value>valuesOfButtons[i][1]) SetOptions(i);
       for(int i=0;i<15;i++) Serial.println();
    Serial.println("Card ID => [ "+cards[currentID]+" ]");
      Serial.println(cardNames[currentID]);
      SerialPrintln();
    }
  }
  

void loop()
{ 
  if(currentID==-1)
  {
    if(!cardOkumaYazdirildi)
    {
      for(int i=0;i<50;i++)Serial.println();
      Serial.println("Lütfen Kartınızı Okutunuz\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
       cardOkumaYazdirildi=true;
    }
    
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    
    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    
    String content= "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    
    String str1 = content.substring(1);
    Serial.println("Card ID => [ "+str1+" ]");
    for(int i=0;i<sizeof(cards);i++)
    {
        if(content.substring(1)==cards[i])
        {
          currentID=i;
        }
    }
    
    Serial.println(cardNames[currentID]);
    SerialPrintln();
    
  }
  else
  {
    buttonControl();
  }
   
  
}




/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/
/******************************************************************************************************************/





















 //buttonControl();
   
    //String ClassName="Accounts";
    /*for(int i=1;i<=3;i++)
    {    
      int id=i;
      Serial.println(Firebase.getString(ClassName+"/"+id+"/firstName"));
      Serial.println(Firebase.getString(ClassName+"/"+id+"/lastName"));
      Serial.println(Firebase.getString(ClassName+"/"+id+"/cardID"));
      Serial.println(Firebase.getString(ClassName+"/"+id+"/number"));
    }*/

    /*if(Firebase.getString(ClassName+"/"+3+"/cardID").equals(str1))
    {
      Serial.println("TRUE");
    }
    Serial.println(".......");*/

  /*if (Firebase.failed())
  {
    Serial.print("Firebase Error: ");
    Serial.println(String(Firebase.error()));
    return;
  }*/


  /*
   
    Serial.println();
    Serial.print(" UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
    
    */
    
    
    
  
