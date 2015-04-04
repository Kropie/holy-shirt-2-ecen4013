# Voltage Regulation Research Document #
### Justin Freeman - The Rajamani Tsunami ###



## I. Block Diagrams ##

![http://i.imgur.com/954e3Rv.jpg](http://i.imgur.com/954e3Rv.jpg)

![http://i.imgur.com/y9A6sxW.jpg](http://i.imgur.com/y9A6sxW.jpg)

## II. Primary Approach ##

![http://i.imgur.com/87T4J8w.jpg](http://i.imgur.com/87T4J8w.jpg)

http://www.6502.org/mini-projects/dpod/dpodfiles/LP2954A.pdf

|Cost|$2.62|
|:---|:----|
|Output|1.23V-29V Adjustable (250mA)|

## III. Alternative Approach ##

![http://i.imgur.com/37P0QoP.png](http://i.imgur.com/37P0QoP.png)
http://www.ti.com/lit/ds/symlink/tps73001.pdf

This approach seems great.  It provides easily adjustable voltage that is within the range needed. It is extremely affordable, and it is from a proven company.   The only problem is that the max output current (200mA) is exactly what is required for one of our components. This is not an ideal world, and I would like to have a little bit of wiggle room with the current.  That is the main reason that this is an alternative.  It might be simpler than the primary chip, and if this were an ideal world this would be the primary.

|Cost|$0.70|
|:---|:----|
|Output|1.22-5.5V Adjustable (200mA)|

## IV. Alternative Approach 2 ##

![http://i.imgur.com/D67CjDf.png](http://i.imgur.com/D67CjDf.png)
http://www.analog.com/static/imported-files/data_sheets/ADP3333.pdf

If, for some reason, we have trouble with the adjustable voltage regulators we can use these set regulators.  There is a 3.3V and a 5V model. These are nice because they are extremely easy to use, and the anyCAP capacitor system will save board space. At 300 mA they should easily be able to provide the necessary power to our system. The only reason that they are an alternative is because the set voltage outputs limit what you can do with them.

|Cost|$2.31|
|:---|:----|
|Output|5V or 3.3V Fixed (300mA)|

## V. Data Sources ##

|Type of Datasource|URL|Used in Prototype?|
|:-----------------|:--|:-----------------|
|Datasheet|http://www.6502.org/mini-projects/dpod/dpodfiles/LP2954A.pdf|Yes|
|Datasheet|http://www.ti.com/lit/ds/symlink/tps73001.pdf|No|
|Datasheet|http://www.analog.com/static/imported-files/data_sheets/ADP3333.pdf|No|