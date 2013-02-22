-- ======================================================================================
-- File         : canvas.lua
-- Author       : Wu Jie 
-- Last Change  : 02/22/2013 | 16:18:16 PM | Friday,February
-- Description  : 
-- ======================================================================================

local __M = {}
local typename = ex.typename

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function draw_texture ( _pos, _texture )
    assert ( typename(_pos) == "vec2f", "Type error: _pos must be vec2f" )
    assert ( typename(_texture) == "texture", "Type error: _texture must be texture" )

    ex_c.canvas_draw_texture( _texture._cptr, _pos.x, _pos.y )
end
__M.draw_texture = draw_texture

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function draw_text ( _pos, _font, _content ) 
    assert ( typename(_pos) == "vec2f", "Type error: _pos must be vec2f" )
    assert ( typename(_font) == "bitmapfont", "Type error: _font must be bitmapfont" )
    assert ( type(_content) == "string", "Type error: _content must be string" )

    local cur_x, cur_y = _pos.x, _pos.y
    local ustr_ptr = ex_c.ustr_new(_content)
    local count = ex_c.ustr_length(ustr_ptr)-1

    for i=0,count do
        local id = ex_c.ustr_get(ustr_ptr,i)
        local charInfo = _font.charInfos[id]
        assert( charInfo, "Can't find char info by id " .. id )
        local page_texture = _font.pageInfos[charInfo.page]

        ex_c.canvas_draw_texture_region( page_texture._cptr, 
                                         cur_x, cur_y + charInfo.yoffset,
                                         charInfo.x,
                                         charInfo.y,
                                         charInfo.width,
                                         charInfo.height
                                         )
        cur_x = cur_x + charInfo.xadvance

        -- TODO { 
        -- if _font.haskerning then
        --     cur_x = cur_x
        -- end
        -- } TODO end 
    end
    ex_c.ustr_delete(ustr_ptr)
end
__M.draw_text = draw_text

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
