-- ======================================================================================
-- File         : table.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 16:59:48 PM | Monday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function contains (_t,_v)
    for _,v in pairs(_t) do
        if v == _v then
            return true
        end
    end
    return false
end
__M.contains = contains

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function add ( _to, _from )
    for k,v in pairs(_from) do
        _to[k] = v
    end
    return _to
end
__M.add = add

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
