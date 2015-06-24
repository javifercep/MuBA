/***************************************************************/
/*****************   Multi Bus Analyzer   **********************/
/***************************************************************/

PHDLLAYER(Physical Layer & Data Link Layer)
----------------------------------------------------------------

This layer (also knows as Hardware Abstraction Layer) offers a 
set of functions that allows to the upper layers manage any 
hardware. 

This directory contains two of the seven OSI model layers. 
Whereas protocols like SPI need their data link layer defined, 
most of the automotive protocols manage this layer by hardware

The main hardware and software architecture of all boards follow
the next scheme:

 --------------------------------------------
|                  MBA Board                 |
| -----------   ----------------   --------- |
||           | |                | |         ||  
||    BUS    | |   Controller   | |   SPI   ||
||           | |                | |         ||
| -----------   ----------------   --------- |
 --------------------------------------------

The PHDLLayer directory are composed by:

 - BUSAPI directory    -> Contains the program files to manage the 
                          specific bus (CAN, LIN...)
 - SPIAPI directory    -> Contains the program files to manage the
                          SPI protocol. MCU firmwares usually offer
					      this kind of library. However, this API 
					      pretends unifies them in an only format.
 - BOARDAPI directory  -> Contains the program files to manage the
                          board elements like LEDs, buttons, GPIO...
						  It allows to configure hardware peculiarities.

					   
 