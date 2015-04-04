# User Input Research Document #
### Kyle Lawler - The Rajamani Tsunami ###



The holy shirt must be able to send both attack and healing packets at the users command.  To do this, a switch of some kind must be used to signal the MCU that it needs to send IR packets. The MCU has four interrupt on change pins but they will most likely be used by the IR receiver so two external interrupt pins that interrupt on a selected edge will be used. Larger buttons will be used because placement of the user input will be around the chest area making it more difficult to find and press since the user will have to look to their own chest in order to see the buttons. Having the buttons here forces the user to bring their hand to their chest making a sort of prayer motion which can add to the visual appeal of using the holy shirt.  The use of Push buttons also force the user to hold the button down for a short while making the action look more like a prayer than a tap on the chest.

## I. Primary Option ##
**Digi-Key Part Number EG4790-ND**

This switch was chosen because it is cheap and is larger than most push button switches found.  I believe a larger button will make the shirt easier to use because the user will be able to find and press the button faster than a smaller button.

![http://i.imgur.com/r2KOFkb.jpg](http://i.imgur.com/r2KOFkb.jpg)

http://www.digikey.com/product-search/en?x=0&y=0&lang=en&site=us&KeyWords=EG4790-ND

## II. Alternative Option 1 ##
**NTE54-394 - Pushbutton OFF/(ON) Momentary Switch SPST 3A**

This was chosen as a backup because it can be purchased at radio shack and can be pickup up as needed. The button is a little larger than most push buttons at radio shack making it easier on the user to find the button.

![http://i.imgur.com/bzWDdfU.jpg](http://i.imgur.com/bzWDdfU.jpg)

http://www.radioshack.com/product/index.jsp?productId=12706299&retainProdsInSession=1

Option one was chosen over option two mainly over cost.  But the size and shape of the switch is also not as good as option one.  Option two is too long and this increased length could cause wear on the location the button is attached when pressing the button or bumping against it.

## III. Schematic ##

This is how the switch will be connected.  This makes the signal on the GPIO pin high while the switch is open and low when the switch is closed.  Care will need to be used when sensing the change from high to low or low to high on the MCU because the signal from the switch bounces high and low several times at the moment the switch changes state.  To fix this, the switches state can be rechecked a short time after the interupt has sensed a change.  This second check of the swiches state will tell the user what state the switch is in.

![http://i.imgur.com/yXpEOlf.jpg](http://i.imgur.com/yXpEOlf.jpg)

Testing can be done by making a program that changes the state of a light each time the switch is pressed.

## IV. Data Sources ##

|Type of Datasource|URL|Used in Prototype?|
|:-----------------|:--|:-----------------|
|Datasheet|http://www.digikey.com/product-detail/en/KS-00Q-03/EG4790-ND/2116269|Yes|
|Datasheet|http://www.radioshack.com/product/index.jsp?productId=12706299&retainProdsInSession=1|No|
|Website|http://en.wikipedia.org/wiki/Switch|No|