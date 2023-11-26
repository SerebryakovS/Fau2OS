
from json import dumps
from requests import post

class Requester(object):
    def __init__(self, Hostname):
        self.MessageIndex = 0;
        self.EndpointBase = f"http://{Hostname}/cgi-bin/luci/rpc"
    def SendUbusHTTPRequest(self, URL:str, RequestBody:dict):
        self.MessageIndex+=1;
        RequestBody["id"] = self.MessageIndex;
        Headers = {'Content-type': 'application/json'}
        return post(URL, data=dumps(RequestBody), headers=Headers).json();

    def Login(self, Username, Password):
        ResponseBody = self.SendUbusHTTPRequest(self.EndpointBase+"/auth",{
            "id": 0,
            "method": "login",
            "params": [ Username, Password ]
        })
        self.AccessToken = ResponseBody["result"]
        print(self.AccessToken)

    def GetNetworkConfig(self, InterfaceName:str):
        Params = [ "network" ]
        if len(InterfaceName) > 0:
            Params.append(InterfaceName)
        ResponseBody = self.SendUbusHTTPRequest(self.EndpointBase+f"/uci?auth={self.AccessToken}",{
            "id": 0,
            "method": "get_all",
            "params": Params
        })
        return ResponseBody["result"]

    def GetWirelessDeviceConfig(self, InterfaceName:str):
        Params = [ "wireless" ]
        if len(InterfaceName) == 0:
            Params.append(InterfaceName)
        ResponseBody = self.SendUbusHTTPRequest(self.EndpointBase+f"/uci?auth={self.AccessToken}",{
            "id": 0,
            "method": "get_all",
            "params": Params
        })
        return ResponseBody["result"]

    def GetWirelessStatus(self,InterfaceName:str):
        ResponseBody = self.SendUbusHTTPRequest(self.EndpointBase+f"/sys?auth={self.AccessToken}",{
            "id": 0,
            "method": "wifi.getiwinfo",
            "params": [InterfaceName]
        })
        return ResponseBody["result"]


