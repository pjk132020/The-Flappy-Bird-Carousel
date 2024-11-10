# The-Flappy-Bird-Carousel

## Servo Motor Pair Control (file 1)
This project demonstrates the control of pairs of servo motors using the Arduino platform. Each pair of servos moves to random angles while maintaining a specified gap between them, then resets to a middle position.

### Hardware Requirements
1. Arduino board
2.Servo motors (2 per pair)
3. Connecting wires
4. Software Requirements
5. Arduino IDE
6. Servo library
7. Wiring
8. Servo 1 of each pair: Connect to pin 2
9. Servo 2 of each pair: Connect to pin 3


### Libraries
#include <Servo.h>

### Definitions
numPairs: Number of servo pairs (adjustable for testing).
servoPins1 and servoPins2: Arrays holding the pin numbers for each servo in the pairs.
gap: The gap between the two servos in a pair.
speed: Speed of movement (not used in this code but can be adjusted for future use).
minAngle, maxAngle, middleAngle: Angle limits and default middle position for the servos.

### Setup Function
Attaches each servo to its respective pin.
Initializes servos to the middle position.
moveServoToAngle Function
Moves a servo to a target angle with smooth movement by incrementing/decrementing the current angle.

### Loop Function
Generates a random angle for each servo pair.
Moves each servo in the pair to the new random position while maintaining the specified gap.
Resets servos to the middle position after a short delay.

### Usage
Connect the hardware as described in the wiring section.
Upload the code to your Arduino board.
Observe the servos moving to random positions and then resetting to the middle position.

-----------
## Stepper Motor Control with AccelStepper (file 2)
This project demonstrates the control of two stepper motors using the AccelStepper library. One motor runs continuously in the background, while the other motor can perform a “flap” motion when a button is pressed.

### Hardware Requirements
1. Arduino board
2. Two 4-wire stepper motors
3. Stepper motor drivers
4. Push button
5. Connecting wires
6. Software Requirements
7. Arduino IDE
8. AccelStepper library
9. Wiring
10. Motor 1 (Background motor): Connect to pins 12, 11, 10, 9
11. Motor 2 (Flap motor): Connect to pins 22, 23, 24, 25
12. Button: Connect to pin 3 with a pull-up resistor

### Libraries
#include <AccelStepper.h>

### Definitions
motorInterfaceType: Defines the type of stepper motor (4-wire in this case).
stepsPerRevolution: Number of steps per revolution for the stepper motor.
Motor Initialization
Motor 1: Initialized with AccelStepper on pins 12, 11, 10, 9.
Motor 2: Controlled by the StepperControl class, initialized on pins 22, 23, 24, 25.
StepperControl Class
This class encapsulates the control logic for Motor 2, including:

### Constructor: Initializes the motor with specific settings.
begin(): Sets the maximum speed and acceleration.
setTargetSpeed(): Sets the motor speed in RPM.
applyFlap(): Initiates a counterclockwise “flap” motion.
update(): Checks if the flap duration has ended and resets the speed.
run(): Runs the motor at the set speed.

### Setup Function
Initializes Motor 1 and Motor 2 settings.
Sets the button pin as input with a pull-up resistor.

### Loop Function
Runs Motor 1 continuously.
Checks if the button is pressed to apply the flap effect to Motor 2.
Updates and runs Motor 2 based on the flap duration.

### Usage
Connect the hardware as described in the wiring section.
Upload the code to your Arduino board.
Press the button to see Motor 2 perform a flap motion.
