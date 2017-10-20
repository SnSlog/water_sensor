Ticker D3_delay;
Ticker send_delay;
Ticker second_tick;

void update_time (void) {
  UnixTimestamp++;
}

void Send_Data (void) {
  send_mqtt_data = true;
  if (config_dev.ADC_EN) {
    ADC_data = analogRead (A0);
    Serial.println ("ADC data: " + (String)ADC_data);
  }
}

void D3_pressed (void) {
  D3_delay.detach ();
  if (digitalRead (D3) == 0) {
    if (!config_dev.AdminEnabled) {
      config_dev.AdminEnabled = true;
      save_cfg = true;
      Serial.println("AdminEnabled=true");
    }
    wifi_conf = true;
    Serial.println ("Start WiFi Access Point");
  } else {
    Serial.println ("RST button relesed");
    pin_cfg = true;
  }
}

void rst_btn (void) {
  detachInterrupt (D3);
  D3_delay.once (3, D3_pressed); //3 seconds wait
  Serial.println ("RST button pressed");
}

void D1_intr (void) {
  static unsigned long D1_millis_prev;
  if(millis()-50 > D1_millis_prev) {     //Ignore the interrupt if it appeared earlier than 5 ms
    D1_millis_prev = millis();
    if (digitalRead (D1) == LOW) {
        Counter1++;
        Serial.println ("Counter 1: " + (String)Counter1);
    }
  }
}

void D2_intr (void) {
  static unsigned long D2_millis_prev;
  if(millis()-50 > D2_millis_prev) {
    D2_millis_prev = millis();
    if (digitalRead (D2) == LOW) {
        Counter2++;
        Serial.println ("Counter 2: " + (String)Counter2);
    }
  }
}

void D5_intr (void) {                   //first interrupt implementation project
  static unsigned long D5_millis_prev;
  Serial.println ("D5");
  if(millis()-200 > D5_millis_prev) {
    D5_millis_prev = millis();
  	if (digitalRead (D5) == LOW) {
    	  SNS1 =! SNS1;
        Serial.println ("Sensor 1: " + (String)SNS1);
    	  send_mqtt_data = true;
      }
  }
}


void D6_intr (void) {                     
  static unsigned long D6_millis_prev;
  Serial.println ("D6");
  if(millis()-205 > D6_millis_prev) {
    D6_millis_prev = millis();
    if (digitalRead (D6) == LOW) {
        SNS2 =! SNS2;
        Serial.println ("Sensor 2: " + (String)SNS2);
        send_mqtt_data = true;
      }
  }
}

void D7_intr (void) {                     
  static unsigned long D7_millis_prev;
  Serial.println ("D7");
  if(millis()-210 > D7_millis_prev) {
    D7_millis_prev = millis();
    if (digitalRead (D7) == LOW) {
        SNS3 =! SNS3;
        Serial.println ("Sensor 3: " + (String)SNS3);
        send_mqtt_data = true;
      }
  }
}
