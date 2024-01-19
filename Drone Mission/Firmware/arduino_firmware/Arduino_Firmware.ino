#include <SPI.h>
#include <Ethernet.h>

// Identifying Variables
char command = 'p';

int i;
int j = 0;
String myArray[12];

// Identifying LED
int Led = 2; // Changed pin to 2 to avoid conflict with Ethernet

// Identifying DC Motors
// Front Left Motor
int motor1pin1 = 4;
int motor1pin2 = 5;
int motor1ENA = 9;

// Front Right Motor
int motor2pin1 = 6;
int motor2pin2 = 7;
int motor2ENB = 10;

// Back Left Motor
int motor3pin1 = 8;
int motor3pin2 = 9;
int motor3ENA = 6;

// Back Right Motor
int motor4pin1 = 12;
int motor4pin2 = 13;
int motor4ENB = 11;

// Ethernet settings
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Replace with your own MAC address
IPAddress ip(192, 168, 1, 100);                    // Replace with your desired IP address
EthernetServer server(80);

void LedOnFunction()
{
  digitalWrite(Led, HIGH);
  Serial.println("Led is ON");
  delay(10);
}

void LedOffFunction()
{
  digitalWrite(Led, LOW);
  Serial.println("Led is Off");
  delay(10);
}

void setup()
{
  // put your setup code here, to run once:
  // Serial Initialization For Demonstration
  Serial.begin(9600);
  Serial.println("Drone Has Started");

  // Ethernet initialization
  Ethernet.begin(mac, ip);
  server.begin();

  // Led
  pinMode(Led, OUTPUT);

  // Front Left Motor
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1ENA, OUTPUT);

  // Front Right Motor
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor2ENB, OUTPUT);

  // Back Left Motor
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor3ENA, OUTPUT);

  // Back Right Motor
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
  pinMode(motor4ENB, OUTPUT);

  // Direction of motors
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);
}

void loop()
{
  int motorPins[] = {motor1ENA, motor2ENB, motor3ENA, motor4ENB};
  int ledPins[] = { /* define your LED pins here */ };
  int powerPin; // Define your power pin

  // Wait for the incoming packet
  EthernetClient client = server.available();
  if (client)
  {
    // An Ethernet client connected
    if (client.available())
    {
      String input = client.readStringUntil('\r\n');
      if (input.startsWith("Drone_"))
      {
        // Extract values from the packet
        String values = input.substring(6);
        int tokens = values.indexOf('_');
        if (tokens >= 0)
        {
          int motorValues[4];
          int ledValues[3];
          int powerValue;

          // Extract motor values
          for (int i = 0; i < 4; i++)
          {
            int nextToken = values.indexOf('_');
            motorValues[i] = values.substring(0, nextToken).toInt();
            values = values.substring(nextToken + 1);
          }

          // Extract LED values
          for (int i = 0; i < 3; i++)
          {
            int nextToken = values.indexOf('_');
            ledValues[i] = values.substring(0, nextToken).toInt();
            values = values.substring(nextToken + 1);
          }

          // Extract power value
          powerValue = values.toInt();

          // Print the received values
          Serial.print("Motor Pins: ");
          for (int i = 0; i < 4; i++)
          {
            Serial.print(motorPins[i]);
            Serial.print(" ");
          }
          Serial.println(); // Print a new line

          Serial.print("Motor Values: ");
          for (int i = 0; i < 4; i++)
          {
            Serial.print(motorValues[i]);
            Serial.print(" ");
          }
          Serial.println(); // Print a new line

          Serial.print("LED Values: ");
          for (int i = 0; i < 3; i++)
          {
            Serial.print(ledValues[i]);
            Serial.print(" ");
          }
          Serial.println(); // Print a new line

          Serial.print("Power Value: ");
          Serial.println(powerValue);

          // Assign motor values and LED colors based on the received packet
          for (int i = 0; i < 4; i++)
          {
            analogWrite(motorPins[i], motorValues[i]);
          }
          for (int i = 0; i < 3; i++)
          {
            analogWrite(ledPins[i], ledValues[i]);
          }
          analogWrite(powerPin, powerValue);

          // Send a response packet
          sendResponse(client);
        }
      }
      client.stop();
    }
  }

  // put your main code here, to run repeatedly:
  // Wait for the incoming packet

  // Watch Dog Code
  j++;
  Serial.println(j);

  if (j == 5000)
  {
    j = 0;
    Serial.println("Drone is still active");
  }
}

// Function to send a response packet
void sendResponse(EthernetClient &client)
{
  // Format your response packet here
  String response = "Response_123_456_789"; // Replace with your actual response format
  client.print(response);
}
