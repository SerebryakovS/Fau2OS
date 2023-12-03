import requests
import json

Url = "http://fau2.net/ubus"

Headers = {
  'Content-Type': 'application/json'
}
Payload = json.dumps({
  "jsonrpc": "2.0",
  "id": 1,
  "method": "call",
  "params": [
    "00000000000000000000000000000000",
    "session",
    "login",
    {
      "username": "root",
      "password": ""
    }
  ]
})
##
AccessToken = requests.request("POST", Url, headers=Headers, data=Payload).json()["result"][1]["ubus_rpc_session"]
print(f"Access Token Received:{AccessToken}");
##
Payload = json.dumps({
  "jsonrpc": "2.0",
  "id": 20,
  "method": "call",
  "params": [
    AccessToken,
    "mesh",
    "GetClientsInfo",
    {}
  ]
})
print(requests.request("POST", Url, headers=Headers, data=Payload).json())
Payload = json.dumps({
  "jsonrpc": "2.0",
  "id": 20,
  "method": "call",
  "params": [
    AccessToken,
    "mesh",
    "GetInetConnInfo",
    {
      "Hostname" : "mesh_slave_2"
    }
  ]
})
print(requests.request("POST", Url, headers=Headers, data=Payload).json())
Payload = json.dumps({
  "jsonrpc": "2.0",
  "id": 20,
  "method": "call",
  "params": [
    AccessToken,
    "mesh",
    "GetMeshConnInfo",
    {
      "Hostname" : "mesh_slave_2"
    }
  ]
})
print(requests.request("POST", Url, headers=Headers, data=Payload).json())

# Examples output:
# {'jsonrpc': '2.0', 'id': 20, 'result': [0, {'ActiveClients': [{'MACAddress': 'b4:0e:de:89:95:5e', 'IPAddress': '192.168.1.170', 'Hostmame': 'asusvbook', 'ConnectionInfo': {'RadioType': '5g', 'RadioChannel': '153', 'SignalPower': '-35', 'LinkRates': {'RxBitrate': '6.0', 'TxBitrate': '108.0', 'ExpectedThroughput': '41.1'}}}], 'BlockedClients': '[]'}]}
# {'jsonrpc': '2.0', 'id': 20, 'result': [0, {'Hostname': 'mesh_slave_2', 'InternetConnection': {'Download': '25.87', 'Upload': '36.72'}}]}
# {'jsonrpc': '2.0', 'id': 20, 'result': [0, {'MeshConnections': [{'TargetHostname': 'mesh_slave_1', 'SignalPower': ' -63', 'LinkRates': {'RxBitrate': ' 6.5', 'TxBitrate': ' 6.5', 'ExpectedThroughput': ' 4.394'}}, {'TargetHostname': 'mesh_master', 'SignalPower': ' -40', 'LinkRates': {'RxBitrate': ' 324.0', 'TxBitrate': ' 300.0', 'ExpectedThroughput': ' 58.43'}}], 'Hostname': 'mesh_slave_2'}]}

