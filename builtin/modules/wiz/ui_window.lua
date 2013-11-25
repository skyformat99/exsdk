-- ======================================================================================
-- File         : ui_window.lua
-- Author       : Wu Jie 
-- Last Change  : 11/20/2013 | 00:08:28 AM | Wednesday,November
-- Description  : 
-- ======================================================================================

local __M = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local ui_window = wiz.window.extend ({
    __typename = "ui_window",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        _self.__super.__init( _self, _w, _h )
        _self.widget_mng = ui.widget_mng(_w,_h)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    widget_mng = nil,

    --/////////////////////////////////////////////////////////////////////////////
    -- overwrite events
    --/////////////////////////////////////////////////////////////////////////////

    on_resize = function ( _self, _w, _h )
        _self.widget_mng.width = _w
        _self.widget_mng.height = _h
    end,
}) 
__M.ui_window = ui_window

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M