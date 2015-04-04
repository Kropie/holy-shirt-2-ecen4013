# Microcontorller Research Document #
### Kyle Lawler - The Rajamani Tsunami ###



## Requirements ##
**Requires 5V or less
  * Power supply is 5V** Memory of 32KB
  * Previous years main code averaged 15KB in size. Might have other files so extra memory needed.
**Clock speed much greater than 56kHz
  * Needs to be fast enough to interpret MIRP packets** GPIO x 9
  * 4 for haptic feedback signal
  * 4 for Visuals
  * 1 for IRTx
**PWM x 1
  * IRTx backup** UART
    * For CAN Bus
**External Interrupt Pins x 6
  * 2 for User Input
  * 4 for IR Receiver**

## Option 1 ##
**PIC18F25K80**
Microchip offers free 2 free samples per person on their website.  The PICs were first narrowed down to PIC18F type chips. This is because PIC18s are made to utilize C programming and this would be preferred over assembly.  The PICs were then narrowed to only PIC18F258x because these would be 28 pin micro controllers with 32KB of memory and CAN support. The 28 pin specification was chosen because the smaller option may have 18 pin PICs that may not have enough signal pins as some will be for powering the device and we need a minimum of 13 plus pins for visuals. The CAN support as a requirement because it is available for free and adds a backup in case we have problems with our chosen CAN hardware.  The micro controllers that fit these requirements are the PIC18F258, PIC18F2580, PIC18F2585, and PIC18F25K80.  The 2580 is an improved 258 so the 258 can be excluded.  The PIC18F25K80 is chosen because it offers extra PWMs and timers which may be used for backup while the PIC18F2585 only offers extra memory which should not be an issue since the 32KB constraint was chosen based on around 15KB being needed.

![http://i.imgur.com/hsDEP5l.jpg](http://i.imgur.com/hsDEP5l.jpg)

![http://i.imgur.com/8nFJ43b.jpg](http://i.imgur.com/8nFJ43b.jpg)

![http://i.imgur.com/RGhhC6Z.jpg](http://i.imgur.com/RGhhC6Z.jpg)

If more GPIO pins are needed, the same procedure to pick a chip can be used but instead PIC18F458x microcontrollers will be looked at.  The PIC18F45K80 is the equivalent of the PIC18F25K80 but with 44 pins instead of 28.

## Option 2 ##
**Arduino Pro(328)**

From the Arduino website, the compare page was used to look for micro controllers that would fit requirements listed. Looking though the list, only 3 boards matched the voltage requirement and 32KB of memory. One board comes with a blue tooth module giving extra features that we do not need. So the options are the Fio and Pro(328). The micro controller itself is the same for both boards so based on price the Pro (328) is chosen.

![http://i.imgur.com/V9rs5F5.jpg](http://i.imgur.com/V9rs5F5.jpg)

![http://i.imgur.com/IGVk3pY.jpg](http://i.imgur.com/IGVk3pY.jpg)

To make this work, hardware must be added to reduce pins needed by haptic feedback, visuals, and ir receiver. The user inputs can but put through the analog input pins freeing up two GPIO pins but these will no longer be able to trigger an interrupt so the state of these pins will have to be polled and additional software will need to be written to determine the state of the pin. Also the cost for this option is much higher than using a PIC.  The team feels more comfortable programming an Arduino so the price may be ignored but the amount of pins available will make things difficult.  If an Arduino with more pins is needed, the Leanardo would be a good fit but it requires 7V and our power source will have to be reconsidered.

## Main Loop and Power Level Manager ##

The main loop will be calling other team member’s functions and set the general structure of the program.

**Functions**
|Function|Description|
|:-------|:----------|
|initialize()|Configure things like port, tris, ect. and Set variables = 0 |
|SendAttack()|Creates signal to send MIRP attack packet|
|SendHeal()|Creates signal to send MIRP heal packet|
|updateVisuals()|Sends updated signals to visual LEDs|
|absorb()||Increments the current hit count.|
If hit count over maximum send signal to all haptic feedback, call updateVisuals(), and call sendDead().
If hit count under maximum. Send signal to correct haptic feedback motor and call updateVisuals().
|sendDead()|Sends the im dead signal to CAN BUS|
|receiveIR()|This will be a function written by another team member to check for valid MIRP attack packets.  It will need to be added to the interrupt setup since calling functions from interrupts causes slow downs.|
|receiveUserInput|This will be added to the interrupt setup and will change the variable of attack to true if the attack button is pressed. It will also change the variable of heal to true if the healing button is pressed.|
|haptic(8bit input)|Function to control haptic motors. First 2 bits determine what motors to vibrate. Next three bits give magnitude or length of vibrate. Last bit determines if shirt overloaded. This would reduce some work for the absorb function but make code easier to make sense of.|

I will be responsible for creating initialize(), getStorage(), storageReset(), and absorb() and the other functions will be written by the other team members.

Another way to handle sending IR packets based on our hit count is to make sendAttack(), and sendHeal() have the storage variable as a parameter. This will mean that theloop will be done within them making the main code look cleaner

## Testing Procedure ##

To test the main loop, LEDs and delays can be used to indicate certain states in the device like whether or not the device is receiving an attack or sending one. The LEDs can also blink on and off to show how many times an attack or heal is used.  Switches can then simulate receiving attack packets and be used for the two user inputs. These simulations can be done within dummy functions so that it can catch some possible early mistakes make sure the correct signals are going to the right place.

## Data Sources ##

|Type of Datasource|URL|Used in Prototype?|
|:-----------------|:--|:-----------------|
|Website|http://arduino.cc/en/Products.Compare#.UwYFo_lMnU8|No|
|Datasheet|http://arduino.cc/en/Main/ArduinoBoardPro#.UwYGPvlMnU8|Yes|
|Website|http://www.sprut.de/electronic/pic/18f.htm#schuessel|No|
|Datasheet|http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en550200|Yes|

## Example Code ##

![http://i.imgur.com/MmfS29M.jpg](http://i.imgur.com/MmfS29M.jpg)