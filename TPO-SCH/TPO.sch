EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X03 J?
U 1 1 5A22970C
P 3850 1850
F 0 "J?" H 3850 2050 50  0000 C CNN
F 1 "Salida Digital 0" V 3950 1850 50  0000 C CNN
F 2 "" H 3850 1850 50  0001 C CNN
F 3 "" H 3850 1850 50  0001 C CNN
	1    3850 1850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 J?
U 1 1 5A2297BB
P 3100 1850
F 0 "J?" H 3100 2050 50  0000 C CNN
F 1 "Salida Digital 1" V 3200 1850 50  0000 C CNN
F 2 "" H 3100 1850 50  0001 C CNN
F 3 "" H 3100 1850 50  0001 C CNN
	1    3100 1850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X06 J?
U 1 1 5A229828
P 6300 3050
F 0 "J?" H 6300 3400 50  0000 C CNN
F 1 "TP5" V 6400 3050 50  0000 C CNN
F 2 "" H 6300 3050 50  0001 C CNN
F 3 "" H 6300 3050 50  0001 C CNN
	1    6300 3050
	1    0    0    -1  
$EndComp
$Sheet
S 5500 1550 650  600 
U 5A229B03
F0 "Fuente-Externa" 60
F1 "..sch" 60
F2 "5v" I B 5800 2150 60 
F3 "GND" I B 5950 2150 60 
$EndSheet
Wire Wire Line
	3750 2050 3750 2400
Wire Wire Line
	3750 2200 3200 2200
Wire Wire Line
	3200 2200 3200 2050
Wire Wire Line
	3000 2050 3000 2300
Wire Wire Line
	3000 2300 5800 2300
Wire Wire Line
	3950 2300 3950 2050
Text GLabel 5750 3300 0    60   Input ~ 0
Vcc-Kit
Wire Wire Line
	6100 3300 5750 3300
Wire Wire Line
	3850 2050 3850 2850
Wire Wire Line
	3100 2050 3100 2850
Text GLabel 3100 2850 3    60   Input ~ 0
Motor_A1
Text GLabel 3850 2850 3    60   Input ~ 0
Motor_A2
Text GLabel 5750 3150 0    60   Input ~ 0
Servo_1
Text GLabel 5750 3000 0    60   Input ~ 0
Servo_2
Text GLabel 5750 2850 0    60   Input ~ 0
Servo_3
Wire Wire Line
	5750 3150 5950 3150
Wire Wire Line
	5950 3150 5950 3200
Wire Wire Line
	5950 3200 6100 3200
Wire Wire Line
	5750 3000 6000 3000
Wire Wire Line
	6000 3000 6000 3100
Wire Wire Line
	6000 3100 6100 3100
Wire Wire Line
	5750 2850 6050 2850
Wire Wire Line
	6050 2850 6050 3000
Wire Wire Line
	6050 3000 6100 3000
Wire Wire Line
	5950 2150 5950 2800
Wire Wire Line
	5950 2800 6100 2800
Text GLabel 5750 2700 0    60   Input ~ 0
GND_Kit
Wire Wire Line
	5750 2700 5950 2700
Connection ~ 5950 2700
Wire Wire Line
	5800 2300 5800 2150
Connection ~ 3950 2300
Wire Wire Line
	3750 2400 5950 2400
Connection ~ 3750 2200
Connection ~ 5950 2400
Text GLabel 4350 2850 3    60   Input ~ 0
5v_Servos
Text GLabel 4600 2850 3    60   Input ~ 0
GND_Servos
Wire Wire Line
	4350 2850 4350 2300
Connection ~ 4350 2300
Wire Wire Line
	4600 2850 4600 2400
Connection ~ 4600 2400
$EndSCHEMATC
