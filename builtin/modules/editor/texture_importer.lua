-- ======================================================================================
-- File         : texture_importer.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 17:33:43 PM | Monday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local texture_importer = editor.importer.extend ({
    __typename = "texture_importer",

    -- constructor & destructor
    __init = function ( _self, _path )
        assert ( type(_path) == "string", "Type error: _path must be path" )
        _self.path = _path
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    textureFormat = "ARGB32",
    writable = false,
    filterMode = "Bilinear",
    wrapMode = "Clamp",

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exec = function (_self)
        local tex = ex.texture.new()
        local cptr = ex_c.texture_load ( editor.asset_db.fullpath(_self.path) )
        tex:_setptr(cptr)

        return tex
    end,
})
__M.texture_importer = texture_importer

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
