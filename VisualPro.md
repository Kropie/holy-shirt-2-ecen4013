# Visual Effects Prototyping #
### Kaitlin Hehmann - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/cjLxjFI.png](http://i.imgur.com/cjLxjFI.png)

_**Figure 1: Level 1 Block Diagram**_

![http://i.imgur.com/1tAow0b.png](http://i.imgur.com/1tAow0b.png)

_**Figure 2: Level 2 Block Diagram**_

## II. Schematic ##

![http://i.imgur.com/ZMCRQTV.png](http://i.imgur.com/ZMCRQTV.png)

## III. Software Flowchart ##

![http://i.imgur.com/rpkNCeS.jpg](http://i.imgur.com/rpkNCeS.jpg)

## IV. Inputs ##

| **Input Name** | **Description of Signal** | **Expected Range**|
|:---------------|:--------------------------|:------------------|
|DIN|Serial-Data Input. Data is loaded into the internal 16-bit shift register on CLK’s rising edge. |0-5V|
|LOAD|Load-Data Input. The last 16 bits of serial data are latched on LOAD’s rising edge.|0-5V|
|CLK|Serial-Clock Input. 10MHz maximum rate. On CLK’s rising edge, data is shifted into the internal shift register. On CLK’s falling edge, data is clocked out of DOUT.|0V to 5V|
|V+|Input from power supply.|5V|
|GND|Ground to/from power supply.|0V|
|ISET|Connect to VDD through a resistor to set the peak segment current.|20mA|

| **Function Name** | **Description** | **Input Parameters** | **Return Value** |
|:------------------|:----------------|:---------------------|:-----------------|
|LED\_init|This function initializes the LED bars. It sets the SDO as output, CLK as output, SDI as input, SS as output. The two SPI registers are initialized. Decode mode, scan limit, intensity, and normal operations are set up.|null|null|

## V. Outputs ##

| **Output Name** | **Description of Signal** | **Expected Range** |
|:----------------|:--------------------------|:-------------------|
|DIG 0-DIG 7|Eight-Digit Drive Lines that sink current from the display common cathode. Pulls the digit outputs to V+ when turned off.|0V or 5V Digital|
|SEG A-SEG G, SEG DP|Seven Segment Drives and Decimal Point Drive that source current to the display. When a segment driver is turned off it is pulled to GND.|0V or 5V Digital|
|DOUT|Serial-Data Output. The data into DIN is valid at DOUT 16.5 clock cycles later.|0V or 5V Digital|

| **Function Name** | **Description** | **Input Parameters** | **Return Value** |
|:------------------|:----------------|:---------------------|:-----------------|
|addr\_off()|This function turns a LED bar off depending on the address that was sent.|int addr|null|
|addr\_on()|This function turns a LED bar on depending on the address that was sent.|int addr|null|
|all\_off()|This function turns all of the LED bars off.|null|null|
|all\_on()|This function turns all of the LED bars on.|null|null|
|addr\_2thru8\_off()|This function turns bars 2-8 off.|null|null|
|addr\_3thru8\_off()|This function turns bars 3-8 off.|null|null|
|addr\_4thru8\_off()|This function turns bars 4-8 off.|null|null|
|addr\_5thru8\_off()|This function turns bars 5-8 off.|null|null|
|addr\_6thru8\_off()|This function turns bars 6-8 off.|null|null|
|addr\_7thru8\_off()|This function turns bars 7-8 off.|null|null|
|addr\_1thru2\_on()|This function turns bars 1-2 on.|null|null|
|addr\_1thru3\_on()|This function turns bars 1-3 on.|null|null|
|addr\_1thru4\_on()|This function turns bars 1-4 on.|null|null|
|addr\_1thru5\_on()|This function turns bars 1-5 on.|null|null|
|addr\_1thru6\_on()|This function turns bars 1-6 on.|null|null|
|addr\_1thru7\_on()|This function turns bars 1-7 on.|null|null|
|powerBar()|This function takes in the power level supplied by the main code and then lights up the appropriate number of LEDs.|int power|null|
|debug()|This function is used to test the LED display and communication with the PIC by turning all of the LEDs on.|null|null|
|main()|This function initializes the LEDs and then sends the power level to them.|null|null|

| **Variable Name** | **Description/Values** |
|:------------------|:-----------------------|
|int power|Power level of the Holy Shirt. 0-50 Value|

| **T.P. Name** | **Description of Signal and measurement conditions** | **Range of Values** |
|:--------------|:-----------------------------------------------------|:--------------------|
|J1|Voltage signal from driver to turn on LEDs.|0/5V Digital|
|J2|Voltage signal from driver to turn on LEDs.|0/5V Digital|
|J3|Voltage signal from driver to turn on LEDs.|0/5V Digital|
|J4|Voltage signal from driver to turn on LEDs.|0/5V Digital|
|J5|Voltage signal from driver to turn on LEDs.|0/5V Digital|

| **Debug Location** | **Description of Signal and Debug Statement Method** | **Expected Outputs** |
|:-------------------|:-----------------------------------------------------|:---------------------|
|debug()|Using the Display Test register, all of the LEDs are turned on to indicate that they are communicating with the PIC and getting power.|All LED bars are on.|