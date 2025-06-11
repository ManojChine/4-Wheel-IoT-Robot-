
#define IN1 23  // Direction Control
#define IN2 22  // Direction Control
#define ENA 21  // Speed Control (PWM)

// Right Motor Pins
#define IN3 19  // Direction Control
#define IN4 18  // Direction Control
#define ENB 5   // Speed Control (PWM)

// IR Sensor Pins
#define ir_left  34  // Left IR Sensor
#define ir_right 35  // Right IR Sensor

// Motor Speed Values (0-255 scaled for ESP32 PWM range 0-1023)
int defaultSpeed = 250;  // Default speed for forward motion
int turnSpeed =450;     // Speed for turning movements

// PWM Channels
#define PWM_FREQ 5000
#define PWM_RESOLUTION 10
#define ENA_CHANNEL 0
#define ENB_CHANNEL 1

void setup() {
    // Set motor control pins as OUTPUT
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    // Set IR sensor pins as INPUT
    pinMode(ir_left, INPUT);
    pinMode(ir_right, INPUT);

    // Initialize PWM channels
    ledcSetup(ENA_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(ENB_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(ENA, ENA_CHANNEL);
    ledcAttachPin(ENB, ENB_CHANNEL);
    
    // Initialize serial communication for debugging
    Serial.begin(115200);

    // Set default motor speed
    ledcWrite(ENA_CHANNEL, defaultSpeed);
    ledcWrite(ENB_CHANNEL, defaultSpeed);
}

void loop() {
    // Read IR Sensor Values
    int left_detect = digitalRead(ir_left);
    int right_detect = digitalRead(ir_right);

    // Debugging - Print Sensor Values
    Serial.print("Left Sensor: ");
    Serial.print(left_detect);
    Serial.print(" | Right Sensor: ");
    Serial.println(right_detect);

    // Decision Logic
    if (left_detect == HIGH && right_detect == LOW) {
        turnRight();
    } 
    else if (left_detect == LOW && right_detect == HIGH) {
        turnLeft();
    } 
    else if (left_detect == HIGH && right_detect == HIGH) {
        moveForward();
    } 
    else {
        stopMotors();
    }

    delay(100);  
}
void moveForward() {
    Serial.println("Moving Forward...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(ENA_CHANNEL, defaultSpeed);
    ledcWrite(ENB_CHANNEL, defaultSpeed);
}

void moveBackward() {
    Serial.println("Moving Backward...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(ENA_CHANNEL, defaultSpeed);
    ledcWrite(ENB_CHANNEL, defaultSpeed);
}

// Function to Stop Motors
void stopMotors() {
    Serial.println("Stopping...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    ledcWrite(ENA_CHANNEL, 0);
    ledcWrite(ENB_CHANNEL, 0);
}

// Function to Turn Left
void turnLeft() {
    Serial.println("Turning Left...");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    ledcWrite(ENA_CHANNEL, turnSpeed);
    ledcWrite(ENB_CHANNEL, turnSpeed);
}

// Function to Turn Right
void turnRight() {
    Serial.println("Turning Right...");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    ledcWrite(ENA_CHANNEL, turnSpeed);
    ledcWrite(ENB_CHANNEL, turnSpeed);
}
