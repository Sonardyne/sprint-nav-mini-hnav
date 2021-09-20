# sprint-nav-mini-hnav
Simple example HNav Message decoder. It is written in C++ and uses CMake to control the building of the application. A 
sample message is constructed in main.cpp and this is then passed in to a decoder object which checks for a valid
HNav message, if one is found then it's details are extracted and printed to terminal<br/>

# Building
After cloning this repo, please ensure that you have CMake and a suitable toolchain installed run the following
commands from a terminal:
* cmake CMakeLists.txt
* make

Then run the resulting executable.

#Sample Output
Valid HNav message detected in data provided to decoder. Decoded as:<br/>
&emsp;*****   Time                    ***** <br/>
&emsp;&emsp;UTC Time: 1.63213e+009<br/>
&emsp;*****   2-D Position            ***** <br/>
&emsp;&emsp;Latitude (degrees): 51.3306<br/>
&emsp;&emsp;Longitude (degrees): -0.835691<br/>
&emsp;&emsp;Position Quality (CEP50): 1.99522<br/>
&emsp; ****   Depth                   ***** <br/>
&emsp;&emsp;Depth (Metres): -0.135<br/>
&emsp;*****   Altitude                ***** <br/>
&emsp;&emsp;Altitude Invalid<br/>
&emsp;*****   Orientation             ***** <br/>
&emsp;&emsp;Roll (degrees): -0.099<br/>
&emsp;&emsp;Pitch (degrees): -0.462<br/>
&emsp;&emsp;Heading (degrees): 72.9685<br/>
&emsp;&emsp;Heading Quality (degrees): 2.195<br/>
&emsp;*****   Velocities              ****** <br/>
&emsp;&emsp;Velocity, Vehicle Forward (m/s): -0.006<br/>
&emsp;&emsp;Velocity, Vehicle Starboard (m/s): -0.006<br/>
&emsp;&emsp;Velocity, Vehicle Down (m/s): -0.001<br/>
&emsp;&emsp;Velocity Quality (mm/s): 0.107<br/>
&emsp;*****   Angular Rates           ***** <br/>
&emsp;&emsp;Angular Rate, Vehicle Forward (deg/s): 0<br/>
&emsp;&emsp;Angular Rate, Vehicle Starboard (deg/s): 0<br/>
&emsp;&emsp;Angular Rate, Vehicle Down (deg/s): 0<br/>
&emsp;*****   Sound Velocity          ***** <br/>
&emsp;&emsp;Sound Velocity (m/s): 1522.38<br/>
&emsp;*****   Water Temperature       ***** <br/>
&emsp;&emsp;Temperature Invalid<br/>
&emsp;*****   Status                  *****<br/>
&emsp;&emsp;In Hybrid Mode<br/>