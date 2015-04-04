# Voltage Regulation Prototyping #
### Justin Freeman - The Rajamani Tsunami ###



## 5V Regulator ##

Our power source is poorly regulated. When a load is attached the voltage would drop to around 3V.  To overcome this, we will be using the LMR62014 adjustable switching boost regulator.  Via a feedback resistor this part will be set to regulate the source at a steady 5V.

### Block Diagram ###

![http://i.imgur.com/qN4CVRx.png](http://i.imgur.com/qN4CVRx.png)

### Schematic ###

![http://i.imgur.com/zfpITZm.png](http://i.imgur.com/zfpITZm.png)

![http://i.imgur.com/Seme9Zf.png](http://i.imgur.com/Seme9Zf.png)

### Regulator Layout ###

![http://i.imgur.com/8FugBkr.png](http://i.imgur.com/8FugBkr.png)

## 3.3V Regulator ##

For the 3.3V regulation an adjustable linear LDO regulator is used.  This regulator uses a feedback resistance to control the voltage output. For our purposes, the output will be set at 3.3V.  The regulator takes input from the power source (5V/1A) and outputs a regulated 3.3V.

### Block Diagram ###

![http://i.imgur.com/XyqUiGe.png](http://i.imgur.com/XyqUiGe.png)

### Schematic ###

![http://i.imgur.com/8ycy01q.png](http://i.imgur.com/8ycy01q.png)

### Regulator Layout ###

![http://i.imgur.com/dfXbfpZ.png](http://i.imgur.com/dfXbfpZ.png)