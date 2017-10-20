//Read and Write functions EEPROM

void WriteStringToEEPROM (int beginaddress, String str, int maxsize) {
  int sizest = str.length ();
  if (maxsize < sizest) sizest = maxsize;
  for (int t = 0; t < sizest; t++) EEPROM.write ((beginaddress + t), str[t]);
  EEPROM.write ((beginaddress + sizest), ';');
}

String ReadStringFromEEPROM (int beginaddress, int sizest) {
  int counter = 0;
  char rChar;
  String retString = "";
  while (counter <= sizest) {
    rChar = EEPROM.read (beginaddress + counter);
    if (rChar == ';') break;
    retString += rChar;
    counter++;
  }
  return retString;
}

void EEPROMWritelong (int address, long value) { //Write the 4 bytes into the eeprom memory.
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  EEPROM.write (address, four);
  EEPROM.write (address + 1, three);
  EEPROM.write (address + 2, two);
  EEPROM.write (address + 3, one);
}

long EEPROMReadlong (long address) { //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read (address);
  long three = EEPROM.read (address + 1);
  long two = EEPROM.read (address + 2);
  long one = EEPROM.read (address + 3);
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
} //Return the recomposed long by using bitshift.

void WriteConfig () {
  EEPROM.begin (332);
  Serial.println ("Writing Config");
  EEPROM.write (0, 'C');
  EEPROM.write (1, 'F');
  EEPROM.write (2, 'G');
  EEPROM.write (3, 0);
  EEPROM.write (4, 0);
  EEPROM.write (5, 0);
  EEPROM.write (6, 0);
  EEPROM.write (7, config_dev.AdminEnabled);  //1 byte
  EEPROM.write (8, config_dev.dhcp);  //1 byte
  EEPROM.write (9, config_dev.SSL);  //1 byte
  EEPROM.write (10, config_dev.timestamp); //1 byte
  EEPROM.write (11, config_dev.ADC_EN); //1 byte
  EEPROM.write (12, config_dev.D0_EN); //1 byte
  EEPROM.write (13, config_dev.D1_EN); //1 byte
  EEPROM.write (14, config_dev.D2_EN); //1 byte
  EEPROM.write (15, config_dev.D4_EN); //1 byte
  EEPROM.write (16, config_dev.D5_EN); //1 byte
  EEPROM.write (17, config_dev.D6_EN); //1 byte
  EEPROM.write (18, config_dev.D7_EN); //1 byte
  EEPROMWritelong (19, config_dev.MQTT_port); //4 bytes
  EEPROM.write (23, config_dev.IP [0]); //1 byte
  EEPROM.write (24, config_dev.IP [1]); //1 byte
  EEPROM.write (25, config_dev.IP [2]); //1 byte
  EEPROM.write (26, config_dev.IP [3]); //1 byte
  EEPROM.write (27, config_dev.Netmask [0]); //1 byte
  EEPROM.write (28, config_dev.Netmask [1]); //1 byte
  EEPROM.write (29, config_dev.Netmask [2]); //1 byte
  EEPROM.write (30, config_dev.Netmask [3]); //1 byte
  EEPROM.write (31, config_dev.Gateway [0]); //1 byte
  EEPROM.write (32, config_dev.Gateway [1]); //1 byte
  EEPROM.write (33, config_dev.Gateway [2]); //1 byte
  EEPROM.write (34, config_dev.Gateway [3]); //1 byte
  EEPROM.write (35, config_dev.DNS [0]); //1 byte
  EEPROM.write (36, config_dev.DNS [1]); //1 byte
  EEPROM.write (37, config_dev.DNS [2]); //1 byte
  EEPROM.write (38, config_dev.DNS [3]); //1 byte
  WriteStringToEEPROM (39, config_dev.ssid, 24); //24 bytes
  WriteStringToEEPROM (63, config_dev.password, 24); //24 bytes
  WriteStringToEEPROM (87, config_dev.DeviceName, 24); //24 bytes
  WriteStringToEEPROM (111, config_dev.MQTT_server, 24); //24 bytes
  WriteStringToEEPROM (135, config_dev.MQTT_login, 24); //24 bytes
  WriteStringToEEPROM (159, config_dev.MQTT_password, 24); //24 bytes
  WriteStringToEEPROM (183, config_dev.time_topic, 16); //16 bytes
  WriteStringToEEPROM (199, config_dev.ADC_topic, 16); //16 bytes
  WriteStringToEEPROM (215, config_dev.D0_topic, 16); //16 bytes
  WriteStringToEEPROM (231, config_dev.D1_topic, 16); //16 bytes
  WriteStringToEEPROM (247, config_dev.D2_topic, 16); //16 bytes
  WriteStringToEEPROM (263, config_dev.D4_topic, 16); //16 bytes
  WriteStringToEEPROM (279, config_dev.D5_topic, 16); //16 bytes
  WriteStringToEEPROM (295, config_dev.D6_topic, 16); //16 bytes
  WriteStringToEEPROM (311, config_dev.D7_topic, 16); //16 bytes
  EEPROMWritelong (327, config_dev.MQTT_interval); //4 bytes
  EEPROM.end(); //total 332 bytes
}

