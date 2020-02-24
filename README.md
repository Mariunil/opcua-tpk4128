The demo implements client-server communication using the open-source OPC UA library [open62541](https://github.com/open62541/open62541.git). <br /> <br />




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


