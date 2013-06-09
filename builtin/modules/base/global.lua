-- ======================================================================================
-- File         : global.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 17:16:22 PM | Monday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- DISABLE: we are using lua_pcall with traceback function, so no use for error and assert traceback { 
-- -- ------------------------------------------------------------------ 
-- -- Desc: 
-- -- ------------------------------------------------------------------ 

-- local builtin_error = error
-- local function error ( _msg, ... )
--     print( _msg, ... ) 
--     print(debug.traceback())
--     builtin_error(_msg, ...)
-- end
-- __M.error = error

-- -- ------------------------------------------------------------------ 
-- -- Desc: 
-- -- ------------------------------------------------------------------ 

-- local builtin_assert = assert
-- local function assert ( _exp, ... )
--     if _exp == nil or _exp == false then 
--         print(...) 
--         print(debug.traceback()) 
--     end
--     builtin_assert(_exp, ...)
-- end
-- __M.assert = assert
-- } DISABLE end 

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function checkarg ( _arg, _typename )
    assert ( typename(_arg) == _typename, 
             string.format("Type error: must be %s", _typename ) )
end
__M.checkarg = checkarg

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function TODO ( ... )
    assert ( false, ... )
end
__M.TODO = TODO

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
