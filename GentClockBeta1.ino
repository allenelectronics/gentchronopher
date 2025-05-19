#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char* ssid     = "VM-Allen-IOT";
const char* password = "HighamLaneSchool02!";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

void setup() {
  // Declare Output Pins
  pinMode(32, OUTPUT); // 24V Motor Drive 1
  pinMode(33, OUTPUT); // 24V Motor Drive 2
  pinMode(2, OUTPUT); // D2 (GPIO 2) as output for LED indicator

  digitalWrite(32, LOW);  
  digitalWrite(33, LOW);
  digitalWrite(2, LOW);   // Make sure LED is off at startup

  // Initialize Serial Monitor
  delay(1000);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Once connected
  digitalWrite(2, HIGH);  // Turn on LED D2

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);
  Serial.println("");
  delay(3000);

  
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);

}

String prevMinute = "";

void loop() {
  timeClient.update(); // Refresh the time
  String currentTime = timeClient.getFormattedTime();
  String currentMinute = currentTime.substring(3, 5); // Extract MM from HH:MM:SS

  if (currentMinute != prevMinute) {
    int minuteValue = currentMinute.toInt();

    if (minuteValue % 2 == 0) {
      // Even minute
      Serial.println("Even minute: " + currentMinute);
      digitalWrite(32, HIGH);  
      digitalWrite(33, LOW);
      delay(200);
      digitalWrite(32, LOW);  
      digitalWrite(33, LOW);  
      delay(800);
    } else {
      // Odd minute
      Serial.println("Odd minute: " + currentMinute);
       digitalWrite(32, LOW);
      digitalWrite(33, HIGH);
      delay(200);
      digitalWrite(32, LOW);  
      digitalWrite(33, LOW);  
      delay(800);  
    }

    prevMinute = currentMinute; // Update stored minute
  }

  delay(1000); // Check every second
}
