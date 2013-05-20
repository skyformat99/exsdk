-- ======================================================================================
-- File         : test_css.lua
-- Author       : Wu Jie 
-- Last Change  : 05/20/2013 | 14:09:10 PM | Monday,May
-- Description  : 
-- ======================================================================================

return {

    background = { 1, 1, 1 },
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        local style = ui.css.build()
                            .margin("0px 0px 0px 10px")
                            -- .border("20px 10px")
                            -- .padding("auto")
                            .color("rgb( 255, 0, 0) ")
                            .done()

        -- local style = ui.css.build()
        --                     .font_size("20px")
        --                     .text_outline("1px #000")
        --                     .color("#0f0")
        --                     .margin("0px 0px 0px 10px")
        --                     .done()

        debug.dump(style)
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
    end
}
