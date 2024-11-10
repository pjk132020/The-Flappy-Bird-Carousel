#include <Servo.h>

const int numPairs = 1; // Adjusted for testing with two pairs
Servo servos1[numPairs]; // Array to hold the first servo of each pair
Servo servos2[numPairs]; // Array to hold the second servo of each pair
int servoPins1[numPairs] = {2}; // Pins for the first servos of each pair
int servoPins2[numPairs] = {3}; // Pins for the second servos of each pair

int gap = 20;  // The gap between the two servos in a pair
int speed = 5; // Speed of movement
int minAngle = 0;
int maxAngle = 135;
int middleAngle = 90; // Regular middle position

void setup() {
  for (int i = 0; i < numPairs; i++) {
    servos1[i].attach(servoPins1[i]);
    servos2[i].attach(servoPins2[i]);
    
    // Initialize servos to starting positions
    servos1[i].write(middleAngle);
    servos2[i].write(middleAngle);
  }
}

void moveServoToAngle(Servo &servo, int targetAngle) {
  int currentAngle = servo.read();
  while (currentAngle != targetAngle) {
    currentAngle += (targetAngle > currentAngle) ? 1 : -1;
    servo.write(currentAngle);
    delay(10); // Adjust delay for smoother movement
  }
}

void loop() {
  for (int i = 0; i < numPairs; i++) {
    // Generate a random angle for the new position
    int randomAngle = random(minAngle, maxAngle);
    
    // Move servos to the new random position for this pair
    moveServoToAngle(servos1[i], randomAngle);
    moveServoToAngle(servos2[i], randomAngle + gap);
    delay(100); // Pause to observe the random position
    
    // Reset servos to regular gap with both at middleAngle
    moveServoToAngle(servos1[i], middleAngle);
    moveServoToAngle(servos2[i], middleAngle);
    delay(500); // Pause to observe the regular gap position
  }
}
