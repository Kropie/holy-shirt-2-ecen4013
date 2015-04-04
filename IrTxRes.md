# IR Emitter Research Document #
### Kyle Grant - The Rajamani Tsunami ###



The Holy Shirt 2.0 specifications call for the ability to transmit a 940nm, 56 kHz infrared MIRP packet in all directions with a viewing angle of 45 degrees. In order to perform this action there must be at least 2 IR emitters implemented; one on the front of the shirt and one on the back of the shirt.

In order to perform this action there must be software implemented that will be able to initialize a PWM port and send the appropriate signal to the array of infrared emitters, determined by the MIRP packet documentation for the MAGE system. Once the appropriate PWM signal is sent to the IR emitters it will then be staged up via an Op Amp to provide additional current in order to maximize the radiant intensity of the IR emitters.

## I. Block Diagram ##

![http://i.imgur.com/Cthth7e.jpg](http://i.imgur.com/Cthth7e.jpg)

## II. Primary Approach ##

![http://i.imgur.com/djs4Hwh.jpg](http://i.imgur.com/djs4Hwh.jpg)
http://optoelectronics.liteon.com/upload/download/DS50-2003-020/P_100_LTE-3271BL.pdf

This IR emitter was chosen because it is the cheapest and most powerful option which adheres to the project specifications. This IR emitter will operate at a 50 degree viewing angle, exceeding the requirement of 45 degrees. It will also operate at a radiant intensity of 30mW/sr which will be powerful enough to be received at 20ft. It can also be implemented easily due to its through-hole design, meaning it could be easily mounted on the chest and back pointed in the appropriate direction.

## III. Secondary Approach ##

![http://i.imgur.com/7yGgOcN.jpg](http://i.imgur.com/7yGgOcN.jpg)
http://catalog.osram-os.com/catalogue/catalogue.do;jsessionid=7667A78B5A2190F007E2E148FD64A417?act=downloadFile&favOid=02000001000191b3000200b6

Although this alternative possesses a radiant intensity 10mW/sr more powerful than the primary option. This alternative was eliminated due to the fact that it draws more power and has a viewing angle 10° less than the primary option. This IR emitter will not meet the project requirement of a 45 degree viewing angle.

![http://i.imgur.com/WO4OyPm.jpg](http://i.imgur.com/WO4OyPm.jpg)
http://www.vishay.com/doc?81008

This alternative was eliminated due to the fact that it draws more power and has a viewing angle 6° less than the primary option causing it not to meet the 45 degree viewing angle requirement.

## IV. Data Sources ##

|Type of Datasource|URL|Used in Prototype?|
|:-----------------|:--|:-----------------|
|Datasheet|http://optoelectronics.liteon.com/upload/download/DS50-2003-020/P_100_LTE-3271BL.pdf|Yes|
|Datasheet|http://catalog.osram-os.com/catalogue/catalogue.do;jsessionid=7667A78B5A2190F007E2E148FD64A417?act=downloadFile&favOid=02000001000191b3000200b6|No|
|Datasheet|http://www.vishay.com/doc?81008|No|
|Reference Sheet|https://stillwater.sharepoint.okstate.edu/ecendesign/Training%20Documents/PIC/PIC%20Reference/ccpwm.pdf|Yes|

## V. Simulation ##

![http://i.imgur.com/OAY4IN3.jpg](http://i.imgur.com/OAY4IN3.jpg)
### Figure 1) Schematic for IR Emitter Output ###

![http://i.imgur.com/zLYOuaH.jpg](http://i.imgur.com/zLYOuaH.jpg)
### Figure 2) Transient Analysis of IR Voltage with a 56kHz Control Signal ###

## VI. Software ##

![http://i.imgur.com/wCtKicv.jpg](http://i.imgur.com/wCtKicv.jpg)
### Figure 3) Flowchart for IR Emitter Software ###

This approach was chosen because it is very simple and will utilize only one PWM port on the microcontroller. The software will receive an input from the main program which will interpret if the user wants to transmit a heal or transmit an attack. If it is to transmit an attack/heal it will send the appropriate logic 1 or 0 for the correct amount of duty cycles via the PWM port.

An alternative approach considered for the software was to utilize a GPIO port to send logic 1 or 0 and calculate the time needed for each duty cycle. However this can be done more efficiently and with less error when using a PWM signal.