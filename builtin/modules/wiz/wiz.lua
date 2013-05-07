-- ======================================================================================
-- File         : wiz.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 16:56:37 PM | Tuesday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local platform = ex_c.platform
__M.platform = platform

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local cwd = ex_c.fsys_app_dir()
__M.cwd = cwd

-- ------------------------------------------------------------------ 
-- Desc: the arguments will be set by exsdk through __lua_wiz_init()
-- ------------------------------------------------------------------ 

local arguments = {}
__M.arguments = arguments

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local open_app = function ( _self, _path )
    -- if we have app open, close it first
    if wiz.app.cwd ~= nil and wiz.app.cwd ~= "" then
        wiz:close_app ()
    end

    ex_c.open_app(_path)
    wiz.app.cwd = ex_c.fsys_writedir()

    if wiz.app.exists("init.lua") then
        ex_c.lua_dofile ( wiz.app.fsys_path("init.lua") )
    end

    if _self.on_init ~= nil then
        _self.on_init()
    end
end
__M.open_app = open_app

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local close_app = function ( _self )
    if _self.on_close ~= nil then
        _self.on_close()
    end
    ex_c.close_app()
    wiz.app.cwd = ""
end
__M.close_app = close_app

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
