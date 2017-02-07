/* MQTT, send sample (esp8266)
*/
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

SoftwareSerial mySerial(4, 5); /* RX:D4, TX:D5 */
const char* ssid = "aterm-b1f792-g";
const char* password = "6c600f2ccfc11";

//String mAPI_KEY=" ";
const char* mClient_id = "cliennt-1";
const char* mqtt_server = "XXXX-.compute-1.amazonaws.com";

char mTopicIn[]="item-kuc/device-1/test1";

const int mLedPin=4;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
uint32_t mTimer;
//uint32_t mTimerPost;
char msg[50];
int value = 0;
//int mMaxMatrix=20;
//String mWDAT="";
//String mBuff="";

String mHtypOne="01";
String mHtypScr="02";

int mSTAT=0;

//
void setup() {
  pinMode(mLedPin, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
 // mySerial.begin( 9600 );
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //client.setServer(localserver, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
//  mSTAT=mSTAT_1_WDAT;
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  //Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
}

//
void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  String sTopi=String( mTopicIn );
  String sTopi_in =String( topic );
  //String sLine="";
  //mBuff="";
  String sCRLF="\r\n";  
  if( sTopi.equals( sTopi_in ) ){
    for (int i=0;i<length;i++) {
//      Serial.print((char)payload[i]);
      String sPay= String( (char)payload[i] );
      Serial.println("sPay= "+ sPay);
      if(sPay=="1" ){
        digitalWrite(mLedPin  , HIGH );
      }else if(sPay == "0"){
        digitalWrite(mLedPin  , LOW );
      }
//      mBuff += sPay;
    }
   }
}

//
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect( mClient_id )) {
      Serial.println("connected");
      client.subscribe(mTopicIn);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//
void loop() {
  //delay(100);
  //Serial.println("#Loop");
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
//  if(millis() > mTimer ){
//  }
  
}







