# CAN Bus Transceiver Research Document #
### Michael Vancamp = The Rajamani Tsunami ###



Our project requires us to use CAN Bus in order to communicate with the MAGE system – we must be able to send an “I’m Dead” signal as soon as the shirt overloads. This requires two separate blocks – a software block and a hardware block. The software block is a function on the MCU that is called when the main program realizes that the shirt has overloaded. When the function is called, the on-board CAN controller generates the serial signal corresponding to an “I’m dead” signal to the transceiver via the TXD pin. The hardware block involves all the circuitry required to transmit the signal, as well as the connection to the bus itself.

## I. Block Diagram ##

This diagram shows how we envision this approach occurring and how the software and hardware interact.

![http://i.imgur.com/nA1mXxt.jpg](http://i.imgur.com/nA1mXxt.jpg)

## II. Primary Approach ##

The primary electronic that this phase of the project requires us to research and purchase is the CAN transceiver. This is the IC that turns a serial signal into CAN high and CAN low and sends it over the CAN bus. Here is the chip that we found to be the most appropriate.

![http://i.imgur.com/gQa4OWJ.jpg](http://i.imgur.com/gQa4OWJ.jpg)
https://www.sparkfun.com/datasheets/DevTools/Arduino/MCP2551.pdf

## III. Secondary Approach ##

![http://i.imgur.com/hbtok4R.jpg](http://i.imgur.com/hbtok4R.jpg)
http://www.ti.com/lit/ds/slls933f/slls933f.pdf

This transceiver appeared to be the highest quality. It had more features than the others, and draws far less average power. However, these facts are overshadowed by the massive increase in price. We will keep this option as a possibility in case we run into power issues or we need the extra features. For now we don’t foresee either of those issues occurring, so we will stick with the cheaper option.

![http://i.imgur.com/mNdqpVi.jpg](http://i.imgur.com/mNdqpVi.jpg)
http://www.st.com/web/en/resource/technical/document/datasheet/CD00002241.pdf

This transceiver draws a bit more power than the MCP2551. However, other than that, there are few drawbacks – they are quite comparable. The decision came down mainly to the fact that there were multiple groups in the past that had used the MCP2551; therefore, we expect there to be more useful documentation on the MCP2551 as opposed to this chip, which we know relatively little about.

## IV. Data Sources ##

|Type of Datasource|URL|Using in Prototype?|
|:-----------------|:--|:------------------|
|Datasheet|https://www.sparkfun.com/datasheets/DevTools/Arduino/MCP2551.pdf|Yes|
|Datasheet|http://www.ti.com/lit/ds/slls933f/slls933f.pdf|No|
|Datasheet|http://www.st.com/web/en/resource/technical/document/datasheet/CD00002241.pdf|No|

## V. Schematic ##

This is the circuit that I will use to communicate with CAN Bus. The inductors are a common mode choke, but I was unable to find the right model for Multisim.

![http://i.imgur.com/vM1dAdH.jpg](http://i.imgur.com/vM1dAdH.jpg)