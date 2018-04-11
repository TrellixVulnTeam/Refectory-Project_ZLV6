#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "androidfirebaseproject-dc499.firebaseio.com"
#define FIREBASE_AUTH "wSh3ZHg7qMVDgT2KYWdPqNXT3I7yn2r4SATMSCp4"
#define WIFI_SSID "Elif-Apart-K2"
#define WIFI_PASSWORD ""

void PostConnectionInfo()
{
  HTTPClient http;
  http.begin("http://192.168.0.1/login");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("username=elif&password=apart");
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
  Serial.println("Connected to: "+String(WIFI_SSID));
  Serial.println("Local IP: "+WiFi.localIP());
  Serial.println("Posting Username and Password ");
  PostConnectionInfo();
  
  /*int httpCode=http.GET();
  if(httpCode > 0) 
  {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
    // file found at server
    if(httpCode == HTTP_CODE_OK) 
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else 
  {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();*/
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
int counter=0;

void loop() 
{
  Serial.println("..........Inside LoopAnother");
  Firebase.setInt("DemoCounter",counter);
  counter++;
  
  FirebaseObject fbObject=Firebase.get("Accounts/");
  Serial.println("..............");
  for(int i=1;i<=3;i++)
  {
    String query=String(i)+"/lastName";
    Serial.println(fbObject.getString(query));
  }
  Serial.println("..............");




     
  if (Firebase.failed()) 
  {
      Serial.print("Firebase Error: ");
      Serial.println(String(Firebase.error()));  
      return;
  }
  delay(3000);

}

/*














void loop() 
{
  if(Firebase.getString("LedState")=="true")
  {
    digitalWrite(LED,HIGH);
  }
  else if(Firebase.getString("LedState")=="false")
  {
    digitalWrite(LED,LOW);
  }

  if(digitalRead(REED)==LOW)
  {
    alarm++;
    counter++;
    digitalWrite(REDLED,HIGH);
    Firebase.setInt("Relay",counter);
  }
  if(digitalRead(REED)==HIGH)
  {
    digitalWrite(REDLED,LOW);
    alarm=0;
  }
  if(alarm>=150)
  {
      digitalWrite(BUZZER,HIGH);
     
  }
  else 
  digitalWrite(BUZZER,LOW);
  

  if (Firebase.failed()) 
  {
      Serial.println(Firebase.error());  
      return;
  }
  delay(100);
}







*/


/*int n = 0;
void loop() {
  // set value
  Firebase.setFloat("number", 42.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("number", 43.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("number: ");
  Serial.println(Firebase.getFloat("number"));
  delay(1000);

  // remove value
  Firebase.remove("number");
  delay(1000);

  // set string value
  Firebase.setString("message", "hello world");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);
}*/
