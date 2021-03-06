-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 11/19/2013 | 16:03:32 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

print ( "" )
print ( "=======================" )
print ( "start" )
print ( "=======================" )
print ( "" )

-- create window
local window = wiz.window( 640, 480 )

-- load resource, NOTE: texture resource must be load after first window created
local font1 = bundle:load("assets/VeraMono.ttf")
local font2 = bundle:load("assets/BerlinSansFB_MonoOutline.bft")
local font3 = bundle:load("assets/MolotShadow.bft")
local logo = bundle:load("assets/ex2d_logo.png")
local imgWindow = bundle:load("assets/windowActive.png")

--
window.onRepaint = function ( self )
    -- ex.painter.color = ex.color4f.white
    -- ex.painter.bitmapText( "Hello World", font2, 10, 10 )

    -- ex.painter.color = ex.color4f.green
    -- ex.painter.text( "Hello World", font1, 10, 50 )

    ex.painter.color = ex.color4f.white
    local size = { w = logo.width, h = logo.height } 
    ex.painter.image( logo, 
    self.width - 10 - size.w, 
    self.height - 10 - size.h,
    size.w,
    size.h )

    ex.painter.color = ex.color4f.white
    ex.painter.slicedImage( imgWindow, 
    100, 100, 200, 300,
    27, 14, 15, 14 )

    -- ex.painter.color = ex.color4f( 1.0, 0.0, 0.0, 0.5 )
    -- ex.painter.filledRect( 100, 100, 200, 300 )

    -- ex.painter.color = ex.color4f( 1.0, 1.0, 0.0, 1.0 )
    -- ex.painter.rect( 100, 100, 200, 300 )

    -- ex.painter.color = ex.color4f( 1.0, 0.0, 0.0, 0.5 )
    -- ex.painter.rect4( 100, 100, 200, 300,
    --                   27, 14, 15, 14 )

    ex.painter.color = ex.color4f( 1.0, 0.0, 0.0, 1.0 )
    ex.painter.rect( 100, 100, 200, 300, 2 )
end

-- -- create window 2
-- local window2 = wiz.window( 400, 800 )
-- window2.background = { 0, 128, 255 }
-- window2.onRepaint = function ( self )
--     ex.painter.color = ex.color4f.white
--     ex.painter.bitmapText( "Hello World", font2, 10, 10 )

--     ex.painter.color = ex.color4f.green
--     ex.painter.bitmapText( "hello world", font3, 10, 50 )
-- end

window.onDestroy = function ( self )
    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end
