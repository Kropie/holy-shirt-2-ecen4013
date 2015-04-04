# Microcontroller Prototyping #
### Kyle Lawler - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/Nb7cM5C.jpg](http://i.imgur.com/Nb7cM5C.jpg)

_**Figure 1: Level 1 Block Diagram**_

## II. Main Program Flowchart ##

![http://i.imgur.com/OBvToAS.png](http://i.imgur.com/OBvToAS.png)

_**Figure 2: Main Program Flowchart**_

## III. Function List ##
|**Function**|**Description**|
|:-----------|:--------------|
|void irreceive(void);|Simulates receiving an IR packet. Changes variables: int hapfront, int hapleft, int hapright, int hapback, int hit|
|void initialize(void);|Setup for pin directions, settings, ect|
|void absorb(void);|Keeps track of hit count in int storage variable. Increments value on hit. Used for sending correct amount of IR packets when attacking, healing, or overloading|
|void haptic(void);|Simulates sending signal to correct haptic feedback motor. Uses int hapfront, int hapleft, int hapright, int hapback to determine what direction|
|void visuals(void);|Simulates changes in visual effects. Changes are on valid hits, sending IR, and overload|
|void userinput(void);|Simulates user input of the attack and heal buttons.  Changes the int attack and int heal variables.|
|void irsend(void);|Simulates sending IR. Changes the state of either the attack or healing led based on the storage count and which user input button was pressed.|

## IV. Software Inputs ##
|**Function Name**|**Description**|**Input Parameters**|**Return Value**|
|:----------------|:--------------|:-------------------|:---------------|
|irreceive()|Receives IR signals and determines if there is a valid hit and from where. Changes variables: int hapfront, int hapleft, int hapright, int hapback, int hit|null|null|
|userinput()|Determines if the attack or heal button has been pressed. Changes variables: int attack, int heal.|null|null|

## V. Software Outputs ##
|**Function Name**|**Description of expected outputs to function**|**Input Parameters**|**Return Value**|
|:----------------|:----------------------------------------------|:-------------------|:---------------|
|irsend()|Determines if attack or healing is sent and repeated based of storage variable.|null|null|
|visuals()|Updates visuals when hit or sending IR|null|null|
|haptic()|Signals haptic feedback to turn on based on directions hit or overload|null|null|
|absorb()|Stores and changes hit count variable when hit by or sending IR|null|null|

## VI. Signals at Test Points ##
|**T.P. Name**|**Description of Signal and measurement conditions**|**Range of Values**|
|:------------|:---------------------------------------------------|:------------------|
|Hit received x4|Change state of pins C (4 – 7) based on simulated hit direction|On or Off|
|Haptic x4|Change state of pins B (4 – 7) based on simulated hit direction|On or Off|
|Visuals Update|Change state of pin A1 when simulating being hit by or sending IR|On or Off|
|Send Attack|Change state of pin C0 for each simulated sent attack packet|On or Off|
|Send Heal|Change state of pin C3 for each simulated sent healing packet|On or Off|

![http://i.imgur.com/zMFsqrm.jpg](http://i.imgur.com/zMFsqrm.jpg)

_**Figure 3: Test Point Matrix**_

  * Blank boxes are no change.
  * Asterisks indicate changes based on hit count.