-- ======================================================================================
-- File         : defs.lua
-- Author       : Wu Jie 
-- Last Change  : 05/06/2013 | 10:40:22 AM | Monday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- TODO: useful when we optimize style to C { 
-- local font = {

--     style = {
--         normal = 0,
--         italic = 1,
--         oblique = 2,
--     },

--     decoration = {
--         none = 0,
--         underline = 1,
--         overline = 2,
--         through = 3, 
--     },

--     extra_style = {
--         none = 0,
--         outline = 1,
--         shadow = 2,
--     },
-- }
-- __M.font = font
-- } TODO end 

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local event = {
    type = event_type.none,

    keycode = keycode.None, -- we use in keycode table
    shift = false,
    ctrl = false,
    alt = false,
    command = false,
    capslock = false,

    mouse_pos = {0,0},
    mouse_delta = {0,0},
    mouse_button = -1, -- -1:None, 0:left, 1:right, 2:middle
    mouse_click_count = 0
}
__M.event = event

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
