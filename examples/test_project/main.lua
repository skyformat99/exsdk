-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

local tex1
local btfont1

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function init() 
    print ( "" )
    print ( "=======================" )
    print ( "start" )
    print ( "=======================" )
    print ( "" )

    tex1 = editor.asset_db.load("grossini_dance_09.png")
    -- editor.asset_db.load("uv.jpg")

    btfont1 = editor.asset_db.load("BerlinSansFB_MonoOutline.bft")
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function deinit() 
    ex_c.close_project()

    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function update()
    -- TODO
    -- print ( "Hello World!" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function render()
    ex_c.canvas_clear( 0.5, 0.5, 0.5 )

    -- ex_c.canvas_draw_texture( tex1._cptr, 0.0, 0.0 )
    ex_c.canvas_draw_texture( btfont1.pageInfos[0]._cptr, 0.0, 0.0 )

    ex_c.canvas_flush()
end

-- ------------------------------------------------------------------ 
-- TEST: 
-- ------------------------------------------------------------------ 

-- v1 = ex.vec2f ( 1.0, 2.0 )
-- v2 = v1:copy()
-- v2.x = 10.0
-- v2.y = 5.0

-- v3 = v1 + v2
-- print ( "v1 = " .. v1 )
-- print ( "v2 = " .. v2 )

-- v3 = ex.vec2f.lerp( v1, v2, 0.5 )
-- print ( "v3 = " .. v3.normalized )

-- debug.dump ( v1, "v1" )
-- debug.dump ( v2, "v2" )
