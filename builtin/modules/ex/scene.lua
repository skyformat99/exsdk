-- ======================================================================================
-- File         : scene.lua
-- Author       : Wu Jie 
-- Last Change  : 02/23/2013 | 16:03:34 PM | Saturday,February
-- Description  : 
-- ======================================================================================

local __M = {}

local __nodes = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function tick ()
    -- update entities and its components
    for _,node in ipairs(__nodes) do
        node:update()
    end

    -- commit transforms
    -- TODO: ex_c.pack_nodes () -- pack the node by DOP design as SONY said.
    -- TODO: ex_c.update_transforms ()

    -- batch draw by layer
end
__M.tick = tick

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function new_node ( _name )
    local node = ex.node(_name)
    __nodes[#__nodes+1] = node
    return node
end
__M.new_node = new_node

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
