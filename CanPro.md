# CAN Bus Prototyping #
### Michael Vancamp - The Rajamani Tsunami ###



For prototyping of CAN Bus, I set up two CAN Bus nodes that communicate with each other over a bus. When the first node transmits a message, it lights up an LED. When the second node
receives a message, it lights up its own LED. Ideally, the LEDs will blink on and off in sync –
when one transmits, the other receives.

## I. Block Diagram ##

![http://i.imgur.com/UN6a6b2.png](http://i.imgur.com/UN6a6b2.png)

## II. Schematic ##

![http://i.imgur.com/g5dkp16.png](http://i.imgur.com/g5dkp16.png)

## III. Inputs ##
|**Input Name**|**Description of Signal**|**Expected Range**|
|:-------------|:------------------------|:-----------------|
|TXD PIC 1|Incoming messages from PIC 1. Occurs when function called.|5V|
|TXD PIC 2|Incoming messages from PIC 2. Not implemented by any current function.|0V|
|Input Voltage|Input from power supply.|5V|
|Input Ground|Ground from/to power supply.|0V|
|PIC 1 Control|Activates LED 1 when PIC 1 transmits.|5V|
|PIC 2 Control|Activates LED 2 when PIC 2 transmits.|5V|

|**Function Name**|**Description**|**Input Parameters**|**Return Value**|
|:----------------|:--------------|:-------------------|:---------------|
|MCANinit()|Sets baud rate, masks, filters, and modes.|null|null|
|MCAN\_Receive()|Checks to see if a message has been sent by another node.|null|null|
|MCAN\_Transmit()|Sends a sample message over the bus.|Chars d,e,f,g,h|null|

## IV. Programming Flowcharts ##

![http://i.imgur.com/ia5oeMT.jpg](http://i.imgur.com/ia5oeMT.jpg)

## V. Outputs ##
|**Output Name**|**Description of Signal**|**Expected Range**|
|:--------------|:------------------------|:-----------------|
|RXD PIC 1|Outgoing messages to PIC 1. Not implemented by any current function.|0V|
|RXD PIC 2|Outgoing messages to PIC 2. Sends message from bus when MCAN\_Receive() called.|0-5V|


|**T.P. Name**|**Description of Signal and measurement conditions**|**Range of Values**|
|:------------|:---------------------------------------------------|:------------------|
|1\_TXD|TXD serial input from PIC 1|0-5V|
|1\_RXD|RXD serial output to PIC 1|0V|
|2\_TXD|TXD serial input from PIC 2|0V|
|2\_RXD|RXD serial output to PIC 2|0-5V|
|VSS|Ground|0V|
|VDD|Power|5V|
|CANH|Higher voltage of CAN Bus|2.75V-4.5V|
|CANL|Lower voltage of CAN Bus|0.5V-2.25V|
|1\_Out|Control signal from PIC 1|0-5V|
|2\_Out|Control signal from PIC 2|0-5V|

![http://i.imgur.com/oXuRDTE.png](http://i.imgur.com/oXuRDTE.png)
_**Figure:Voltage vs. Time on CAN Bus after a node transmits.**_