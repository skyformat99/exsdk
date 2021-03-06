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

    -- relation
    parent = nil,
    renderNode = nil,
    style = nil, -- {} css-parsed style
})

--/////////////////////////////////////////////////////////////////////////////
-- class elementNode
--/////////////////////////////////////////////////////////////////////////////

wiz.elementNode = wiz.domNode.extend ({
    __typename = "elementNode",

    -- constructor & destructor
    __init = function ( self, tag, attrs )
        self.tag = tag
        self.attrs = attrs

        if attrs.id ~= nil then
            self.id = attrs.id
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    children = {},

    tag = "",
    id = "",
    attrs = nil, -- {}

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    generateRenderNodes = function ( self, parentRenderNode ) 
        if self.style.display == "inline" then
            self.renderNode = wiz.renderInline(self)
        else
            self.renderNode = wiz.renderBlock(self)
        end

        if parentRenderNode ~= nil then
            parentRenderNode:addChild(self.renderNode)
        end

        for i=1,#self.children do
            local node = self.children[i]
            node:generateRenderNodes(self.renderNode)
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    applyStyle = function ( self )
        -- create default style
        local style = self.style or wiz.style()

        -- process self
        local tag = self.tag
        if tag == "div" or tag == "window" then 
            style.display = "block"
        elseif tag == "a" then 
            style.display = "inline"
        elseif tag == "p" then 
            style.display = "block"
            style.marginTop = { type="legnth", value=16 }
            style.marginBottom = { type="legnth", value=16 }
        end

        -- process parent-tag
        local parentTag = self.parent.tag
        if parentTag == "hbox" then
            style.display = "block"
            style.whiteSpace = "nowrap"
        elseif parentTag == "vbox" then 
            style.display = "block"
            style.whiteSpace = "normal"
        end

        -- apply style
        local styleAttr = self.attrs.style
        if styleAttr ~= nil then
            style:parse(styleAttr)
        end
        self.style = style

        for i=1,#self.children do
            local node = self.children[i]
            node:applyStyle()
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    addChild = function ( self, node )
        node.parent = self
        table.add( self.children, node )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getElementByTag = function ( self, tag )
        for i=1,#self.children do
            local node = self.children[i]
            if node.tag == tag then
                return node
            end
        end
        return nil
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class textNode
--/////////////////////////////////////////////////////////////////////////////

wiz.textNode = wiz.domNode.extend ({
    __typename = "textNode",

    -- constructor & destructor
    __init = function ( self, text, isWhiteSpace )
        self.text = text
        self.isWhiteSpace = isWhiteSpace
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    isWhiteSpace = false,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    generateRenderNodes = function ( self, parentRenderNode ) 
        self.renderNode = wiz.renderText( self, self.text )

        if parentRenderNode ~= nil then
            parentRenderNode:addChild(self.renderNode)
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    applyStyle = function ( self )
    end,
})
