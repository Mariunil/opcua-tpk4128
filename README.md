These demos implements client-server and publisher-subscriber OPC UA communication using the OPC UA library [open62541](https://github.com/open62541/open62541.git).



## Installation guide

The client-server demos can be run without any installation by linking to the amalgated open62541.c/.h library files 
present in the repo.

Navigate to /home/--username--/ or other preferable location and clone this repo: 

`https://github.com/Mariunil/opcua-tpk4128.git`  

If you don't have git installed:  
`sudo apt-get install git`


<br />
The pub-sub demos require the open62541 to be installed.
<br />


**Installation of open62541 from source:** 

(Will take a while on a Raspberry Pie 2/3)

Install dependencies:  
`sudo apt-get install git build-essential gcc pkg-config cmake python python-six` 
`sudo apt-get install cmake-curses-gui`  		    
`sudo apt-get install liburcu-dev`   		       
`sudo apt-get install check`	 	                
`sudo apt-get install python-sphinx graphviz` 
`sudo apt-get install python-sphinx-rtd-theme` 	



Navigate to /home/ or other preferable location, clone the repo:  
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
`make`  
`sudo make install`  
   
For some reason, "ua_pubsub_networkmessage.h" will be missing in the static library.
Manually move it from open62541/src/pubsub to the static library (assuming you have cloned open26541 to /home/--username--).  

`sudo cp /home/$USER/open62541/src/pubsub/ua_pubsub_networkmessage.h /usr/local/include/open62541/plugin`

<br />

## Use

**client-server**

Compile by linking to the open62541.c file:  
`gcc -std=c99 -pthread ../open62541.c cs_demo_client.c -o client`  
`gcc -std=c99 -pthread ../open62541.c cs_demo_server.c -o server`  

<br />

**pub-sub**  

`gcc -std=c99 -pthread ../open62541.c pubsub_demo_pub.c -o pub`  
`gcc -std=c99 -pthread -open62541 pubsub_demo_sub.c -o sub`  

Pub sub demos have not been verified to still function properly. 