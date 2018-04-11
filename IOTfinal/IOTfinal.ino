  #include <LCD5110_Basic.h>
  #include <SoftwareSerial.h>
  /*******************************************************************************************/
  LCD5110 myScreen(8,9,10,11,12);
  const int numberOfChoices=5;
  const int sendButtonPIN=13;
  int valuesOfButtons[6][2]={{1023,990},{950,900},{860,840},{790,770},{740,720},{690,660}};
  int ButtonSequence[6]={4,3,2,1,0,5};
  const int buttonPIN=A0;
  bool sendbutton=false;
  bool choices[]={false,false,false,false,false};
  int menuPositionsX[]={0,15,20,30,35};
  int menuPositionsY[]={0,0,0,0,0};
  char choiceChars[]={'+','-'};
  String menuItems[]=
    {
      /*0*/ "Domates C.",
      /*1*/ "Orman K.",
      /*2*/ "Makarna",
      /*3*/ "Pilav",
      /*4*/ "Yogurt"
    };
  int optionals[]={2,3};
   
  /*******************************************************************************************/
  
  void getInitialScreen()
  {
    myScreen.clrScr();
    for(int k=0;k<3;k++)
    {
      if(k==0) myScreen.print("Initializing",0, 20);
      if(k==1) myScreen.print("Setting Coords.",0, 20);
      if(k==2) myScreen.print("Getting menu",0, 20);
      String s="";
      for(int i=0;i<6;i++)
      {
        s+=".";
        myScreen.print(s,24, 25); 
        delay(40);
      }
      delay(60);
    }
  }
  
  void getSendingScreen()
  {
    myScreen.clrScr();
    myScreen.print("Menu Hazir",8, 20);
    myScreen.print("Geciniz",8, 30);
  }
  
  void getErrorScreen()
  {
    myScreen.clrScr();
    myScreen.print("Yemek Seciniz",0, 20);
  }
  
  String getChoiceChar(bool chosen)
  {
    if(chosen) return String(choiceChars[0]);
    return String(choiceChars[1]);
  }
  
  void getMenuScreen()
  { 
    for(int i=0;i<numberOfChoices;i++)
      myScreen.print(getChoiceChar(choices[i])+" "+String(i+1)+"."+menuItems[i], menuPositionsY[i], menuPositionsX[i]);
  }
  
  void SerialPrintln()
  {
    Serial.println("********************************\n");
    for(int i=0;i<numberOfChoices;i++)
    {
      Serial.println("\t"+getChoiceChar(choices[i])+" "+String(i+1)+"."+menuItems[i]);
    }
    Serial.println("\n********************************\n");
      
  }
  
  void SetOptions(int index)
  {
     if(index==5)
      {
        if(SendData())
        {
          Reset();
          getSendingScreen();
        }
        else
        {
          getErrorScreen();
        }
        delay(1000);
        
        myScreen.clrScr();
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
  }
  
  void buttonControl()
  {
    int value=analogRead(buttonPIN);
    if(value>500)
    {
       value=analogRead(buttonPIN);
       while(analogRead(buttonPIN)>0)
       { 
         value=analogRead(buttonPIN);
         Serial.println("Waiting   "+ String(analogRead(buttonPIN)));
       }
       Serial.println(value); 
       for(int i=0;i<6;i++)
          if(value<=valuesOfButtons[i][0] && value>valuesOfButtons[i][1]) SetOptions(ButtonSequence[i]); 
      SerialPrintln();
    }
  }
  
  void Reset()
  {
    for(int i=0;i<numberOfChoices;i++) choices[i]=false;
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
    return true;
  }
  
  /*******************************************************************************************
  ********************************************************************************************
  ********************************************************************************************
  ********************************************************************************************/
 


  
  void setup()
  {
    Serial.begin(9600); 
    pinMode(buttonPIN,INPUT);
    extern uint8_t SmallFont[]; 
    myScreen.InitLCD();
    myScreen.setFont(SmallFont);
    getInitialScreen();
    Serial.println("System Started");
    pinMode(sendButtonPIN, INPUT);
  }
  
  void loop()
  {   
    getMenuScreen();
    buttonControl();
  }
  
  

