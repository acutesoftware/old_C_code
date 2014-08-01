
-- Create our main table for this addon
tblLogons = tblLogons or {};
local variablesLoaded = 0;
local logoutLogged = 0;

local frame = CreateFrame("FRAME"); -- Need a frame to respond to events
frame:RegisterEvent("ADDON_LOADED"); -- Fired when saved variables are loaded
frame:RegisterEvent("PLAYER_LOGOUT"); -- Fired when about to log out
frame:RegisterEvent("PLAYER_LOGIN");  -- Fired when logged in (best way to get ONE event fired)
frame:RegisterEvent("PLAYER_MONEY");

function frame:OnEvent(event, arg1)
	if arg1 == nil then
		arg1 = ""; 
	end
    -- print("DEBUG - entering frame:OnEvent(event, arg1)" .. event .. " , arg=" .. arg1 ); 

 	if event == "ADDON_LOADED" and arg1 == "asAuction" then
	     --print("DEBUG - entering frame:OnEvent(event, arg1): event == ADDON_LOADED (no longer used) " ); 
	elseif event == "PLAYER_LOGOUT" then
		AddLogLineLogoff();
		-- table.insert(tblLogons,  "LOGOFF:" ..  GetNameAndDate() ) ; -- now save the logon details
	elseif event == "PLAYER_LOGIN"  then
	     --print("DEBUG - entering frame:OnEvent(event, arg1): event == PLAYER_LOGIN" ); 
		AddLogLineLogon(); 
	end
end

frame:SetScript("OnEvent", frame.OnEvent);

function asAuction_initialize()
	-- setup the handler for /asHelp
	SlashCmdList["ASHELP"] = asAuction_Help;
	SlashCmdList["ASLOG"] = asAuction_Log;
	SlashCmdList["ASSTAT"] = asAuction_Stats;
	SLASH_ASHELP1 = "/ashelp";
	SLASH_ASLOG1 = "/aslog";
	SLASH_ASSTAT1 = "/asstat";
end


function Startup()
      print("Hello, and WELCOME to Auction AddOn, " .. UnitName("player") ); 
 	asAuction_initialize();
    --  print("DEBUG - function Startup: finished asAuction_initialize" ); 


  -- something wrong here 9/4/2012 -- first print line of this function works on startup, but tbl
  -- logs not updated into tblLogins. Will try declaring the table here as well, and doing the code
  -- for GetNameAndDate, but need to look into a correct register event above for PLAYER_LOGIN
  -- NOTE - the logs never seemed to work on startup (only the print), looking at previous versions



end

function asAuction_Help(msg)
	-- this function handles the help command
	local txt = date("%y-%m-%d %H:%M:%S") .. " " .. UnitName("player")  .. " " .. msg
	txt = txt .. "Acute Software's WOW AddOn\n"
	txt = txt .. "Type the following commands:\n"
	txt = txt .. "/aslog = show recent logons\n"
	txt = txt .. "/asstat = log all equipment stats\n"
	txt = txt .. "/ashelp = this screen\n"
	txt = txt .. "/ashelp LOG = force a logon LOG event\n"
      ChatFrame1:AddMessage(txt); -- shows the text in the chat frame	
    --  message(txt);               -- pops up a dialog box
 
	if msg == "LOG" then
		-- table.insert(tblLogons,  date("%y-%m-%d %H:%M:%S") .. " - " .. UnitName("player") ) ; 
		AddLogLineLogon();
	end

end

function AddLogLineLogon()
	local copper = GetMoney() ;
	local txt = date("%y-%m-%d %H:%M:%S") .. " - " .. UnitName("player")  .. ", Gold = " .. ("%dg %ds %dc"):format(copper / 100 / 100, (copper / 100) % 100, copper % 100) ;

	if tblLogons == nil then
	   tblLogons = {} ; -- This is the first time this addon is loaded; clear the table.
	end
	table.insert(tblLogons,   "LOGON: " ..  txt ) ; -- now save the logon details

end

function AddLogLineLogoff()
	local copper = GetMoney() ;
	local txt = date("%y-%m-%d %H:%M:%S") .. " - " .. UnitName("player")  .. ", Gold = " .. ("%dg %ds %dc"):format(copper / 100 / 100, (copper / 100) % 100, copper % 100) ;

	if tblLogons == nil then
	   tblLogons = {} ; -- This is the first time this addon is loaded; clear the table.
	end
	table.insert(tblLogons,   "LOGOFF: " ..  txt ) ; -- now save the logon details

end


function asAuction_Log() 
  print("Hello, and Welcome to Duncan's AddOn, " .. UnitName("player") .. ".   (Version 1.0.3)" ); 
   --  ChatFrame1:AddMessage("Last logon " .. tblLogons[1] .. " ."); -- shows the text in the chat frame	
  table.foreach(tblLogons, print) 
  
-- for key,value in pairs(myTable) do print(key,value) end;

-- table.insert(tblLogons,   GetNameAndDate() ) ; 


end

function asAuction_Stats() 
	ShowEquipmentStats() ; 
	ShowXP(); 
end

function GetNameAndDate()
	local playerName = UnitName("player");
	local dateStamp = date("%y-%m-%d %H:%M:%S");
	-- ChatFrame1:AddMessage('Hi my name is: ' .. playerName);
	local txt = dateStamp .. " - " .. playerName;
	return txt;

end


function ShowXP()
	local e=UnitXP("player"); 
	local m=UnitXPMax("player"); 
	local b=m/20; 
	local rba=floor((e/b)*10+0.5)/10; 
	local rbb=floor((20-(e/b))*10+0.5)/10; 
	local txt = "I am "..rba.." bars into "..UnitLevel("player").." ("..rbb.." bars left)" ;
	-- SendChatMessage(txt ,"PARTY",nil); 
	print (txt); 
end

function ShowEquipmentStats()
	local nme = ""; 
	local lnk = 0; 
	local itemLink = 0;
	local slotId = 0;
	for slotId = 1 , 19 do
		itemLink = GetInventoryItemLink("player", slotId) ; 
		if itemLink ~= nil then
			-- print("The item link is: " .. itemLink); 
	       	nme, lnk =  GetItemInfo(itemLink) ; 
			print("Slot " .. slotId .. "  = " .. itemLink);
		else
			print("Slot " .. slotId .. "  = Empty " );

		end
      end
 


end




















