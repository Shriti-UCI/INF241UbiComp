INF241UbiComp
=============

Contains Arduino code for water flow meter

Components of the set up are as follows:
Circuit:
Used the intel Galileo Board. The circuit diagram used can be found here: http://forum.arduino.cc/index.php/topic,8548.0.html

Data Collection:
Dweet.io is used for collecting data published by water flow meter through Galileo. The specific request is below:
	client.print("GET /dweet/for/UciUbicompSensor1?data=");
	client.print(Calc);

Data Visualization:
Freeboard is used for gathering data from dweet.io and producing visualization.
