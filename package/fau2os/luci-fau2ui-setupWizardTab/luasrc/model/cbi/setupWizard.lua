
WizardMap = Map("fmesh", translate("Mesh Setup Wizard"), translate("Configure your mesh network in few simple steps"))
WizardMap.template = "cbi/mWizardMap"
WizardMap.apply_on_parse = true

WizardMap.on_after_apply = function(self)
    local uci = require("uci").cursor()
    local part1 = uci:get("fmesh", "@system[0]", "id_part1") or ""
    local part2 = uci:get("fmesh", "@system[0]", "id_part2") or ""
    local part3 = uci:get("fmesh", "@system[0]", "id_part3") or ""
    local newMAC = part1 .. part2 .. part3
    luci.sys.call("echo '[FAU2OS-utils]: New BSSID part: " .. newMAC .. "' > /dev/kmsg")
    luci.sys.call("mesh-conf libre " .. newMAC)
end

SystemSection = WizardMap:section(TypedSection, "system", "System settings")
SystemSection.template = "cbi/mSystemSection"

for i = 1, 3 do
    local option = SystemSection:option(ListValue, "id_part" .. i, "")
    for hex = 0, 255 do
        option:value(string.format("%02X", hex), string.format("%02X", hex))
    end
end

return WizardMap


-- local fs  = require "nixio.fs"
-- local has_pptp  = fs.access("/usr/sbin/pptp")
-- local has_pppoe = fs.glob("/usr/lib/pppd/*/rp-pppoe.so")()

-- WizardMap = Map("fmesh", translate("Mesh Setup Wizard"), translate("Configure your mesh network in few simple steps"))
-- WizardMap.template = "cbi/mWizardMap"
-- WizardMap.apply_on_parse = true
--
-- WizardMap.on_after_apply = function(self)
-- 	luci.sys.call("echo '[WIUOS-utils]: on_after_apply started' > /dev/kmsg")
--     luci.sys.call("mesh-wan")
--     luci.sys.call("echo '[WIUOS-utils]: mesh-wan finished WAN configuration' > /dev/kmsg")
--     luci.sys.call("mesh-conf $(uci get fmesh.@system[0].role | tr '_' ' ')")
-- end
--
-- SystemSection = WizardMap:section(TypedSection, "system", "System settings")
-- SystemSection.template = "cbi/mSystemSection"
--
-- RoleOption = SystemSection:option(ListValue, "role", "Role selection")
-- SlavesNote = SystemSection:option(DummyValue, "dummy_slaves", "", "<h3>No additional settings required for <span style='color:yellow'>Slave</span></h3>")
-- MasterNote = SystemSection:option(DummyValue, "dummy_master", "", "<h3>To finish initial setup for <span style='color:yellow'>Master</span>, specify WAN settings</h3>")
-- RoleOption:value("none", "none")
-- RoleOption:value("master", "master")
-- RoleOption:value("slave_1", "slave 1")
-- RoleOption:value("slave_2", "slave 2")
-- MasterNote:depends({role="master"})
-- SlavesNote:depends({role="slave_1"})
-- SlavesNote:depends({role="slave_2"})
-- RoleOption.default = "none"


