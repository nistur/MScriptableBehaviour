
local lsdir = function(path, pattern)
    local rtn = {}
    if os.is("windows") then
    else
        local _dir = assert(io.popen("ls " .. path))
        local file = _dir:read()
        while(file ~= nil) do
            if pattern == nil or file:match(pattern) ~= nil then
                rtn[#rtn+1] = file
            end
            file = _dir:read()
        end
        _dir:close()

    end

    local function dir_iter(t, i)
        i = i + 1
        local v = t[i]
        if v ~= nil then
            return i, v
        else
            return nil
        end
    end
    return dir_iter, rtn, 0
end

if os ~= nil and type(os) == "table" and os.dir == nil then
    os.dir = lsdir
else
    dir = lsdir
end