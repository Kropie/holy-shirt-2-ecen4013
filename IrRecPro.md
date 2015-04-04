# IR Reception Prototyping #
### Ty Prather - The Rajamani Tsunami ###



## I. Block Diagrams and Schematics ##

![http://i.imgur.com/kS130UR.png](http://i.imgur.com/kS130UR.png)

_**Figure 1: Block Diagram**_

![http://i.imgur.com/3w2p9vv.png](http://i.imgur.com/3w2p9vv.png)

_**Figure 2: Level 2 Block Diagram**_

![http://i.imgur.com/sq6eVNE.jpg](http://i.imgur.com/sq6eVNE.jpg)

_**Figure 3: Schematic and Software Flowchart**_

## II. Inputs ##

|**Input Name**|**Description of Signal**|**Expected Range**|
|:-------------|:------------------------|:-----------------|
|MIRP IR x 4|4 Channels of MIRP|0V or 5V @ 56kHz|

|**Function Name**|**Description**|**Input Parameters**|
|:----------------|:--------------|:-------------------|
|irISR|Actual interrupt service routine|Read int. flags|
|main|Main loop to initialize and strobe status LED|null|
|high\_vector|Pointer to irISR from high priority interrupt|Interrupt Trigger|

## III. Outputs ##

|**Output Name**|**Description of Signal**|**Expected Range**|
|:--------------|:------------------------|:-----------------|
|INT0|Interrupt Pin 0 - Front IR Receiver signal|0V or 5V digital|
|INT1|Interrupt Pin 1 - Left IR Receiver signal|0V or 5V digital|
|INT2|Interrupt Pin 2 - Right IR Receiver signal|0V or 5V digital|
|INT3|Interrupt Pin 3 - Back IR Receiver signal|0V or 5V digital|

|**Function Name**|**Description**|**Output Variables**|
|:----------------|:--------------|:-------------------|
|irISR|Actual interrupt service routine|Set "hit" variable|
|main|Main loop to initialize and strobe status LED|null|
|high\_vector|Pointer to irISR from high priority interrupt|null|

|**Variable Name**|**Description/Values**|
|:----------------|:---------------------|
|hit|Variable representing the presence and location of an IR attack|
**0 - No hit present** 1 - Hit at IR Receiver 1
**2 - Hit at IR Receiver 2** 3 - Hit at IR Receiver 3
**4 - Hit at IR Receiver 4**

## IV. Signals at Test Points ##

|**T.P. Name**|**Description of Signal and measurement condition**|**Range of Values**|
|:------------|:--------------------------------------------------|:------------------|
|J2|Signal from IR Receiver 1. Used to view incoming IR data.|0/5V Digital|
|J3|Signal from IR Receiver 2. Used to view incoming IR data.|0/5V Digital|
|J4|Signal from IR Receiver 3. Used to view incoming IR data.|0/5V Digital|
|J5|Signal from IR Receiver 4. Used to view incoming IR data.|0/5V Digital|

|**Debug Location**|**Description of signal and debug statement method**|**Expected outputs**|
|:-----------------|:---------------------------------------------------|:-------------------|
|irISR - top|Used to test for interrupt received|LED flash on interrupt|

![http://i.imgur.com/KASf5ep.png](http://i.imgur.com/KASf5ep.png)

_**Figure 4: MIRP Data from IR receiver test point**_

## V. Prototyping Pictures ##

![http://i.imgur.com/Ar8hi6e.jpg](http://i.imgur.com/Ar8hi6e.jpg)

![http://i.imgur.com/dRVLmOc.jpg](http://i.imgur.com/dRVLmOc.jpg)

![http://i.imgur.com/YudvLab.jpg](http://i.imgur.com/YudvLab.jpg)