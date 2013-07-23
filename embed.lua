dofile("bin2c.lua")
dofile("os.lua")

function embed(dir)
	local _EMBED_DIR = _WORKING_DIR .. "/".. dir .."/"
	-- embed all lua files in the embed dir
	for i, filename in os.dir(_EMBED_DIR, "%.lua$") do
	    local file = io.open(_EMBED_DIR .. filename:gsub("%.lua$", "Lua%.c"), "w")
	    file:write(bin2c({path.getrelative(_WORKING_DIR, _EMBED_DIR .. filename)}))
	    file:close()
	end
end