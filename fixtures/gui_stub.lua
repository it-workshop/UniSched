#!/usr/bin/env lua

-- Load the wxLua module, does nothing if running from wxLua, wxLuaFreeze, or wxLuaEdit
require("wx")

frame = nil

-- paint event handler for the frame that's called by wxEVT_PAINT
function OnPaint(event)
    -- must always create a wxPaintDC in a wxEVT_PAINT handler
    local dc = wx.wxPaintDC(panel)
    -- call some drawing functions
    dc:DrawRoundedRectangle(20, 20, 280, 280, 20);
    dc:DrawText("A test string", 50, 150);
    -- the paint DC will be automatically destroyed by the garbage collector,
    dc:delete() -- ALWAYS delete() any wxDCs created when done
end

function main()
    frame = wx.wxFrame( wx.NULL,            -- no parent for toplevel windows
                        wx.wxID_ANY,          -- don't need a wxWindow ID
                        "wxLua Raspisator GUI Demo", -- caption on the frame
                        wx.wxDefaultPosition, -- let system place the frame
                        wx.wxSize(450, 450),  -- set the size of the frame
                        wx.wxDEFAULT_FRAME_STYLE ) -- use default frame styles

    panel = wx.wxPanel(frame, wx.wxID_ANY)

    panel:Connect(wx.wxEVT_PAINT, OnPaint)

    local fileMenu = wx.wxMenu()
    fileMenu:Append(wx.wxID_EXIT, "E&xit", "Quit the program")

    local helpMenu = wx.wxMenu()
    helpMenu:Append(wx.wxID_ABOUT, "&About", "About the Raspisator")

    local menuBar = wx.wxMenuBar()
    menuBar:Append(fileMenu, "&File")
    menuBar:Append(helpMenu, "&Help")

    frame:SetMenuBar(menuBar)

    frame:CreateStatusBar(1)
    frame:SetStatusText("Welcome to wxLua Raspisator GUI.")

    frame:Connect(wx.wxID_EXIT, wx.wxEVT_COMMAND_MENU_SELECTED,
                  function (event) frame:Close(true) end )

    frame:Connect(wx.wxID_ABOUT, wx.wxEVT_COMMAND_MENU_SELECTED,
        function (event)
            wx.wxMessageBox('Something very important.\n'..
                            wxlua.wxLUA_VERSION_STRING.." built with "..wx.wxVERSION_STRING,
                            "About wxLua Raspisator GUI",
                            wx.wxOK + wx.wxICON_INFORMATION,
                            frame)
        end )

    frame:Show(true)
end

main()
wx.wxGetApp():MainLoop()

