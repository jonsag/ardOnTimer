# ardOnTimer
An on timer with relay, mainly for use in an UV exposure box.  

Time is set with buttons and visualized on an LCD display.  

When setting new time it's saved in eeprom and reloaded at startup.  

Timer range is from 10 seconds to 9 hours, 59 minutes and 59 seconds in 10 seconds steps.  
This can be changed in configuration file.  

Parts list
==========
1 x Arduino Uno, kjell.com art#88860  
1 x LCD display 2x16 characters, kjell.com art# 90215  
1 x Relay module KY-019, kjell.com art# 87878  
1 x Buzzer, kjell.com art# 87887  
4 x Switch, kjell.com art# 36011  
1 x 10kohm potentiometer  
4 x 10kohm resistor  
1 x 220ohm resistor  
1x 100ohm resistor  

Screens
==========
The timer has three screens.  
Second row on screens shows which buttons are active.  

Standby screen
----------
Waiting for start or set.  

 * Start/Stop/Store button to start timer and enter run screen.  
 * Set button to enter set screen.  

Run screen
----------
Shows spinning bar and time left on first row, and progressbar on the second.  

 * Start/Stop/Store button to stop timer and go back to standby screen.  

Set screen
----------
Setting timer.  

* Start/Stop/Store button to store set time.  
* Set button to exit back to standby screen. If set time was not, previous time will be used.  
* Up or Down button to increase/decrease time. Each press adds/subtracts 10 seconds from time. Long press adds/subtracts one minute from time. Holding buttons keeps stepping minutes.  

