-- ======================================================================================
-- File         : node.lua
-- Author       : Wu Jie 
-- Last Change  : 12/17/2013 | 15:16:32 PM | Tuesday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- class domNode
--/////////////////////////////////////////////////////////////////////////////

wiz.domNode = class ({
    __typename = "domNode",

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    parent = nil,
    children = {},

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    addChild = function ( _self, _node )
        _node.parent = _self
        table.add( _self.children, _node )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getElementByTag = function ( _self, _tag )
        for i=1,#_self.children do
            local node = _self.children[i]
            if node.tag == _tag then
                return node
            end
        end
        return nil
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class elementNode
--/////////////////////////////////////////////////////////////////////////////

wiz.elementNode = wiz.domNode.extend ({
    __typename = "elementNode",

    -- constructor & destructor
    __init = function ( _self, _tag, _attrs )
        _self.tag = _tag
        _self.attrs = _attrs

        if _attrs.id ~= nil then
            _self.id = _attrs.id
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    tag = "",
    id = "",
    attrs = {},
    style = {},
})

--/////////////////////////////////////////////////////////////////////////////
-- class textNode
--/////////////////////////////////////////////////////////////////////////////

wiz.textNode = wiz.domNode.extend ({
    __typename = "textNode",

    -- constructor & destructor
    __init = function ( _self, _text, _isWhiteSpace )
        _self.text = _text
        _self.isWhiteSpace = _isWhiteSpace or false
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    isWhiteSpace = false,
})