-- ======================================================================================
-- File         : textureImporter.lua
-- Author       : Wu Jie 
-- Last Change  : 12/09/2013 | 11:29:23 AM | Monday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

wiz.textureImporter = wiz.importer.extend ({
    __typename = "textureImporter",

    -- constructor & destructor
    __init = function ( self, bundle, path )
        super(self).__init( self, bundle, path )
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

    exec = function (self)
        local tex = ex.texture.new()
        local cptr = ex_c.texture_load ( self.bundle:osPath(self.path) )
        tex._cptr = cptr

        return tex
    end,
})
