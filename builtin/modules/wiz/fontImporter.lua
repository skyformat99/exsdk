-- ======================================================================================
-- File         : fontImporter.lua
-- Author       : Wu Jie 
-- Last Change  : 12/09/2013 | 11:28:34 AM | Monday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

wiz.fontImporter = wiz.importer.extend ({
    __typename = "fontImporter",

    -- constructor & destructor
    __init = function ( _self, _path )
        checkarg(_path,"string")

        _self.path = _path
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    size = 16,

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exec = function (_self)
        local fnt = ex.font.new()
        local cptr = ex_c.font_load ( wiz.fsysPath(_self.path), _self.size )
        fnt._cptr = cptr

        return fnt
    end,
})