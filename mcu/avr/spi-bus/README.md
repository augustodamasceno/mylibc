# SPI Bus for Tests  
### MCUs ATmega48A-PA-88A-PA-168A-PA-328-P

## Slaves  

* MCU 0 : Slave with SS connected to port PD2 of master    
* MCU 1 : Slave with SS connected to port PD4 of master    
* MCU 2 : Slave with SS connected to port PD7 of master    
* MCU 3 : Slave with SS connected to port PB0 of master    

## Sequence of operation:  
* The master sends '0' to MCU 0   
* Get the response 'A' from MCU 0   
* The master sends '1' to MCU 1    
* Get the response 'B' from MCU 1  
* The master sends '2' to MCU 2    
* Get the response 'C' from MCU 2  
* The master sends '3' to MCU 3    
* Get the response 'D' from MCU 3    
* Wait 1 second  
* Repeat the sequence  

### Note that if the MCU do not get the correct char,  
### the response is the equivalent char and not the letter.  

