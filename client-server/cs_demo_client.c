/*
CLIENT/SERVER DEMO EXAMPLE: Simple OPC UA Client accessing fake sensor data.

The OPC UA Client sets up a connection to the OPC UA Server by a TCP connection.
The server "counts" with a sensor and updates the numberOfparts attribute 
of its "Piece counter" node. The client accesses this data and prints it insinde a loop.
*/

// Library amalgamated to a single file .h/.c file for simplicity
#include "../open62541.h"
#include <stdlib.h>

//NodeID of sensor-node
#define COUNTER_NODE_ID 20305
//polling interval for the client
#define POLLING_RATE 600000

int main(int argc, const char *argv[])
{

  if (argc < 2)
  {
    fprintf(stderr, "ERROR: No ip provided. Usage: ./client <end-point-ip>\n");
    exit(EXIT_FAILURE);
  }

  char end_point[256];
  strcat(end_point, "opc.tcp://");
  strcat(end_point, argv[1]);
  strcat(end_point, ":4840");

  /* First, we set up the connection */

  // Create a new client
  UA_Client *client = UA_Client_new();
  // Set client config to default
  UA_ClientConfig_setDefault(UA_Client_getConfig(client));
  // Statuscode for client connection to spcified endpoint ("opc.tcp://<Raspberry pie ip-adress>:4840)
  UA_StatusCode retval = UA_Client_connect(client, end_point); // ip address 127.0.0.1 = This computer" (opc.tcp://127.0.0.1:4840")

  if (retval != UA_STATUSCODE_GOOD)
  {
    UA_Client_delete(client);
    return (int)retval;
  }

  /* Next we will read the value attribute of the node */

  // Variants can hold scalar values and arrays of any type
  UA_Int32 myInteger = 0;
  UA_Variant value;
  UA_Variant_init(&value);
  UA_Variant_setScalar(&value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);

  // Browsing nodes in objects folder
  UA_BrowseRequest bReq;
  UA_BrowseRequest_init(&bReq);

  bReq.requestedMaxReferencesPerNode = 0;
  bReq.nodesToBrowse = UA_BrowseDescription_new();
  bReq.nodesToBrowseSize = 1;
  // Browse objects folder
  bReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
  // Return everything
  bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL;
  UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

  /* Iterate through list looking for a specific node, the node representing 
		 number of counted parts */
  for (size_t i = 0; i < bResp.resultsSize; ++i)
  {
    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j)
    {
      UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
      if (ref->nodeId.nodeId.identifier.numeric == COUNTER_NODE_ID)
      {
        while (retval == UA_STATUSCODE_GOOD)
        {
          /* READ FROM NODE OPERATION */
          // Reads the value of the node ID , puts it into "value"
          retval = UA_Client_readValueAttribute(client, ref->nodeId.nodeId, &value);
          if (retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
          {
            UA_Int32 raw_val = *(UA_Int32 *)value.data;
            printf("\nRecieved from server: [Counted pieces] %i ", raw_val);
          }
          else
          {
            /* For debugging */
            if (retval != UA_STATUSCODE_GOOD)
              printf("\nretval != UA_STATUSCODE_GOOD\n");
            if (!UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT32]))
            {
              printf("\nUA_Variant_hasScalarType != OK\n");
            }
          }
          usleep(POLLING_RATE);
        }
      }
    }
  }

  // clean up
  UA_BrowseRequest_clear(&bReq);
  UA_BrowseResponse_clear(&bResp);
  UA_Variant_clear(&value);
  UA_Client_delete(client); //Disconnects the client internally
  return EXIT_SUCCESS;
}