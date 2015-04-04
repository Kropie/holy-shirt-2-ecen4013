# IR Receiver Research Documentation #
### Ty Prather - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/gUolc10.jpg](http://i.imgur.com/gUolc10.jpg)

One of the main components of the Holy Shirt is the ability to receive IR (MIRP) packets from other devices. The IR packets will need to be received and decoded for processing by the microcontroller to determine what type of packet was received and whether the attack strength level of the shirt should be increased.


## II. Primary Approach ##

![http://i.imgur.com/iX8zPHa.jpg](http://i.imgur.com/iX8zPHa.jpg)
http://www.vishay.com/docs/82457/tsop61.pdf

## III. Alternative Approaches ##

![http://i.imgur.com/6zrVEjN.jpg](http://i.imgur.com/6zrVEjN.jpg)
http://www.vishay.com/docs/82490/tsop321.pdf

This alternative was rejected primarily since it is a through-hole component. My main concern with this is the durability of mounting a through-hole component and the ability to keep the receiver pointed in the correct direction at all times. For the front and back receivers, a surface mount component is already facing in the correct direction whereas this component would have to be bent at a 90 degree angle; however, on the shoulder receivers, a through-hole component could be easier to mount making this component a viable alternative for the shoulder mounts. This alternative is also slightly cheaper, requires a less minimum irradiance, and has smaller directivity. However, with the durability and mounting concerns, the TSOP6256 is still my preferred choice.

![http://i.imgur.com/JdfPDdQ.jpg](http://i.imgur.com/JdfPDdQ.jpg)
http://www.vishay.com/docs/82496/tsop752w.pdf

This alternative was eliminated for multiple reasons. First, the directivity of the primary selection is significantly less than this solution, which is beneficial to our application since we do not want a large amount of overlap in the coverage of the four receivers. Second, the cost of the primary selection was approximately 66% of this alternative. Finally, the range of this alternative is less than the primary selection. (This could be due to the difference in current in the test emitter, but is likely also related to the fact that the alternative has no lens). The primary solution also has better interference rejection, but likely not different enough to make a difference in our application.

## IV. Table of Comparison ##

|Component|Directivity|Supply Cur.|Min. Irradiance|Trans. Distance|Cost|Mounting|
|:--------|:----------|:----------|:--------------|:--------------|:---|:-------|
|TSOP6256|50deg|.7mA|.25mW/m^2|40m|$1.17|SMT|
|TSOP75356W|75deg|.35mA|.15mW/m^2|30m|$1.42|SMT|
|TSOP32156|40deg|.35mA|.08mW/m^2|45m|$1.03|SIP|

## V. Software ##

![http://i.imgur.com/aKSii0w.png](http://i.imgur.com/aKSii0w.png)

There are two main ways to write the software to receive IR information: interrupt-based, and polling-based. In interrupt-based reception, the microcontroller is constantly reading data from the receiver and waiting for a trigger on the falling edge (Since the receiver is outputting high when no IR signal is present, see attached figure below). Polling-based reception would poll the receiver every half of a cyle (appx. 8μs). In our application, interrupt-based reception will be a more reliable solution, allowing us to process every packet of data instead of potentially missing parts of packets due to polling intervals. The only downside to interrupt-based polling is that it will require a good amount of error management code in order to be sure that we are not processing IR noise instead of a valid IR signal.

The main IR processing software will be composed of four steps of storing and validating envelopes. The software will store the first envelope of 150 cycles and check to ensure that it is a valid start envelope. If it is valid, the software will continue and store the next two envelopes, compare the two envelopes with each other, and compare one envelope with the known attack signal. If all envelopes match, the software will continue to receive the last envelope and will return an increment command to the main program if a valid stop envelope is received.

## IR Broadcast Data vs. IR Receiver Output ##

![http://i.imgur.com/NftM39Y.jpg](http://i.imgur.com/NftM39Y.jpg)

Like stated above, this figure depicts that when our receiver input is high, the output signal will be low, and when the receiver input is low, the output will be high. This is why the IR receiver software must trigger an interrupt on the falling edge of the signal.

## VI. Data Sources ##

|Type of Datasource|URL|Using in Prototype?|
|:-----------------|:--|:------------------|
|Datasheet|http://www.vishay.com/docs/82457/tsop61.pdf|Yes|
|Datasheet|http://www.vishay.com/docs/82496/tsop752w.pdf|No|
|Datasheet|http://www.vishay.com/docs/82490/tsop321.pdf|No|
|Manufacturer Info|http://www.vishay.com/docs/80071/dataform.pdf|No|
|General Info|http://learn.parallax.com/propeller-c-simple-devices/ir-receiver-and-remote|No|
|Software Info|http://www.winpicprog.co.uk/pic_tutorial5.htm|Yes|
|Hardware Info|http://ww1.microchip.com/downloads/en/AppNotes/90003096A.pdf|No|

## VII. Simulation ##

![http://i.imgur.com/6e1VhOY.jpg](http://i.imgur.com/6e1VhOY.jpg)

For prototyping, four receivers will be wired to a seven-pin header on a breakout board. One receiver will be facing in each cardinal direction allowing us to test the location functionality of our code.

Since we are unable to simulate this circuit, I predict the output of all four receivers to be equal to Vs when no IR signal is present and 0 whenever a 56kHz IR signal is received. Using this, we should be able to use an interrupt to detect the falling edge of the IR receiver data on all four GPIO pins, and process the data accordingly for each receiver.