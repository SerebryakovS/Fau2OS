
## Mesh System API
All backend implementation is located in: /usr/libexec/rpcd/mesh
The package uhttpd-mod-ubus must be installed before using described API
Following api calls are used for getting information from single mesh router. So, as very first step it's required to obtain IP addresses for next supported hostnames:
```
AvailableHostnames = [ "mesh_master", "mesh_slave_1", "mesh_slave_2" ]
```
##### ubus call mesh GetMeshConnInfo
This call is used to retrieve information about internal wireless mesh links:
```
{
    "MeshConnections" : [
        {
            "MACAddress" : "...",
            "IPAddress" : "...",
            "Hostmame" : "...", # one of the AvailableHostnames
            "SignalPower" : "...",
            "LinkRates" : { #[MBit/s]
                "RxBitrate" : "...",
                "TxBitrate" : "...",
                "ExpectedThroughput" : "..."
            }
        },
        ...
    ],
}
```
The main idea is to retrieve connection information from every mesh node one by one in order to get full system information
##### ubus call mesh GetInetConnInfo
This call is used to retrieve information about internet connection speeds measured on mesh point. Getting response **may take some time** because of speedtest processing:
```
{
    "InternetConnection" : {
        "Download" : "...",
        "Upload" : "...",
    }
}
```
##### ubus call mesh GetClientsInfo
This call is used to retrieve information about all clients currently connected to the specific mesh node APs:
```
{
    "ActiveClients": [
        {
            "MACAddress" : "...",
            "IPAddress" : "...",
            "Hostmame" : "...",
            "ConnectionInfo" : {
                "RadioType" : "2g" | "5g",
                "RadioChannel" : "...",
                "SignalPower" : "...",
                "LinkRates" : {
                    "RxBitrate" : "...",
                    "TxBitrate" : "...",
                    "ExpectedThroughput" : "..."
                }
            }
        },
        ...
    ],
    "BlockedClients":[
        {
            "MACAddress" : "...",
            "IPAddress" : "...",
            "Hostmame" : "..."
        },
        ...
    ]
}
```
##### ubus call mesh DisconnectClient '{ "ClientIP" : "<CLIENT_IP>", "Block" : true | false }'
This call is used to disconnect or reconnect(depending on "Block" option value) mesh client specified by it's IP address:
```
{
    "Success" : true
}
```
