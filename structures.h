#define ACCESS_POINT_NAME "SnSLog"
#define ACCESS_POINT_PASSWORD "mqtt_device" //should be more than 8 characters

#define AP_MODE 2
#define STA_MODE 1
#define OFF_MODE 0

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

#define DELAY2SEND 10 //delay seconds between sends data
long delay2send = DELAY2SEND;

IPAddress ServerIP (192, 168, 10, 1);
IPAddress ServerGW (192, 168, 10, 1);
IPAddress ServerSN (255, 255, 255, 0);

WiFiClientSecure secure_client;
WiFiClient WF_client;
PubSubClient mqtt_client;

uint8_t MAC [6];
byte wifi_status = OFF_MODE;
boolean wifi_conf = false;
boolean server_status = false;
boolean save_cfg = false;
boolean pin_cfg = false;
boolean wifi_cfg = false;
boolean connect_mqtt = false;
boolean mqtt_status = false;
boolean send_mqtt_data = false;
boolean b_check_tick = false;


int ADC_data = 0;
unsigned long Counter1 = 0;
unsigned long Counter2 = 0;
boolean SNS1 = false;
boolean SNS2 = false;
boolean SNS3 = false;

unsigned long UnixTimestamp = 0;

struct strConfig {
  boolean AdminEnabled; //1 byte
  boolean dhcp; //1 byte
  boolean SSL; //1 byte  
  boolean timestamp; //1 byte
  boolean ADC_EN; //1 byte
  boolean D0_EN; //1 byte
  boolean D1_EN; //1 byte
  boolean D2_EN; //1 byte
  boolean D4_EN; //1 byte
  boolean D5_EN; //1 byte
  boolean D6_EN; //1 byte
  boolean D7_EN; //1 byte
  long MQTT_port; //4 bytes
  long MQTT_interval; // 4 byte
  byte IP [4]; //4 bytes
  byte Netmask [4]; //4 bytes
  byte Gateway [4]; //4 bytes
  byte DNS [4]; //4 bytes
  String ssid; //24 bytes
  String password; //24 bytes  
  String DeviceName; //24 bytes
  String MQTT_server; //24 bytes
  String MQTT_login; //24 bytes
  String MQTT_password; //24 bytes
  String time_topic; //16 bytes
  String ADC_topic; //16 bytes
  String D0_topic; //16 bytes
  String D1_topic; //16 bytes
  String D2_topic; //16 bytes
  String D4_topic; //16 bytes
  String D5_topic; //16 bytes
  String D6_topic; //16 bytes
  String D7_topic; //16 bytes
};

strConfig config_dev;

void getStruct(){
  Serial.println("AdminEnabled:" + (String)config_dev.AdminEnabled);
  Serial.println("dhcp:" + (String)config_dev.dhcp);
  Serial.println("SSL:" + (String)config_dev.SSL);
  Serial.println("timestamp:" + (String)config_dev.timestamp);
  Serial.println("ADC_EN:" + (String)config_dev.ADC_EN);
  Serial.println("D0_EN:" + (String)config_dev.D0_EN);
  Serial.println("D1_EN:" + (String)config_dev.D1_EN);
  Serial.println("D2_EN:" + (String)config_dev.D2_EN);
  Serial.println("D4_EN:" + (String)config_dev.D4_EN);
  Serial.println("D5_EN:" + (String)config_dev.D5_EN);
  Serial.println("D6_EN:" + (String)config_dev.D6_EN);
  Serial.println("D7_EN:" + (String)config_dev.D7_EN);
  Serial.println("MQTT_port:" + (String)config_dev.MQTT_port);
  Serial.println("MQTT_server:" + (String)config_dev.MQTT_server);
  Serial.println("MQTT_interval:" + (String)config_dev.MQTT_interval);
  Serial.println("MQTT_password:" + (String)config_dev.MQTT_password);
  Serial.println("ssid:" + (String)config_dev.ssid);
  Serial.println("password:" + (String)config_dev.password);
  Serial.println("DeviceName:" + (String)config_dev.DeviceName);
  Serial.println("time_topic:" + config_dev.time_topic);
  Serial.println("D0_topic:" + config_dev.D0_topic);
  Serial.println("D1_topic:" + config_dev.D1_topic);
  Serial.println("D2_topic:" + config_dev.D2_topic);
  Serial.println("D4_topic:" + config_dev.D4_topic);
  Serial.println("D5_topic:" + config_dev.D5_topic);
  Serial.println("D6_topic:" + config_dev.D6_topic);
  Serial.println("D7_topic:" + config_dev.D7_topic);
}

