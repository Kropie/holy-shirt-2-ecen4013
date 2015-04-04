# Visual Effects Research Document #
### Kate Hehmann - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/hA5Qswp.jpg](http://i.imgur.com/hA5Qswp.jpg)

## II. Primary Approach ##

![http://i.imgur.com/DCbgyAs.jpg](http://i.imgur.com/DCbgyAs.jpg)

10 Segment LED Bar Graph
|Cost|$1.90|
|:---|:----|
|Supply Voltage|3.6V|
|Supply Current|30mA|

![http://i.imgur.com/HeQ4YWv.jpg](http://i.imgur.com/HeQ4YWv.jpg)
http://datasheets.maximintegrated.com/en/ds/MAX6966-MAX6967.pdf

MAX6966AEE+ (10-Port Constant Current LED Driver)
|Cost|$4.98|
|:---|:----|
|Connection|SPI|
|Supply Voltage|2.25-3.6V|

![http://i.imgur.com/WoI3sZF.png](http://i.imgur.com/WoI3sZF.png)
http://www.adafruit.com/datasheets/WS2812.pdf

NeoPixel Ring - 24 WS2812 5050 RGB LED
|Cost|$19.95|
|:---|:-----|
|Connection|SPI|
|Supply Voltage|5V|
|Supply Current|480mA|

![http://i.imgur.com/pKJ1pnA.png](http://i.imgur.com/pKJ1pnA.png)
http://www.adafruit.com/datasheets/WS2812.pdf

NeoPixel Ring – 16 WS2812 5050 RGB LED
|Cost|$9.95|
|:---|:----|
|Connection|SPI|
|Supply Voltage|5V|
|Supply Current|320mA|

For the LED array, we decided to go with a simple LED array. Looking at the various models, we decided to go with this one because of the cheap price, low power requirements, and the simplicity. There are several examples of the LED array with code online to use as a reference. If the size of our bar needs to be expanded, we’ll be able to accomplish this easily. There were plenty of LED drivers to go through—mostly analog—but this one seemed to be the best choice. Using SPI, the driver will allow the MCU and the LED array to communicate through PWM. We were unsure if we could use a 8-port driver to control a 10 segment LED array, so to be on the safe side, we used a 10-port driver. For the other LED visuals, we decided to go with a NeoPixel Ring. This ring has WS2812 RGB LEDs which are special because they have are addressable thanks to the driver chip being located inside the LED. Because of this, a separate LED driver is not needed for purchase. The fact that it is comprised of RGB LEDs, more flexibility for our display is possible (i.e. Red: Harmed, Green: Attack, Blue: Healing). The price originally worried us, but once we calculated how much money we would need to do the LEDs separately (see table below), the slight price increase was worth it. There are also libraries and example code included online. To help with the cost, a smaller version (16 RGB LED NeoPixel Ring) was found for half the price. For this case the size of the ring shrunk from 2.6” to 1.75”. We figured the larger ring can be on the chest and then the smaller rings can be used for the shoulders and the back, thus helping with cost and power consumption while still adding to visual appeal.

RGB LED array price:
|24 x 5 mm RGB LEDs (@ $0.27)|$6.48|
|:---------------------------|:----|
|LED Driver| ~$5.00|
|Circular Perfboard|$3-$5|
|**Total**|**$14.48-$16.48**|

## III. Alternative Approach ##

![http://i.imgur.com/p4A0ben.png](http://i.imgur.com/p4A0ben.png)
https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Hardware%20Specifications

COM-11442 7-Segment Display
|Cost|$12.95|
|:---|:-----|
|Connection|UART, SPI, or I2C|
|Supply Voltage|3.3-5V|
|Supply Current|7.9mA for 3.3V 14.1mA for 5.0V|

![http://i.imgur.com/1i292De.png](http://i.imgur.com/1i292De.png)
http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/LED/LED-CCL-A.pdf

COM-10595 Circular LED Bargraph
|Cost|$9.95|
|:---|:----|
|Supply Voltage|2.4V|
|Supply Current|25mA|

This alternative approach allows us to show an actual number for damage rather than a level. It also allows us several connections to choose from so we can adapt more easily as changes are made during the design process. Arduino coding examples is also included for the 7-segment display. The second option for our other LED visuals, we continued with the circular LED display. This visual, unfortunately, does not have RGB LEDs, so our creative flexibility will be limited (only light up red to show where the user was attacked). For the same price, 16 red LEDs, and no built in driver, this circular bargraph will stay as an alternative and will only be brought forward if there are power issues with the first option.

## IV. Alternative Approach 2 ##

![http://i.imgur.com/Hfca1fE.png](http://i.imgur.com/Hfca1fE.png)
https://www.sparkfun.com/datasheets/Components/YSM-2388CRGBC.pdf

COM-00760 LED Matrix
|Cost|$59.95|
|:---|:-----|
|Connection|SPI|
|Supply Voltage|5V|
|Supply Current|120mA|

![http://i.imgur.com/hgmuH8d.png](http://i.imgur.com/hgmuH8d.png)
http://www.taydaelectronics.com/datasheets/A-1094.pdf

RGB LED 5mm Common Cathode
|Cost|$0.27|
|:---|:----|
|Supply Voltage|2-3V|
|Supply Current|20mA|

This LED Matrix could be a possible candidate for the visual effects for the project. Unfortunately, the price and size (2.38” x 2.38”) wouldn’t necessarily be optimal. The website includes firmware and sample code for the LED matrix, which is a plus. We are unsure as to how we are recording and displaying the power levels. We need to find out if an actual value needs to be displayed or if we can represent the power level just by a strip of LEDs. Once this is worked out, we can decide if we want to go with this array or use a 7-segment display. The third visual approach would be to use just regular RGB LEDs in an array. As stated from the first approach, this option did seem like the cheapest, but once you added in the cost of the driver and perfboard and the various LEDs, it was a lot better to go with the first option that had everyone built into one. If we bought the WS2812 version of the RGB LED, for double the cost of the regular RGB LED, our cost would still be less than the original approach but then again we would have to deal with soldering and packaging. It wouldn’t be too much of an issue, but for the cost, it would be easier to have everything already packaged together.

## V. Data Sources ##

|Type of datasource|URL|Using in prototype?|
|:-----------------|:--|:------------------|
|Datasheet|https://www.sparkfun.com/datasheets/Components/LED/YSLB-102510B5-10.pdf|Yes|
|Datasheet|http://datasheets.maximintegrated.com/en/ds/MAX6966-MAX6967.pdf|Yes|
|Datasheet|http://www.adafruit.com/datasheets/WS2812.pdf|Yes|
|User Guide|http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/LED/adafruit-neopixel-uberguide.pdf|Yes|
|Datasheet|https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Hardware%20Specifications|No|
|Datasheet|http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/LED/LED-CCL-A.pdf|No|
|Datasheet|https://www.sparkfun.com/datasheets/Components/YSM-2388CRGBC.pdf|No|
|Datasheet|https://www.sparkfun.com/datasheets/Components/rgbmatrixbackpack_userguide.pdf|No|
|Datasheet|http://www.taydaelectronics.com/datasheets/A-1094.pdf|No|