# Week 7
## Thursday, March 7th, 2024
### Time
- 8:30am - 9:20am
### Attendees/Role
- Nathan
- Ethan T
- Ethan H
- Nermeen
- Thomas
### Decisions Made
- Ethan T and Nermeen worked on distance sensor and motor code and tested on an ESP-32
- Nathan, Ethan H, and Thomas worked on testing encryption code on an ESP-32
    - The code worked, however, the encrypted data will need to be converted into JSON format and a new table will need to be created in PostgREST
- Nathan and Ethan T went to Russ basement to test motor and motor drivers on ESP-32 with voltages of 3.7 and 6.5. Both cases were successful
### Questions or Concerns
- Our battery is 3.7V, however, a design sheet specifies that we need 6.5V for our motor driver.
    - From testing, we found that the motor driver still works with only 3.7V, but a new battery can be purchased if necessary
- Our motors are not waterproof
    - We have the budget to buy new motors, or we can use our waterproof sealant to waterproof the motors