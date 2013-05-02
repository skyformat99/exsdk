-- ======================================================================================
-- File         : sys_event.lua
-- Author       : Wu Jie 
-- Last Change  : 05/02/2013 | 10:45:07 AM | Thursday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

__M.type = event_type.none
__M.display = ex_c.null
__M.keycode = -1 -- we use in keycode table
__M.mouse_pos_x = -1
__M.mouse_pos_y = -1
__M.mouse_button = -1 -- -1:None, 0:left, 1:right, 2:middle

return __M
