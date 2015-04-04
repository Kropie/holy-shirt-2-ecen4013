# User Input Prototyping #
### Kyle Lawler - The Rajamani Tsunami ###



## I. Block Diagram ##

![http://i.imgur.com/EVIYInd.jpg](http://i.imgur.com/EVIYInd.jpg)

_**Figure 1: Level 1 Block Diagram**_

## II. Inputs ##
|**Input Name**|**Description of Signal**|**Expected Range**|
|:-------------|:------------------------|:-----------------|
|Attack Button|Switch to determine if attack button was pressed|0V-5V|
|Heal Button|Switch to determine if heal button was pressed|0V-5V|

|**Function Name**|**Description**|**Input Parameters**|
|:----------------|:--------------|:-------------------|
|userinput()|Changes the attack or heal variable based on which button is pressed|null|null|

## III. Outputs ##

|**Function Name**|**Description of expected outputs to function**|**Input Parameters**|**Return Value**|
|:----------------|:----------------------------------------------|:-------------------|:---------------|
|userinput()|Attack or healing variable set to high when the corresponding button is pressed|null|null|

## IV. Signals at Test Points ##
|**T.P. Name**|**Description of Signal and Measurement Conditions**|**Range of Values**|
|:------------|:---------------------------------------------------|:------------------|
|Attack|Pin C0 will change state based on hit count when the attack button is pressed|On or Off|
|Heal|Pin C3 will change state based on hit count when the heal button is pressed|On or Off|

|**Attack Switch**|**Heal Switch**|**Attack LED**|**Heal LED**|
|:----------------|:--------------|:-------------|:-----------|
|0 |0 |0 |0 |
|0 |1 |0 |Change State+|
|1 |0 |Change State+|0 |
|1 |1 |Change State+|0 |

  * + indicates changes based on hit count.
  * Attack is above heal in the code so attack will take priority over healing if both buttons are pressed at the same time.