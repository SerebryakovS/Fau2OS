
## Meshok System RestAPI V1.0
All backend implementation is located in: /usr/libexec/rpcd/mesh
The package uhttpd-mod-ubus must be installed before using described API
--------------------
### Mesh Network API
--------------------
##### ubus call mesh GetMeshNetworkOverview '{ "SearchFrom" : "..." }'
This call is used to get fast mesh network overview to build the round map:
```
{
    "Success" : true,
    "MeshNodes" : [
        {
            "HopsToMe" : "...", // 0 - for closest
            "NetworkDeviceInfo" : {
                "MACAddress" : "...",
                "IPv4Address" : "...",
                "IPv6Address" : "...",
                "Hostmame" : "..."
            }
        },
        ...
    ]
}
```
##### ubus call mesh GetMeshNetworkDirectLinksMap '{ "SearchFrom" : "...", "RoutesDepth" : "..." }'
This call is used to get all connection chains in mesh network relatively to closest node:
```
{
    "Success" : true,
    "MeshLinksChains" : [
        {
            "Hostname" : "...",
            "RouteType" : "default" | "custom",
            "WirelessSignalPowerRatio" : "...",
            "LinkStatus" : {
                "RxBitrate" : "...",
                "TxBitrate" : "...",
                "ExpectedThroughput" : "..."
            },
            "NextLink" : {
                ...
            }
        },
        ...
    ]
}
```
##### ubus call mesh DefineCustomMeshRoute '{ "MeshRoutesChain" : [ <MeshHostname1> , <MeshHostname2>, ... ] }'
This call is used to get all connection chains in mesh network relatively to closest node:
```
{
    "Success" : true
}
```
##### ubus call mesh GetMeshNetworkWANStatus '{ "SearchFrom" : "...", "RoutesDepth" : "..." }'
This call is used to get all available WAN connection in specified mesh network routes depth:
```
{
    "Success" : true,
    "IsInternetConnExist" : "true" | "false",
    "WANConnections": [
        <MeshNodeHostname>, ...
    ]
}
```
##### ubus call mesh GetMeshNetworkClientsInfo
This call is used to retrieve information about all clients currently connected to the specific mesh node APs:
```
{
    "Success" : true,
    "ActiveClients": [
        {
            "ClosestNodeHostname" : "...",
            "NetworkDeviceInfo" : {
                "MACAddress" : "...",
                "IPv4Address" : "...",
                "Hostmame" : "..."
            },
            "ConnectionType" : "2ghz" | "5ghz" | "eth",
            "WirelessSignalPowerRatio" : "...", # empty for eth
            "LinkStatus" : {
                "RxBitrate" : "...",
                "TxBitrate" : "...",
                "ExpectedThroughput" : "..."
            }
        },
        ...
    ],
    "BlockedClients":[
        {
            "NetworkDeviceInfo" : {
                "MACAddress" : "...",
                "IPv4Address" : "...",
                "Hostmame" : "..."
            },
            "BlockDatetime" : "..."
        },
        ...
    ]
}
```
##### ubus call mesh DisconnectMeshNetworkClient '{ "ClientIP" : "...", "Block" : "true" | "false" }'
This call is used to disconnect permanently or reconnect(depending on "Block" option value) mesh client specified by it's IP address:
```
{
    "Success" : true
}
```
------------------------
### Single Mesh Node API
------------------------
##### ubus call mesh RebootMeshNode '{ "Hostname" : "..." , "ResetNetworkServicesOnly" : "true" | "false" }'
This call is used to reboot specific mesh router (or reset it's network/wireless services depending on "ResetNetworkServicesOnly" option), specified by it's Hostname:
```
{
    "Success" : "true"
}
```
##### ubus call mesh ConfigureMeshNodeWAN '{ "Hostname" : "..." , "Mode" : "Static" , "IPv4Address" : "..." , "Mask" : "..." , "DNS" : "...", "Gateway" : "..." }'
##### ubus call mesh ConfigureMeshNodeWAN '{ "Hostname" : "..." , "Mode" : "Dhcp" }'
These calls are used to configure WAN interface on specific mesh node:
```
{
    "Success" : "true"
}
```
##### ubus call mesh GetMeshNodeWANSpeedTest '{ "Hostname" : "..." }'
This call is used to trigger speed test for WAN channel on specified mesh node:
```
{
    "Success" : "true",
    "Status" : "Running" | "Done"
    "SpeedTestReport" : {
        "DownloadSpeed" : "...",
        "UploadSpeed" : "..."
    }
}
```
------------------------
### Error message format
------------------------
All above calls return following message in case of any failure:
```
{
    "Success" : "false",
    "ErrorMessage" : "..." (optional)
}
```



