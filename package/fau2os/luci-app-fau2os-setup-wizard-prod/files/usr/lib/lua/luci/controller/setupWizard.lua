
module("luci.controller.setupWizard", package.seeall)

function index()
    local EntryObject = entry({"admin", "setupWizard"}, cbi("setupWizard",{autoapply=false,hideapplybtn=false,hidesavebtn=true,hideresetbtn=true}), "setupWizard", 60)
    EntryObject.dependent=false
end
