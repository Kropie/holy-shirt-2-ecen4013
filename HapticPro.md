# Haptic Feedback Prototyping #
### Michael Vancamp - The Rajamani Tsunami ###



For prototyping the vibration motors, I set up a loop that shows how the vibration motor looks and feels as it gets shot. There are four motors on the board, like there will be on the shirt. The program alternates between the four motors, vibrating each one first with single buzzes, then a burst of consecutive buzzes, as if the player is attacked by more than one MIRP packet.

## I. Block Diagram ##

![http://i.imgur.com/s4NlR9I.png](http://i.imgur.com/s4NlR9I.png)

## II. Schematic ##

![http://i.imgur.com/4QZCUjc.png](http://i.imgur.com/4QZCUjc.png)

## III. Inputs ##

|**Input Name**|**Description of Signal**|**Expected Range**|
|:-------------|:------------------------|:-----------------|
|PIC Pin 3|Comes from Pin 3 on the PIC, a controllable output|0-3.3V|
|PIC Pin 4|Comes from Pin 4 on the PIC, a controllable output|0-3.3V|
|PIC Pin 5|Comes from Pin 5 on the PIC, a controllable output|0-3.3V|
|PIC Pin 7|Comes from Pin 7 on the PIC, a controllable output|0-3.3V|
|VCC|Supply voltage from power supply|3.3V|

|**Function Name**|**Description**|**Input Parameters**|**Return Value**|
|:----------------|:--------------|:-------------------|:---------------|
|init\_haptic()|Sets pins 3,4,5, and 7 as outputs|null|null|
|haptic()|Causes a vibration in the specified vibration motor|loc (which motor to activate)|null|

## IV. Outputs ##

|**Output Name**|**Description of Signal**|**Expected Range**|
|:--------------|:------------------------|:-----------------|
|Motor 1|Vibrates to motor 1|0-2.5V|
|Motor 2|Vibrates to motor 2|0-2.5V|
|Motor 3|Vibrates to motor 3|0-2.5V|
|Motor 4|Vibrates to motor 4|0-2.5V|

|**T.P. Name**|**Description of Signal and measurement conditions**|**Range of Values**|
|:------------|:---------------------------------------------------|:------------------|
|OUT|Output of the transistor, running to motor|0-2.44V|
|GND|Ground to/from power supply|0V|
|VCC|Supply voltage from power supply|3.3V|
|PIC\_V|Control voltage from output pin of PIC|0-3.3V|

<br>

<img src='http://i.imgur.com/nxvcVYO.png' />
<i><b>Figure: Sample waveform sent through a motor, taken on OUT pin</b></i>