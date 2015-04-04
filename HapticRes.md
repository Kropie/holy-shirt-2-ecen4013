# Haptic Feedback Research Sheet #
### Michael Vancamp - The Rajamani Tsunami ###



One of the specifications for the Holy Shirt 2.0 is that it must have haptic feedback where the shirt is hit. To implement this, we decided to have vibration motors on the shirt in each of the four cardinal directions that vibrate when shot. The duration of the vibration will change based on how many MIRP packets it absorbs.

In order to complete this implementation, we plan on having two stages – software and hardware. In the software stage, a function is called with the two parameters: an integer 1-4 that indicates which location to send the feedback to and the number of MIRP packets that were absorbed. This stage is also responsible for outputting the .6V wave for the correct amount of time. The hardware phase is very simple – it only involves the vibration motor and an op amp that boosts the signal to 3V. Because the voltage wave is already conditioned to generate the proper amplitude of vibration for the correct length of time, there is no need to add any extra circuitry.

## I. Block Diagram ##

![http://i.imgur.com/d2m6lr2.jpg](http://i.imgur.com/d2m6lr2.jpg)

The following vibration motors are the models that we considered to be the most plausible as we looked through the possibilities.

## II. Primary Approach ##
![http://i.imgur.com/9LB81pl.jpg](http://i.imgur.com/9LB81pl.jpg)
http://www.pololu.com/product/1636

## III. Secondary Approach ##
![http://i.imgur.com/wFd1oy4.jpg](http://i.imgur.com/wFd1oy4.jpg)
http://www.adafruit.com/products/1201#Technical_Details

While cheaper, this vibration motor is certainly less efficient. It vibrates considerably slower, and draws far more power than the primary approach. The extra $1.50 is worth the increase in quality we will see if we choose not to use this motor.

![http://i.imgur.com/3T8mFQT.jpg](http://i.imgur.com/3T8mFQT.jpg)
http://www.vibration-motor.com/products/pancake-vibrator-motors/coin-motor-C1234B016F.html

The primary advantage of this option is the size – the diameter is 2 mm larger than most coin vibration motors. However, it spins significantly slower than the others – this will likely nullify the advantage of the size. It is the most expensive of the three, so unless we realize that diameter matters more than we thought it did, we will stick with the primary option.

## IV. Data Sources ##

|Type of Datasource|URL|Using in Prototype|
|:-----------------|:--|:-----------------|
|Datasheet|http://www.pololu.com/product/1636|Yes|
|Datasheet|http://www.adafruit.com/products/1201#Technical_Details|No|
|Datasheet|http://www.parallax.com/sites/default/files/downloads/28821-Flat-Coin-Vibration-Motor-Documentation.pdf|No|

## V. Simulation ##

The following schematic shows the implementation we wish to use for the hardware. It is very minimal because the software stage does everything we need with the wave except amplify it and run it to the motor.

![http://i.imgur.com/DhObGA1.jpg](http://i.imgur.com/DhObGA1.jpg)

If the vibration is too strong, the motor is capable of running at 2.4V. The RPM decreases to 12000. If this is necessary, we will add a 12 ohm resistor in parallel with the motor, as shown in the figure above. I experimented with a 10mm x 3.4mm vibration motor from an old cell phone that appeared similar to our primary approach. This motor had the highest vibration amplitude at about 3.5V, but it was functional as low as 0.3V – it had a well-defined spectrum of voltages it could run at, so the idea of limiting the supply voltage with a resistor is very applicable.