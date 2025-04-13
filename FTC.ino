#include <IRremote.h>
#include <Servo.h>

const int RECV_PIN = 2;       // IR receiver connected to D2
const int SERVO_PIN = 9;      // Servo motor connected to D9

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myServo;

unsigned long lastSeenTime = 200;
bool codeSeen = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();        // Start the IR receiver
  myServo.attach(SERVO_PIN);
  myServo.write(12);  // Attach the servo to pin 9

  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
       
 
}

void loop() {
  if (irrecv.decode(&results)) {

    if (results.value != 0xE0E0F00F) { // Ignore repeat code
      Serial.print("Button Code: ");
      Serial.println(results.value, HEX);

      // If the received code matches your button, move the servo
      if (results.value == 0x2340B922) {
        myServo.write(0);    // Move to 0 degrees
        delay(500); 
        myServo.write(12);          // Stay for 0.5 seconds 

      }
        
      if (results.value == 0x5F12E8C4) {
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      } else {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
      }


    }
    irrecv.resume();  // Ready for next signal
  }
}
    

