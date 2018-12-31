# personalc
My personal reference to C programming  

## To microcontrollers programming see:  
* https://github.com/augustomatheuss/mcu-examples  

## Usage examples in file examples.c  
* Compile - Command Line 
```
gcc -lm examples.c personal.c -o examples
```  
* Compile - Makefile (**Makefile Example!**)
```
make && make clean
```
* Run
```
./examples
```

## Check memory leaks in your program  
```
valgrind --leak-check=full --track-origins=yes name-of-your-program
```

![](https://github.com/augustomatheuss/personalc/blob/master/img/screenshot-examples-1.png)  
![](https://github.com/augustomatheuss/personalc/blob/master/img/screenshot-examples-2.png)  

## References:  
* http://www.cplusplus.com/reference/clibrary/  

