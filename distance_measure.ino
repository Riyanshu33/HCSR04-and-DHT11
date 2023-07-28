#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define Type DHT11
int sensePin = 2;
DHT HT(sensePin, Type);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 11;
const int echoPin = 12;
int duration;
float distance;
float humidity;
float tempC;
float velocity;
int newbuttonval;
int oldbuttonval = 0;

const int buttonPin = 3;     // The pin connected to the button
bool storeDistance = false;  // Flag to indicate whether to store and display distance
int storeDistanceTime;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  HT.begin();
  delay(100);
}

void loop() {
  newbuttonval = digitalRead(buttonPin);
  Serial.println(digitalRead(buttonPin));

  // Code for sending pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Showing distance
  if (duration < 0) {
    Serial.println("Complex Object!");
    lcd.setCursor(0, 1);
    lcd.print("Complex Surface");
  } else {
    // Serial.println(duration);
    // Serial.print("Distance in metres: ");
    // Serial.println(distance);
    // Store and display the distance if the flag
    if (newbuttonval != oldbuttonval) {
      oldbuttonval = newbuttonval;
      if (newbuttonval == LOW) {
        storeDistance = !storeDistance;
        delay(100);
      }
    }
    if (storeDistance) {
      // Serial.print("old:");
      // Serial.println(oldbuttonval);
      // Serial.print("new:");
      // Serial.println(newbuttonval);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Distance:");
      lcd.setCursor(9, 0);
      lcd.print(distance);
      lcd.setCursor(13,0);
      lcd.print("m");
      lcd.setCursor(0, 1);
      lcd.print("Accuracy:0.25%");
      delay(500);
      lcd.clear();
    } 
    else 
    {
      // Serial.print("Humidity: ");
      // Serial.print(humidity);
      // Serial.print(" Temperature in C: ");
      // Serial.println(tempC);
      distance = (duration * 0.000343) / 2;
      // LCD Display
      // lcd.setCursor(0, 0);
      // lcd.print("Temp:");
      // lcd.setCursor(6, 0);
      // lcd.print(tempC);
      // lcd.setCursor(12, 0);
      // lcd.print("C");

      // delay(350);

      // lcd.setCursor(0, 0);
      // lcd.print("Humidity:");
      // lcd.setCursor(9, 0);
      // lcd.print(humidity);

      // delay(350);
      delay(300);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Distance: ");
      lcd.setCursor(5, 1);
      lcd.print(distance);
      lcd.setCursor(9, 1);
      lcd.print("m");
    }
  }
}