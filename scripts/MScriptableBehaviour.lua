--[[
MScriptableBehavior.lua

This file is a modified version of "32 Lines of Goodness"
http://love2d.org/wiki/32_lines_of_goodness

Obviously it's no longer 32 lines, nor is it any more a 
general class implementation, instead it supports purely
lua implementations of Maratis Behaviors

TODO: 
- Push values from the class definition to expose in 
  Maratis Editor
- Extend the MScriptableBehavior interface to wrap up
  common functions and not require digging around in
  self.__id.object
--]]

local function define(class, members)
   class.__members__ = class.__members__ or {}
   for k, v in pairs(members) do
      class.__members__[k] = v
   end
end

local behavior_table = {}

function MScriptableBehavior(name)
   behavior_table[name] = {}

   local newclass = {}

   newclass.onBegin = function(object, behavior)
      local newvalue = {}
      for k,v in pairs(newclass.__members__) do
         newvalue[k] = table.copy(v)
      end
      newvalue.__id = { object = object, behavior = behavior }

      behavior_table[name][object] = newvalue

      if newvalue.onBegin then newvalue:onBegin() end
   end

   newclass.update = function(object, behavior)
      obj = behavior_table[name][object]
      if obj == nil then print("Unable to find behavior to update"); return end

      if obj.update then obj:update() end
   end

   newclass.onEnd = function(object, behavior)
      obj = behavior_table[name][object]
      if obj == nil then return end

      if obj.onEnd then obj:onEnd() end
      behavior_table[name][object] = nil
   end

   newclass.get = function(object)
      return behavior_table[name][object]
   end

   _G[name] = newclass
   return setmetatable(newclass, {__index = {}, __call = define})
end

--[[ load all behavior scripts ]]
local behavior_scripts = readDirectory("behaviors")
for i=1, #behavior_scripts do
   dofile("behaviors/" .. behavior_scripts[i])
end
