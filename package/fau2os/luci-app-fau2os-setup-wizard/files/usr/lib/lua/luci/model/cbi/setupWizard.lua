
WizardMap = Map("fmesh", translate("Mesh Setup Wizard"), translate("Configure your mesh network in few simple steps"))
WizardMap.template = "cbi/mWizardMap"
WizardMap.apply_on_parse = true

WizardMap.on_after_apply = function(self)
    luci.sys.call("mesh-conf profile && mesh-conf index &")
end

SystemSection = WizardMap:section(TypedSection, "system", "System settings")
SystemSection.template = "cbi/mSystemSection"

local option_one = SystemSection:option(ListValue, "node_id_one", translate("Base Id part:"), translate("In most cases default value is OK"))
for hex = 2, 254 do
    option_one:value(string.format("%02X", hex), string.format("%02X", hex))
end

local option_two = SystemSection:option(ListValue, "node_id_two", translate("Node Id part:"), translate("Should be unique within the same Base Id"))
for hex = 2, 254, 4 do
    option_two:value(string.format("%02X", hex), string.format("%02X", hex))
end

local Routing = SystemSection:option(ListValue, "network_profile", translate("Routing strategy:"))
Routing:value("bmx", translate("BMX7"))
Routing:value("bat", translate("Batman-Adv"))
Routing:value("bat+bmx", translate("Full Routing"))

return WizardMap
