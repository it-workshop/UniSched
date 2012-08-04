#!/usr/bin/env lua

require "wx"
require "bit"

f = wx.wxFrame(wx.NULL, wx.wxID_ANY, "UniSched")

types_list = wx.wxListCtrl(f, wx.wxID_ANY, wx.wxPoint(10, 10), wx.wxSize(200, 200), bit.bor(wx.wxLC_LIST, wx.wxLC_SINGLE_SEL), wx.wxDefaultValidator, "types_list")
types_list:InsertItem(0, "People")
types_list:InsertItem(1, "Groups")
types_list:InsertItem(2, "Events")
types_list:InsertItem(3, "Resources")

event_presets_list = wx.wxListCtrl(f, wx.wxID_ANY, wx.wxPoint(220, 10), wx.wxSize(200, 200), bit.bor(wx.wxLC_LIST, wx.wxLC_SINGLE_SEL), wx.wxDefaultValidator, "presets_list")
event_presets_list:Show(false)
event_presets_list:InsertItem(0, "Lections")
event_presets_list:InsertItem(1, "Work")
event_presets_list:InsertItem(2, "Pleasure")

people_list = wx.wxListCtrl(f, wx.wxID_ANY, wx.wxPoint(220, 10), wx.wxSize(400, 200), bit.bor(wx.wxLC_REPORT, wx.wxLC_SINGLE_SEL), wx.wxDefaultValidator, "people_list")
people_list:InsertColumn(0, "name")
people_list:InsertColumn(1, "surname")
people_list:InsertColumn(2, "sex")

i = 0
for k, o in pairs(search({})) do
    if o.type() == 'person' then
        print(o.name)
        local cell = wx.wxListItem()
        cell.SetText(o.read('name'))
        cell.SetColumn(0)
--        cell.SetId(i)
        people_list:InsertItem(cell)
--[[
        cell = wx.wxListItem()
        cell.SetText(o.read('surname'))
        cell.SetColumn(1)
        cell.SetId(i)
        people_list:InsertItem(cell)

        cell = wx.wxListItem()
        cell.SetText(o.read('sex'))
        cell.SetColumn(2)
        cell.SetId(i)
        people_list:InsertItem(cell)]]--
    end
end

f:Show(true)
wx.wxGetApp():MainLoop()