-- -- -- -- WAN configuration
-- -- -- ProtoOption = SystemSection:option(ListValue, "wan_proto", translate("Protocol"))
-- -- -- ProtoOption:depends("role","master")
-- -- -- ProtoOption.override_values = true
-- -- -- ProtoOption:value("none", "disabled")
-- -- -- ProtoOption:value("static", translate("manual (static IP)"))
-- -- -- ProtoOption:value("dhcp", translate("automatic (DHCP)"))
-- -- --
-- -- -- function ProtoOption.write(self, section, value)
-- -- -- 	if value == "pptp" or value == "pppoe" then
-- -- -- 		self.map:set(section, "peerdns", "1")
-- -- -- 		self.map:set(section, "defaultroute", "1")
-- -- -- 	end
-- -- -- 	return ListValue.write(self, section, value)
-- -- -- end
-- -- -- -------------------------------------------------------------------------------------------------------------------------
-- -- -- Ipaddr = SystemSection:option(Value, "wan_ipaddr", translate("<abbr title=\"Internet Protocol Version 4\">IPv4</abbr>-Address"))
-- -- -- Ipaddr:depends("wan_proto", "static")
-- -- -- Ipaddr.template = "cbi/mIpOption"
-- -- -- Ipaddr.datatype = "ipaddr"
-- -- -- ProtoOption.override_values = true
-- -- -- Netmask = SystemSection:option(Value, "wan_netmask", translate("<abbr title=\"Internet Protocol Version 4\">IPv4</abbr>-Netmask"))
-- -- -- Netmask:depends("wan_proto", "static")
-- -- -- Netmask.template = "cbi/mIpOption"
-- -- -- Netmask.datatype = "ipaddr"
-- -- -- Gateway = SystemSection:option(Value, "wan_gateway", translate("<abbr title=\"Internet Protocol Version 4\">IPv4</abbr>-Gateway"))
-- -- -- Gateway:depends("wan_proto", "static")
-- -- -- Gateway.template = "cbi/mIpOption"
-- -- -- Gateway.datatype = "ipaddr"
-- -- -- Gateway.rmempty = true
-- -- -- Dns = SystemSection:option(Value, "wan_dns", translate("<abbr title=\"Domain Name System\">DNS</abbr>-Server"))
-- -- -- Dns:depends("wan_proto", "static")
-- -- -- Dns.template = "cbi/mIpOption"
-- -- -- Dns.datatype = "ipaddr"
-- -- -- Dns.rmempty = true
-- -- -- -------------------------------------------------------------------------------------------------------------------------
-- -- -- if has_pppoe then
-- -- --     ProtoOption:value("pppoe", "PPPoE")
-- -- -- end
-- -- -- if has_pptp then
-- -- --     ProtoOption:value("pptp",  "PPTP")
-- -- -- end
-- -- -- -- if not ( has_pppoe and has_pptp ) then
-- -- -- -- 	ProtoOption.description = translate("You need to install \"ppp-mod-pppoe\" for PPPoE or \"pptp\" for PPtP support")
-- -- -- -- end
-- -- --
-- -- -- Username = SystemSection:option(Value, "username", translate("Username"))
-- -- -- Username:depends("wan_proto", "pppoe")
-- -- -- Username:depends("wan_proto", "pptp")
-- -- -- Password = SystemSection:option(Value, "password", translate("Password"))
-- -- -- Password.password = true
-- -- -- Password:depends("wan_proto", "pppoe")
-- -- -- Password:depends("wan_proto", "pptp")
-- -- -- kea = SystemSection:option(Flag, "keepalive", translate("automatically reconnect"))
-- -- -- kea:depends("wan_proto", "pppoe")
-- -- -- kea:depends("wan_proto", "pptp")
-- -- -- kea.rmempty = true
-- -- -- kea.enabled = "10"
-- -- -- cod = SystemSection:option(Value, "demand", translate("disconnect when idle for"))
-- -- -- cod:depends("wan_proto", "pppoe")
-- -- -- cod:depends("wan_proto", "pptp")
-- -- -- cod.rmempty = true
-- -- -- srv = SystemSection:option(Value, "server", translate("<abbr title=\"Point-to-Point Tunneling Protocol\">PPTP</abbr>-Server"))
-- -- -- srv:depends("wan_proto", "pptp")
-- -- -- srv.rmempty = true
------------------------------------------------------------------------------------

-- -- if fs.access("/etc/config/firewall") then
-- -- 	mssfix = SystemSection:option(Flag, "_mssfix",
-- -- 		translate("Clamp Segment Size"), translate("Fixes problems with unreachable websites, submitting forms or other unexpected behaviour for some ISPs."))
-- -- 	mssfix.rmempty = false
-- -- 	mssfix:depends("role","master")
-- -- 	function mssfix.cfgvalue(self)
-- -- 		local value
-- -- 		WizardMap.uci:foreach("firewall", "forwarding", function(s)
-- -- 			if s.src == "lan" and s.dest == "wan" then
-- -- 				value = s.mtu_fix
-- -- 			end
-- -- 		end)
-- -- 		return value
-- -- 	end
-- -- 	function mssfix.write(self, section, value)
-- -- 		WizardMap.uci:foreach("firewall", "forwarding", function(s)
-- -- 			if s.src == "lan" and s.dest == "wan" then
-- -- 				WizardMap.uci:set("firewall", s[".name"], "mtu_fix", value)
-- -- 				WizardMap:chain("firewall")
-- -- 			end
-- -- 		end)
-- -- 	end
-- -- end

-- -- return WizardMap