boolean ReadConfig () {
  Serial.println ("Reading Configuration");
  EEPROM.begin (332);
  if (EEPROM.read (0) == 'C' && EEPROM.read (1) == 'F' && EEPROM.read (2) == 'G' && EEPROM.read (3) == 0 && EEPROM.read (4) == 0 && EEPROM.read (5) == 0 && EEPROM.read (6) == 0) {
    Serial.println ("Configurarion Found");
    config_dev.AdminEnabled = EEPROM.read (7); //1 byte
    config_dev.dhcp = EEPROM.read (8); //1 byte
    config_dev.SSL = EEPROM.read (9); //1 byte
    config_dev.timestamp = EEPROM.read (10); //1 byte
    config_dev.ADC_EN = EEPROM.read (11); //1 byte
    config_dev.D0_EN = EEPROM.read (12); //1 byte
    config_dev.D1_EN = EEPROM.read (13); //1 byte
    config_dev.D2_EN = EEPROM.read (14); //1 byte
    config_dev.D4_EN = EEPROM.read (15); //1 byte
    config_dev.D5_EN = EEPROM.read (16); //1 byte
    config_dev.D6_EN = EEPROM.read (17); //1 byte
    config_dev.D7_EN = EEPROM.read (18); //1 byte    
    config_dev.MQTT_port = EEPROMReadlong (19); //4 Byte
    config_dev.IP[0] = EEPROM.read (23); //1 byte
    config_dev.IP[1] = EEPROM.read (24); //1 byte
    config_dev.IP[2] = EEPROM.read (25); //1 byte
    config_dev.IP[3] = EEPROM.read (26); //1 byte
    config_dev.Netmask[0] = EEPROM.read (27); //1 byte
    config_dev.Netmask[1] = EEPROM.read (28); //1 byte
    config_dev.Netmask[2] = EEPROM.read (29); //1 byte
    config_dev.Netmask[3] = EEPROM.read (30); //1 byte
    config_dev.Gateway[0] = EEPROM.read (31); //1 byte
    config_dev.Gateway[1] = EEPROM.read (32); //1 byte
    config_dev.Gateway[2] = EEPROM.read (33); //1 byte
    config_dev.Gateway[3] = EEPROM.read (34); //1 byte
    config_dev.DNS[0] = EEPROM.read (35); //1 byte
    config_dev.DNS[1] = EEPROM.read (36); //1 byte
    config_dev.DNS[2] = EEPROM.read (37); //1 byte
    config_dev.DNS[3] = EEPROM.read (38); //1 byte
    config_dev.ssid = ReadStringFromEEPROM (39, 24); //24 bytes
    config_dev.password = ReadStringFromEEPROM (63, 24); //24 bytes
    config_dev.DeviceName = ReadStringFromEEPROM (87, 24); //24 bytes
    config_dev.MQTT_server = ReadStringFromEEPROM (111, 24); //24 bytes
    config_dev.MQTT_login = ReadStringFromEEPROM (135, 24); //24 bytes
    config_dev.MQTT_password = ReadStringFromEEPROM (159, 24); //24 bytes
    config_dev.time_topic = ReadStringFromEEPROM (183, 16); //16 bytes
    config_dev.ADC_topic = ReadStringFromEEPROM (199, 16); //16 bytes
    config_dev.D0_topic = ReadStringFromEEPROM (215, 16); //16 bytes
    config_dev.D1_topic = ReadStringFromEEPROM (231, 16); //16 bytes
    config_dev.D2_topic = ReadStringFromEEPROM (247, 16); //16 bytes
    config_dev.D4_topic = ReadStringFromEEPROM (263, 16); //16 bytes
    config_dev.D5_topic = ReadStringFromEEPROM (279, 16); //16 bytes
    config_dev.D6_topic = ReadStringFromEEPROM (295, 16); //16 bytes
    config_dev.D7_topic = ReadStringFromEEPROM (311, 16); //16 bytes
    config_dev.MQTT_interval = EEPROMReadlong (327); //4 Byte
    EEPROM.end ();
    return true;
  } else {
    EEPROM.end ();
    Serial.println ("Configurarion NOT FOUND");
    //SET DEFAULT CONFIG
    config_dev.AdminEnabled = true;
    config_dev.dhcp = true;
    config_dev.SSL = false;
    config_dev.timestamp = false;
    config_dev.ADC_EN = false;
    config_dev.D0_EN = false;
    config_dev.D1_EN = false;
    config_dev.D2_EN = false;
    config_dev.D4_EN = false;
    config_dev.D5_EN = false;
    config_dev.D6_EN = false;
    config_dev.D7_EN = false;
    config_dev.MQTT_port = 1883;
    config_dev.IP[0] = 192; config_dev.IP[1] = 168; config_dev.IP[2] = 1; config_dev.IP[3] = 100;
    config_dev.Netmask[0] = 255; config_dev.Netmask[1] = 255; config_dev.Netmask[2] = 255; config_dev.Netmask[3] = 0;
    config_dev.Gateway[0] = 192; config_dev.Gateway[1] = 168; config_dev.Gateway[2] = 1; config_dev.Gateway[3] = 1;
    config_dev.DNS[0] = 192; config_dev.DNS[1] = 168; config_dev.DNS[2] = 1; config_dev.DNS[3] = 1;
    config_dev.ssid = "ESSID";
    config_dev.password = "password";
    config_dev.DeviceName = "water_SENSOR";
    config_dev.MQTT_server = "MQTT server";
    config_dev.MQTT_login = "MQTT login";
    config_dev.MQTT_password = "MQTT password";
    config_dev.time_topic = "Enter topic";
    config_dev.ADC_topic = "Enter topic";
    config_dev.D0_topic = "Enter topic";
    config_dev.D1_topic = "Enter topic";
    config_dev.D2_topic = "Enter topic";
    config_dev.D4_topic = "Enter topic";
    config_dev.D5_topic = "Enter topic";
    config_dev.D6_topic = "Enter topic";
    config_dev.D7_topic = "Enter topic";
    config_dev.MQTT_interval = 10;
    WriteConfig ();
    Serial.println ("Default config applied");
    return false;
  }
}
