# Arduino-Smart-Lamp
This is a RGB lamp built using an Arduino board. It can be toggled to display different colors, or to cycle through them automatically. It rotates on two axes using servo motors.  
  
**Pictures:**   
<img src="Images/Demo1.jpg" alt="Well Lit" width=50% height=50%><img src="Images/Demo2.jpg" alt="Dark Room" width=50% height=50%>  
  
## How It's Made:
The main assembly was created by modifying an existing lamp. The bottom servo is mounted to the base of the lamp and rotates the lower arm using a belt, while the top servo is mounted to the bottom arm and the top arm is mounted to its rotor. Both servos rotate 180 degrees. The servos are activated, and the LEDs can be turned on/off using push buttons at the base. Once turned on, 2 more push buttons can be used to toggle various colors, or the LEDs can be set to automatically cycle through different colors. The circuit uses PNP BJT transistors operating as common emitters to control the LEDs, and an Arduino UNO R4 to house the code required to operate the LEDs and servos. 
  
## To Do:
I will upload a circuit diagram of the project shortly. The lower servo that is attatched to the belt cant provide enough friction to reliably turn the lamp. I will either mount the lower arm of the lamp directly on the servo, or will do a full rebuild of the assembly using 3D printed parts. 
