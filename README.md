These demos implements client-server and publisher-subscriber the open-source OPC UA communication using the OPC UA library [open62541](https://github.com/open62541/open62541.git). <br /> <br />




# Client-Server Demo

## Installation
The client-server demos can be run without any installation by linking to the amalgamated open62541.c/.h library files present in the repo.

Navigate to /home/--username--/ or other preferable location and clone this repo: 

`https://github.com/Mariunil/opcua-tpk4128.git`  

If you don't have git installed:  
`sudo apt-get install git`

## Use
Compile by linking to the open62541.c file (while inside opcua-tpk4128/client-server):  
`gcc -std=c99 -pthread ../open62541.c cs_demo_client.c -o client`  
`gcc -std=c99 -pthread ../open62541.c cs_demo_server.c -o server`  

The Client-Server demo showcase a simple use case where a device is counting passed pieces in, for instance, a assembly line and another device is interested in this information.

The OPC UA server monitors a fake counting sensor and live-updates the "counted-pieces" field in its information model. This information model is then accessed by the OPC UA client, which in real-time prints the value of that field, i.e. the number of passed pieces.  

The client are run by running the executable with the servers IP address (127.0.0.1 if running between two terminals):  
`./client 127.0.0.1`

The server can be run without any input parameters:  
`./server` <br /> <br /> <br />



# Pub-Sub Demo


## Installation guide

The pub-sub demos require the open62541 to be installed.   



<br />**Installation of open62541 from source:** 


Install dependencies:  
`sudo apt-get install git build-essential gcc pkg-config cmake python python-six` 
`sudo apt-get install cmake-curses-gui`  		    
`sudo apt-get install liburcu-dev`   		       
`sudo apt-get install check`	 	                
`sudo apt-get install python-sphinx graphviz` 
`sudo apt-get install python-sphinx-rtd-theme` 	



Navigate to /home/ or other preferable location, clone the open62541 repo:  
`git clone https://github.com/open62541/open62541.git`

Preparing for cmake:  
`cd open62541 && git submodule update --init --recursive`  
`mkdir build && cd build`  
`cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DUA_NAMESPACE_ZERO=FULL ..`  

Enter the cmake configuration GUI:  
`ccmake ..`  

Fnd and enable `UA_ENABLE_PUBSUB`, `UA_ENABLE_PUBSUB_DELTAFRAMES`, `UA_ENABLE_PUBSUB_ETH_UADP` and `UA_ENABLE_PUBSUB_INFORMATIONMODEL`.   
(You will need press t to toggle to advanced mode to abe able to find all)

When enabled, press c t configure, then q to leave

Compile open62451 with make (while inside /wherever/open62451/build):  
(Will take a while on a Raspberry Pie)  
`make`  
`sudo make install`  
   
For some reason, "ua_pubsub_networkmessage.h" will be missing in the static library.
Manually move it from open62541/src/pubsub to the static library (assuming you have cloned open26541 to /home/--username--).  

`sudo cp /home/$USER/open62541/src/pubsub/ua_pubsub_networkmessage.h /usr/local/include/open62541/plugin` <br /> <br /> <br />



## Use
Compile by linking to the open62541.c file (while inside opcua-tpk4128/pub-sub):  
`gcc -std=c99 -pthread ../open62541.c pubsub_demo_pub.c -o pub`  
`gcc -std=c99 -pthread ../open62541.c pubsub_demo_sub.c -o sub`  

(The pub-sub demos have not been verified to still be working.)