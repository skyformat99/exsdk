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
-- copy will not create new table and copy table-refrence
-- ------------------------------------------------------------------ 

local function copy ( _t, _from )
    for k,v in pairs(_from) do
        _t[k] = v
    end
    return _t
end
__M.copy = copy

-- ------------------------------------------------------------------ 
-- Desc: 
-- deepcopy will create new table and copy the value in the table to the new table
-- ------------------------------------------------------------------ 

local function deepcopy ( _t, _from )
    for k,v in pairs(_from) do
        if type(v) == "table" then
            local tt = {}
            _t[k] = deepcopy ( tt, v )
        else
            _t[k] = v
        end
    end
    return _t
end
__M.deepcopy = deepcopy

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function add ( _t, _el )
    _t[#_t+1] = _el
    return _t
end
__M.add = add

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function add_range ( _t, _list )
    assert ( type(_list) == "table" and #_list > 0, "Invalid _list" )
    for i=1,#_list do
        _t[#_t+1] = _list[i]
    end

    return _t
end
__M.add_range = add_range

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function remove_el ( _t, _el )
    for i=1,#_t do
        if _t[i] == _el then
            table.remove(_t,i)
            break
        end
    end
end
__M.remove_el = remove_el

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function fast_remove_el ( _t, _el )
    for i=1,#_t do
        if _t[i] == _el then
            table.fast_remove_at(_t,i)
            break
        end
    end
end
__M.fast_remove_el = fast_remove_el

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function fast_remove_at ( _t, _idx )
    assert ( type(_idx) == "number" )
    if _idx > #_t then return end

    _t[_idx] = _t[#_t]
    _t[#_t] = nil
end
__M.fast_remove_at = fast_remove_at

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
