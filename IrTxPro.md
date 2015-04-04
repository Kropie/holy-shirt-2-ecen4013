# IR Emitter Prototyping #
### Kyle Grant - The Rajamani Tsunami ###



## I. Block Diagram and Schematics ##

![http://i.imgur.com/TBiXqIw.png](http://i.imgur.com/TBiXqIw.png)

_**Figure 1: Block Diagram**_

![http://i.imgur.com/yWXtaNE.png](http://i.imgur.com/yWXtaNE.png)

_**Figure 2: Schematic**_

![http://i.imgur.com/17ojaBy.png](http://i.imgur.com/17ojaBy.png)

_**Figure 3: Software Flowchart**_

## II. Software Inputs ##

|**Input Name**|**Description of Signal**|**Expected Range**|
|:-------------|:------------------------|:-----------------|
|Control Signal|The high and low signal, which determines when the emitters are on and off|0V-.6V|
|VCC|A constant 5V power source, which will power the IR emitters, whenever they are determined to be on by the control signal|5V|
|GND|A constant 0V that is used to complete the circuit of both the control signal and VCC|0V|

## III. Software Outputs ##
|**Output Name**|**Description of Signal**|**Expected Range**|
|:--------------|:------------------------|:-----------------|
|Heal|A 56kHz data packet that has 4 specified time quanta that correspond with a heal packet as listed in the MAGE documentation|0V-.6V|
|Attack|A 56kHz data packet that has 4 specified time quanta that correspond with an attack packet as listed in the MAGE documentation|0V-.6V|

|**Function Name**|**Description**|**Input Parameters**|**Return Value**|
|:----------------|:--------------|:-------------------|:---------------|
|signal\_on|Outputs an on signal at 56kHz for the number of duty cycles specified in the input parameters on pin 26|Int – The number of duty cycles|Null|
|signal\_off|Outputs an off signals at 56kHz for the number of duty cycles specified in the input parameter on pin 26|Int – The number of duty cycles|Null|
|attack|Uses signal\_on and signal off to generate the correct MIRP packet corresponding to an attack packet|Void|Null|
|heal|Uses signal\_on and signal off to generate the correct MIRP packet corresponding to a heal packet|Void|Null|

![http://i.imgur.com/oYKrViw.png](http://i.imgur.com/oYKrViw.png)

_**Figure 4: Input Waveform of a Heal Packet**_

![http://i.imgur.com/VmZSMLd.png](http://i.imgur.com/VmZSMLd.png)

_**Figure 5: Input Waveform of a Attack Packet**_

## IV. Signals at Test Points ##
|**T.P. Name**|**Description of Signal and measurement conditions**|**Range of Values**|
|:------------|:---------------------------------------------------|:------------------|
|Control Signal|The MIRP packet signal that is going to be amplified to the IR emitters.|0V-0.6V|
|VCC|A constant 5V supplied via the power supply|5V|
|OUT|The amplified control signal via the transistor and the power supply|0V-4.3V|
|GND|A constant 0V provided via the power supply|0V|

## V. Prototyping Pictures ##

![http://i.imgur.com/J9E1p45.jpg](http://i.imgur.com/J9E1p45.jpg)

![http://i.imgur.com/siQcd4g.jpg](http://i.imgur.com/siQcd4g.jpg)