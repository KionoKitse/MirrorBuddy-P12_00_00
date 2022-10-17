### Description 
A project to automate power mirrors. The system will detect who is driving based on their seat position. From this, the system will automatically adjust the mirror position based on the detected user's known preferences. Additionally the system will be able to learn new settings if a user has decided to manually adjust the mirror position. 

### Hardware in use
* 1X ATmega328 (Arduino Pro Mini)
* 1X YX-X801 (low voltage cutoff)
* 2X ATtiny85 (micro processor)
* 3X L7805CV (voltage regulator)
* 4X OH137 (hall Sensor)
* 3X MAX485 (RS485 communication modules)
 
 
### What's next
* Get ATTiny85 to send a number via RS485 and display it on Arduino with OLED
* Get ATTiny85 to send the values in the correct format
* Design circuit boards  
 
### Progress log 
<details>
	<summary>Details of the project history</summary>
	
* 2021-10-05 Started the GitHub repository
* 2021-10-06 OLED test with Pro Mini
* 2021-10-07 Tested transmitting a value from ATtiny85 to ATmega328 over RS485 and displayed with OLED
* 2021-10-13 Building a RS485 HAT to ease testing
* 2021-10-18 Got the plotter working
* 2021-10-18 Monitor hall over serial working fine
* 2022-10-09 Hall sensor reading from spare housing
* 2022-10-10 Working on code to count number of rotations
* 2022-10-10 ATtiny with peakdetection and softserial
* 2022-10-11 Determined that peak detection uses too much memory "Global variables use 489 bytes (95%) of dynamic memory"
* 2022-10-12 Created a simpler peak detection algorithm 
* 2022-10-13 Added a debounce setting to MonitorHall it seems to be sending counts as expected 
* 2022-10-14 Added code to monitor 2 hall sensors 
* 2022-10-16 Built a relay board that can control the motors 
* 2022-10-17 Working on code to control relay board
</details>

### Notebook
<details>
	<summary>Next steps</summary>
* Need to run the MonitorHall program at higher speeds to set the correct debounce time 
* Need to check that I can read from both sensors at high speeds
* Test with multiple MAX485 modules on the network
* ProMini turn on motors then turn off after correct number of rotations achieved 
</details>

<details>
	<summary>Notes on the project</summary>
* Best to have ATTiny85 keep track of count in case ATmega328 misses a count
* Would be nice to see the actual values that got triggered for data monitoring
* RS485 only send a byte so that makes it challenging for sending an int
* Plotting with RS485 seems too slow
* Would be interesting to see if the MAX485 module could do TX/RX might make calibration easier
</details>

<details>
	<summary>Overview</summary>
	
- ProMini is the controller
	* It will detect which diver is in the seat
	* It will detect if the driver has adjusted the mirror
	* It will activate the controls to adjust the mirrors to the correct place
	* Data received
		+ The proMini will be receiving a value that is between 0-255 that contains the limit data and count
		+ It will know which ATtiney is sending because it will be controlling the power to the mirrors
		+ It will also know who is sending because it will have a sensor to detect which way the mirror button is pointing if the user is manually adjusting the mirror position
		+ In the case that the magnet stops in front of the hall sensor then the ATtiny will be sending sporadic readings
		+ There will need to be some sort of way to filter out this noise or adjust the mirrors a little bit to avoid this
- ATtiny85 1&2 are the sensors that monitor the position of the mirrors
	* They will send a signal when the limit switches have been activated
	* They will sens a signal when the hall sensors have detected the magnet passing
	* The RS485 sends a byte of data so that 0-255
	* Data sent
		+ 100 is limit switch for sensor 1 is hit
		+ 200 is limit switch for sensor 2 is hit
		+ 150 is 50 rotations on sensor 1 counted
		+ 255 is 55 rotations counted on sensor 2
	* The count on sensors is reset after 2 seconds of not seeing the hall sensor move
	* There should be some way to calibrate the threshold for the hall sensor reading
	* When it gets power (car turned on) the ProMini will move the mirrors to their outer limits
	* While this is happening the ATtiny85 will be recording the values detected
	* The ProMini will stop and wait a few seconds
	* When the ATtiny detects that it hasn't moved in a while it will use a filter on the collected data to determine the cutoff threshold
	* This data will be sent to the ProMini for logging and the threshold will be set
	* After this data has been sent the ProMini will know that it is okay to move the mirrors into possition
</details>

<details>
	<summary>Collision avoidance</summary>
	
- Collisions are avoided because the ProMini will only be controlling one ATtiny85 at a time so only one node will be transmitting at a time
- It would be impossible for both nodes to be transmitting since the user can only move one mirror at a time
</details>

<details>
	<summary>General thoughts</summary>
	
- Having the ProMini being the controller will allow me to make fine adjustments without having to pull the mirrors off
- limit switches
	* It could be problematic to use the limit switches since they could easily get water damaged since they are exposed to the elements quite a lot. It would be beneficial not not have to rely on them.
	* If I was doing this again I would not have added them since I could easily drive the motors out until I'm sure I'm at the outside limit and then work backwards from there.
	* The inside limit puts stress on the plastic nuts but the outside limit does not
	* Perhaps it's better to not use the limits at all
</details>