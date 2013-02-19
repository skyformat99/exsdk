-- ======================================================================================
-- File         : path.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 18:26:39 PM | Sunday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local sep = "/"
if os.platform == "windows" then
    sep = "\\"
end
__M.sep = sep

-- ------------------------------------------------------------------ 
-- Desc: 
-- example:
--      path.dirname("/foo/bar/baz/asdf/quux")
-- result:
--      /foo/bar/baz/asdf
-- ------------------------------------------------------------------ 

local function dirname (_p)
    local i = _p:findlast("/", true)
    if i then
        if i > 1 then i = i - 1 end
        return _p:sub(1, i)
    else
        return "."
    end
end
__M.dirname = dirname

-- ------------------------------------------------------------------ 
-- Desc: 
-- example:
--     path.extname("index.html")
-- result:
--     .html
--
-- example:
--     path.extname("index.")
-- result:
--     .
--
-- example:
--     path.extname("index")
-- result:
--     ""
-- ------------------------------------------------------------------ 

local function extname (_p) 
    local i = _p:findlast(".", true)
    if i then
        return _p:sub(i)
    else
        return ""
    end
end
__M.extname = extname

-- ------------------------------------------------------------------ 
-- Desc: 
-- example:
--      path.filename("/foo/bar/baz/asdf/quux.html")
-- result:
--      quux.html
-- ------------------------------------------------------------------ 

local function filename (_p)
    local i = _p:findlast("[/\\]")
    if i then
        return _p:sub(i + 1)
    else
        return _p
    end
end
__M.filename = filename

-- ------------------------------------------------------------------ 
-- Desc: filename without extension
-- example:
--      path.basename("/foo/bar/baz/asdf/quux.html")
-- result:
--      quux
-- ------------------------------------------------------------------ 

local function basename (_p) 
    local name = filename(_p)
    local i = name:findlast(".", true)
    if i then
        return name:sub(1,i-1)
    else
        return name
    end
end
__M.basename = basename

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function translate (_p, _sep)
    assert ( type(_p) == "string", "Type error: _p must be string" )

    if _sep == nil then
        if ex.platform == "windows" then
            _sep = "\\"
        else
            _sep = "/"
        end
    end
    return _p:gsub("[/\\]", _sep)
end
__M.translate = translate

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function join (_p1, _p2)
    _p1 = _p1 or ""

    if not _p2 then
        return _p1
    end

    local len = _p1:len()
    if len > 0 and not _p1:ncmp("/", len-1, 1) then
        _p1 = _p1 .. "/"
    end

    return _p1 .. _p2
end
__M.join = join

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function is ( _fname, _ext_list )
    local ext = extname(_fname)
    if type(_ext_list) == "string" then 
        return ext == _ext_list
    else
        return table.contains(_ext_list,ext)
    end
end
__M.is = is

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M

