# Objectives 

**Goal**: To create a robot that can autonomously clean the surface of a residential pool and determine its quality. The robot will also have a user interface that will display the metrics of water quality. 

 

**Objective 1**: The robot can collect trash and debris on the surface of a body of freshwater. 
- Trash and debris refer to smaller pieces of waste that float on the surface of the water, such as wrappers, bottles, and aluminum cans, and would be unable to collect larger waste.  

 

**Objective 2**: The robot can take measurements of the water quality. 
- Water quality refers to four main statistics about the body of water the robot resides in: temperature, pH level, total dissolved solids, and turbidity. The robot periodically measures these numbers and transmits them wirelessly to be stored in a database.  

 

**Objective 3**: A wireless user interface can display metrics measured by the robot. 
- The User Interface could refer to a website that is hosted separately that displays the temperature, the pH level, turbidity, and total dissolved solids of the water; the four metrics the robot collects. 

 

**Objective 4**: The robot can autonomously move across the surface of the water. 
 - The robot moves across the surface of the water by use of propellors, avoiding collision by utilizing sensors to detect walls. 

# Assumptions 

| No. | Assumption                                                                                                        |
|-----|-------------------------------------------------------------------------------------------------------------------|
| 1   | The AquaClean Pro will only be operated in residential pools.                                                     |
| 2   | The AquaClean Pro will only pick up trash on the surface of the water.                                            |
| 3   | Trash collected by the AquaClean Pro will be no larger than half the size of the attached pool skimmer.           |
| 4   | User will provide power to sufficiently charge the AquaClean Pro.                                                 |
| 5   | User will provide an internet service for the AquaClean Pro.                                                      |
| 6   | The AquaClean Pro functions as a residential pool cleaning robot without an internet service provided by the user. |
| 7   | The AquaClean Pro will not operate in a body of water less than 2 feet deep.                                      |
| 8   | User will not be inside of pool during cleaning.                                                                  |
| 9   | User will empty the AquaClean Pro’s pool skimmer net when it’s full.                                              |

# Requirements

| Req No. | Obj No. | Requirement                                                                                      |
| ------- | ------- | ------------------------------------------------------------------------------------------------ |
| 1.0     | 1, 4    | AquaClean Pro must collect buoyant solid waste on the surface of a residential pool.             |
| 1.1     | 1, 4    | AquaClean Pro must haul at least 0.5 pounds.                                                     |
| 2.0     | 2       | AquaClean Pro must measure water quality.                                                        |
| 2.0.1   | 2       | The AquaClean Pro must store the water quality data.                                             |
| 2.0.2   | 2, 3    | AquaClean Pro must transmit water quality data over a wireless internet connection at least once every 10 seconds when in operation. |
| 2.0.3   | 3       | AquaClean Pro must display water quality data to a web-accessible user interface.                |
| 2.0.4   | 2       | AquaClean Pro shall collect accurate water quality data within an acceptable certainty range.    |
| 3.0     | 4       | AquaClean Pro must identify surrounding walls.                                                   |
| 3.0.1   | 4       | AquaClean Pro must navigate surrounding walls during operation.                                  |
| 4.0     | 4       | AquaClean Pro must float on the pool's surface.                                                  |
| 4.1     | 4       | The AquaClean Pro must reach a speed of at least 20cm/s in a forward direction relative to the device. |
| 4.2     | 4       | The AquaClean Pro must rotate about a fixed position.                                            |
| 4.2.1   | 4       | The AquaClean Pro must have a full 360° rotation range in water along its vertical axis (Yaw).   |
| 5.0     | 3       | AquaClean Pro’s battery level must be measured.                                                  |
| 5.0.1   | 3       | AquaClean Pro must transmit battery power level over a wireless internet connection at least once every 10 seconds when in operation. |
| 5.0.2   | 3       | AquaClean Pro must display battery power data to a web-accessible user interface.                |
| 5.1     | 3, 4    | AquaClean Pro must alert the user once it reaches 20% remaining battery power or lower.          |
| 6.0     | 4       | AquaClean Pro is water resistant to a depth of up to 2 feet.                                     |
| 6.1     | 2       | AquaClean Pro’s water quality sensors’ probes must be waterproof.                                |
| 7.0     | 2, 3    | AquaClean Pro shall connect to a wireless network.                                               |
| 7.0.1   | 2, 3    | The AquaClean Pro shall transmit data to a web-accessible user interface.                        |
| 7.1     | 2, 3    | The AquaClean Pro shall use end to end encryption for wireless communication.                    |
| 8.0     | 4       | The AquaClean Pro’s battery shall be charged from an external Micro USB power supply.            |

## Definitions
**Buoyant solid waste** – Any objects that are on the surface of the residential pool, including but not limited to leaves, insects, and plastic wrappers. 

**Operation** – The robot’s state while skimming and cleaning the body of water. 

**Water quality data** – Temperature and pH measurements. 

**Acceptable certainty range** – Allowable uncertainty of sensors: 

- pH: ±0.1

- Temperature: ±1°C 

# Constraints 

| No.       | Constraint                                                                                           |
| --------- | ---------------------------------------------------------------------------------------------------- |
| 1.0       | Total bill of materials shall not exceed $300 without Faculty Advisor approval.                      |
| 2.0       | The AquaClean Pro must fit within a box that has dimensions 45cm x 45cm x 60cm.                      |
| 3.0       | The AquaClean Pro weight must not exceed 20 kg before any trash is collected.                        |
| 4.0       | The AquaClean Pro’s speed shall not exceed 50cm/s.                                                   |
| 5.0       | The battery power shall not exceed 10Ah.                                                             |
| 6.0       | The AquaClean Pro wireless communication must adhere to one or more published IEEE standards.        |
| 6.0.1     | The AquaClean Pro shall comply with IEEE 802.11 for wireless communication standards.                |
| 7.0       | The AquaClean Pro must use end to end encryption for wireless communication.                         |
| 8.0       | Parts shall be sourced from WSU approved vendors: Digikey, Mouser, Robot Shop, MaxBotix, Midwest Surplus Electronics, or SparkFun. The list of approved vendors is subject to change. Updated lists of approved vendors will be posted in Pilot. |
| 9.0       | AquaClean Pro’s water quality and distance sensors’ probes must be waterproof to IP67 or higher.     |

