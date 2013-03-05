-- ======================================================================================
-- File         : enums.lua
-- Author       : Wu Jie 
-- Last Change  : 02/28/2013 | 10:58:02 AM | Thursday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local blend_op = {
    add = 0,
    src_minus_dest = 1,
    dest_minus_src = 2,
} 
__M.blend_op = blend_op

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local blend_mode = {
    zero = 0,
    one = 1,
    alpha = 2,
    inverse_alpha = 3,
}
__M.blend_mode = blend_mode

return __M
