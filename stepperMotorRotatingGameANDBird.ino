#include <AccelStepper.h>

#define motorInterfaceType 4  // 4-wire stepper motor
#define stepsPerRevolution 200  // Change if your motor has a different step count

// Motor 1 (Background motor)
AccelStepper motor1(motorInterfaceType, 12, 11, 10, 9);

// Motor 2 (Flap motor)
#define buttonPin 3  // Button to apply a "flap" counterclockwise effect

class StepperControl {
  private:
    AccelStepper stepper;  // AccelStepper instance within the class
    int maxSpeed;
    int acceleration;
    int defaultRPM;
    int flapRPM;
    int flapDuration;  // Duration of counterclockwise motion in milliseconds
    unsigned long flapStartTime;
    bool isFlapping;

  public:
    // Constructor for StepperControl
    StepperControl(int interfaceType, int pin1, int pin2, int pin3, int pin4, int maxSpeed, int acceleration, int defaultRPM, int flapRPM, int flapDuration)
      : stepper(interfaceType, pin1, pin2, pin3, pin4), maxSpeed(maxSpeed), acceleration(acceleration), defaultRPM(defaultRPM), flapRPM(flapRPM), flapDuration(flapDuration), isFlapping(false) {}

    // Initialize stepper settings
    void begin() {
      stepper.setMaxSpeed(maxSpeed);
      stepper.setAcceleration(acceleration);
      setTargetSpeed(defaultRPM);  // Set initial clockwise speed
    }

    // Set target speed in RPM, converting to steps per second
    void setTargetSpeed(int rpm, bool counterClockwise = false) {
      float stepsPerSecond = (rpm * stepsPerRevolution) / 60.0;
      stepper.setSpeed(counterClockwise ? -stepsPerSecond : stepsPerSecond);
    }

    // Apply the flap effect
    void applyFlap() {
      isFlapping = true;
      flapStartTime = millis();
      setTargetSpeed(flapRPM, true);  // Set to high RPM in counterclockwise direction
    }

    // Check if the flap duration has ended
    void update() {
      if (isFlapping && (millis() - flapStartTime >= flapDuration)) {
        isFlapping = false;
        setTargetSpeed(defaultRPM);  // Return to default clockwise speed
      }
    }

    // Run the stepper at the set speed
    void run() {
      stepper.runSpeed();
    }
};

// Instantiate StepperControl for Motor 2 with specific motor settings
StepperControl motor2(motorInterfaceType, 22, 23, 24, 25, 1000, 500, 3000, 12000, 500);  // 500 ms flap duration

void setup() {
  // Initialize Motor 1 settings
  motor1.setMaxSpeed(1000); // Maximum steps per second
  motor1.setAcceleration(200); // Acceleration in steps per second^2
  int targetRPM1 = 1000;  // Set your target RPM for Motor 1
  float stepsPerSecond1 = (targetRPM1 * stepsPerRevolution) / 60.0;
  motor1.setSpeed(stepsPerSecond1);

  // Initialize Motor 2 settings
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
  motor2.begin();  // Initialize motor 2 settings
}

void loop() {
  // Run Motor 1 at the set speed
  motor1.runSpeed();

  // Check if button is pressed for Motor 2
  if (digitalRead(buttonPin) == LOW) {
    motor2.applyFlap();  // Apply a counterclockwise "flap" for Motor 2
  }
  else if(digitalRead(buttonPin) == HIGH){
  motor2.update();  // Update Motor 2 direction based on flap duration
  motor2.run();  // Run Motor 2 at the set speed
  }
}
