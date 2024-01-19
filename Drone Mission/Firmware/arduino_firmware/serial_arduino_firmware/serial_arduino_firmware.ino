// Identifying Variables
char command = 'p';

int i;
int j = 0;
String myArray[12];

// Identifying LED Pins
// redPin = A0
// greenPin = A1
// bluePin = A2

// Identifying DC Motors
// Front Left Motor
int motor1pin1 = 2;
int motor1pin2 = 4;
int motor1ENA = 3;

// Front Right Motor
int motor2pin1 = 6;
int motor2pin2 = 7;
int motor2ENB = 5;

// Back Left Motor
int motor3pin1 = 8;
int motor3pin2 = 9;
int motor3ENA = 10;

// Back Right Motor
int motor4pin1 = 12;
int motor4pin2 = 13;
int motor4ENB = 11;

int countOccurrences(const String& str, char target) {
  int count = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == target) {
      count++;
    }
  }
  return count;
}

void setup()
{
  // put your setup code here, to run once:
  // Serial Initialization For Demonstration
  Serial.begin(9600);
  
  // Led
  pinMode(A0, OUTPUT); // Red
  pinMode(A1, OUTPUT); // Green
  pinMode(A2, OUTPUT); // Blue

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
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);
  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);

  // Initially motors start off
  analogWrite(motor1ENA, 0);
  analogWrite(motor2ENB, 0);
  analogWrite(motor3ENA, 0);
  analogWrite(motor4ENB, 0);
}

void loop()
{
  int motorPins[] = {motor1ENA, motor2ENB, motor3ENA, motor4ENB};
  int ledPins[] = {A0, A1, A2};

  // Watch Dog Code
  static unsigned long lastPacketTime = millis();
  if (millis() - lastPacketTime > 10000)
  {
    // No packet received in the last 10 seconds
    // Return false and assign motors for hovering
    lastPacketTime = millis(); // Reset the timer
//    Serial.println("No packet received. Drone is hovering.");

    // Assign motor values for hovering (150 is just an example value)
    for (int i = 0; i < 4; i++)
    {
      analogWrite(motorPins[i], 150);
      analogWrite(ledPins[i], 0);
    }
    return; // Exit the loop
  }

  // Wait for the incoming packet
  if (Serial.available() > 0) 
  {
    // Read from the Serial Port
    String input = Serial.readString();
    
    if (input.startsWith("firmware_Drone_")) 
    {
      // Extract values from the packet
      String values = input.substring(15);
      int underscoreCount = countOccurrences(values, '_');

      // Check if the packet has the correct number of underscores
      if (underscoreCount == 6) 
      {
        int motorValues[4];
        int ledValues[3];

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

        // Print the received values
        Serial.print("Motor Pins: ");
        for (int i = 0; i < 4; i++) 
        {
          Serial.print(motorPins[i]);
          Serial.print(" ");
        }

        Serial.print("Motor Values: ");
        for (int i = 0; i < 4; i++) 
        {
          Serial.print(motorValues[i]);
          Serial.print(" ");
        }

        Serial.print("LED Values: ");
        for (int i = 0; i < 3; i++) 
        {
          Serial.print(ledValues[i]);
          Serial.print(" ");
        }

        // Assign motor values and LED colors based on the received packet
        for (int i = 0; i < 4; i++) 
        {
          analogWrite(motorPins[i], motorValues[i]);
        }
        for (int i = 0; i < 3; i++) 
        {
          analogWrite(ledPins[i], ledValues[i]);
        } 

        lastPacketTime = millis();
      }
      else
      {
        // Ignore the packet if it doesn't match the expected format
      }
    }
  }
}
