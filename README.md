### Description 
A project to automate power mirrors. The system will detect who is driving based on their seat position. From this, the system will automatically adjust the mirror position based on the detected user's known preferences. Additionally the system will be able to learn new settings if a user has decided to manually adjust the mirror position. 

### Hardware in use
 * 1X ATmega328 (Arduino Pro Mini)
 * 1X YX-X801 (low voltage cutoff)
 * 2X ATtiny85 (micro processor)
 * 3X L7805CV (voltage regulator)
 * 4X OH137 (hall Sensor)
 
 
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
</details>

### Notebook
<details>
	<summary>Notes on the project</summary>
 * Best to have ATTiny85 keep track of count in case ATmega328 misses a count
 * Would be nice to see the actual values that got triggered for data monitoring
 * RS485 only send a byte so that makes it challenging for sending an int
 * Plotting with RS485 seems too slow
 </details>