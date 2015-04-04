# Power Source Research Document #
### Justin Freeman - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/uCEpywj.jpg](http://i.imgur.com/uCEpywj.jpg)

## II. Power Requirements ##

|Member|Component|Power Draw (mA)|Volts|Notes|
|:-----|:--------|:--------------|:----|:----|
|Ty P.|IRRx|10mA|5V|  |
|Kyle G.|IRTx|200mA|5V|  |
|Michael V.|CAN Bus|25mA|5V|  |
|Michael V.|Haptic|60mA|3V|This is for each motor. Current draw will be only during vibration|
|Kate H.|Visuals|200mA|5V|  |
|Kyle L.|Microcontroller|100mA|5V|  |

## III. Primary Approach ##

![http://i.imgur.com/4xkSI57.jpg](http://i.imgur.com/4xkSI57.jpg)
http://aluratek.com/media/uploads/APBL01Fxx_DataSheet.pdf

|Cost|$15.99 + $1.54(Molex) = $17.53|
|:---|:-----------------------------|
|Output|5V/1A|
|Capacity|2600mAh|

## IV. Secondary Approach ##

![http://i.imgur.com/Oufj9qe.jpg](http://i.imgur.com/Oufj9qe.jpg)
![http://i.imgur.com/LDj04Pm.jpg](http://i.imgur.com/LDj04Pm.jpg)
http://dx.com/en/p/hotsion-5v-2000mah-18650-li-ion-battery-power-bank-for-iphone-4-4s-5-samsung-more-blue-242610

This product fits all the requirements of the device. The 2000mAh would satisfy the given requirement that the device must be able to function for two hours on one charge.  The 5V/500mA outputs satisfy our voltage and current requirements.  The only down-side to this device is that it is not a proven brand, and for the price, may be very cheaply made.  It seems to fit all of the requirements, but if it is a cheaply made device it may not meet the outputs that it has listed on its specifications.  Aluratek is a proven and trusted company, and past project groups have found success with Aluratek devices.  That is why the Aluratek APBL01Fxx is my choice for the prototype.

|Cost|$10.22 + $1.54(Molex) = $11.76|
|:---|:-----------------------------|
|Output|5V/500mA|
|Capacity|2000mAh|

## V. Alternative Approach ##

![http://i.imgur.com/iDrA3Yw.jpg](http://i.imgur.com/iDrA3Yw.jpg)
http://www.amazon.com/Powerex-2700mAh-Rechargeable-Batteries-holder-/dp/B001JR0RR4/ref=sr_1_1?ie=UTF8&qid=1393190706&sr=8-1&keywords=Powerex+AA+2700mAh+Rechargeable+NiMH+Batteries+%282700+mAh%29

![http://i.imgur.com/GC0Woog.jpg](http://i.imgur.com/GC0Woog.jpg)
http://www.amazon.com/Tenergy-TN145-8-Bay-Battery-Charger/dp/B006JILARE/ref=sr_1_4?ie=UTF8&qid=1393190776&sr=8-4&keywords=AA+battery+charger

![http://i.imgur.com/8WZm5cp.jpg](http://i.imgur.com/8WZm5cp.jpg)
http://www.radioshack.com/product/index.jsp?productId=2062253

This is an alternative approach. It is not really one we are considering at this point, but if the USB rechargeable source does not work out 4 of these connected in series will provide the required voltage and should be able to reach the time requirement for power.  The only complaint is that the batteries and battery holder are heavy and will take up a lot of space.  We will also have to buy the charger for them.  So, they seem more affordable, but after all the extra purchases to make them compatible they end up costing more than the other two approaches.

|Cost|$13.90 + $18.49 + $2.49 = $34.88|
|:---|:-------------------------------|
|Output|4.8V|
|Capacity|2700mAh|

## VI. Data Sources ##

|Type of Datasource|URL|Used in Prototype?|
|:-----------------|:--|:-----------------|
|Manufacturer Info|http://aluratek.com/media/uploads/APBL01Fxx_DataSheet.pdf|Yes|
|Online Store|http://www.amazon.com/Aluratek-Portable-External-Built-In-Flashlight/dp/B00FFZCPGW/ref=sr_1_4?ie=UTF8&qid=1392686046&sr=8-4&keywords=aluratek+power+source|Yes|
|Website|http://dx.com/en/p/hotsion-5v-2000mah-18650-li-ion-battery-power-bank-for-iphone-4-4s-5-samsung-more-blue-242610|No|
|Online Store|http://www.amazon.com/Powerex-2700mAh-Rechargeable-Batteries-holder-/dp/B001JR0RR4/ref=sr_1_1?ie=UTF8&qid=1393190706&sr=8-1&keywords=Powerex+AA+2700mAh+Rechargeable+NiMH+Batteries+%282700+mAh%29|No|
|Website|http://www.photonlight.com/batteries-and-battery-chargers/powerex-rechargeable-aa-nimh-2700mah-4pk/|No|
|Online Store|http://www.amazon.com/Tenergy-TN145-8-Bay-Battery-Charger/dp/B006JILARE/ref=sr_1_4?ie=UTF8&qid=1393190776&sr=8-4&keywords=AA+battery+charger|No|
|Online Store|http://www.radioshack.com/product/index.jsp?productId=2062253|No|