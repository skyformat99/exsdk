-- ======================================================================================
-- File         : premake.lua
-- Author       : Wu Jie 
-- Last Change  : 01/05/2013 | 11:29:11 AM | Saturday,January
-- Description  : 
-- ======================================================================================

local __DEST_DIR = "_build/" .. _ACTION .. "/"
local __PLATFORM = _ARGS[1] or "macosx"

--/////////////////////////////////////////////////////////////////////////////
-- Solution: exSDK
--/////////////////////////////////////////////////////////////////////////////

solution "exSDK"

    configurations { "Debug", "Release" }
    location (__DEST_DIR)

    defines {
        -- allegro
        "ALLEGRO_STATICLINK",
        "ALLEGRO_LIB_BUILD",
        "ALLEGRO_SRC",

        -- lua
        "LUA_COMPAT_ALL",

        -- exsdk defines
        "EX_USE_DL_MALLOC",
        "EX_USE_MEMORY_MANAGER",
    }
    if __PLATFORM == "macosx" then
        defines {
            "MAC_OS_X_VERSION_MIN_REQUIRED=1060",
        }
    elseif __PLATFORM == "win32" then
        defines {
            "WIN32",
            "_WINDOWS",
            "_CRT_SECURE_NO_DEPRECATE", -- msvc treat sprintf, strcpy, ... functions as no safe, we don't want the compile keep warning us
        }
    end

    -- ======================================================== 
    -- Project: Allegro (library) 
    -- ======================================================== 

    project "Allegro"
        kind "StaticLib"
        language "C"
        targetname "allegro"

        -- build options
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            buildoptions { "/wd4996" }
        end

        -- include
        includedirs {
            "ext/allegro-5.0.8/include/",
        } 
        if __PLATFORM == "macosx" then
            includedirs {
                -- "/System/Library/Frameworks/AppKit.framework/Headers/", NOTE: in Mac, if we have include problem, uncomment this
            } 
        elseif __PLATFORM == "win32" then
            includedirs {
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include/",
            } 
        end

        -- source
        files { 
            "ext/allegro-5.0.8/src/**.c",
            "ext/allegro-5.0.8/addons/primitives/**.c",
            "ext/allegro-5.0.8/addons/main/**.c",
        }
        if __PLATFORM == "macosx" then
            files { 
                "ext/allegro-5.0.8/src/**.m",
                "ext/allegro-5.0.8/addons/main/**.m",
            }
        elseif __PLATFORM == "win32" then
        end

        -- source exclude
        excludes {
            "ext/allegro-5.0.8/src/optimized.c", -- We never use GP2XWIZ, so we never want this
        }
        if __PLATFORM == "macosx" then
            excludes {
                "ext/allegro-5.0.8/src/gp2xwiz/**",
                "ext/allegro-5.0.8/src/iphone/**",
                "ext/allegro-5.0.8/src/linux/**",
                -- "ext/allegro-5.0.8/src/macosx/**",
                -- "ext/allegro-5.0.8/src/unix/**",
                "ext/allegro-5.0.8/src/win/**",
                "ext/allegro-5.0.8/src/x/**",
            }
        elseif __PLATFORM == "win32" then
            excludes {
                "ext/allegro-5.0.8/src/gp2xwiz/**",
                "ext/allegro-5.0.8/src/iphone/**",
                "ext/allegro-5.0.8/src/linux/**",
                "ext/allegro-5.0.8/src/macosx/**",
                "ext/allegro-5.0.8/src/unix/**",
                -- "ext/allegro-5.0.8/src/win/**",
                "ext/allegro-5.0.8/src/x/**",
            }
        end

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "Allegro/debug/objs/" )
            targetdir ( __DEST_DIR .. "Allegro/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "Allegro/release/objs/" )
            targetdir ( __DEST_DIR .. "Allegro/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    
 
    -- ======================================================== 
    -- Project: exSDK
    -- ======================================================== 

    project "exSDK"
        kind "StaticLib"
        language "C"
        targetname "exsdk"

        -- include
        includedirs {
            "ext/allegro-5.0.8/include/",
            "ext/allegro-5.0.8/addons/primitives/",
            -- "ext/physfs-2.0.3/include/",
            "ext/lua-5.2.1/",
            "ext/luagl/",
            "ext/freetype-2.4.2-1/include/",
            "core/"
        } 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/glut/include/",
            }
        end

        -- source
        files { 
            -- "ext/physfs-2.0.3/**.c",
            "ext/lua-5.2.1/**.c",
            "ext/luagl-1.8/**.c",
            "core/**.c",
        }

        -- source exclude
        excludes {
            "ext/lua-5.2.1/lua.c",
            "ext/lua-5.2.1/luac.c",
        }

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "exSDK/debug/objs/" )
            targetdir ( __DEST_DIR .. "exSDK/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "exSDK/release/objs/" )
            targetdir ( __DEST_DIR .. "exSDK/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    

    -- ======================================================== 
    -- Project: exPlayer
    -- ======================================================== 

    project "exPlayer"
        kind "ConsoleApp"
        language "C"
        targetname "ex_player"

        -- include
        includedirs {
            "core/"
        } 

        -- source
        files { 
            "player/**.c",
        }

        -- library path ( for link to search ) 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            libdirs {
                -- "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86/",
                "ext/glut/lib/win32/",
                "ext/freetype-2.4.2-1/lib/win32",
            }
        end

        -- link
        links {
            "Allegro",
            "exSDK",
        }
        if __PLATFORM == "macosx" then
            links {
                "AppKit.framework/",
                "AudioToolbox.framework/",
                "IOKit.framework/",
                "OpenAL.framework/",
                "OpenGL.framework/",
                "AGL.framework/",
            }
        elseif __PLATFORM == "win32" then
            links {
                -- "d3d9",
                -- "d3dx9",
                -- "dinput8",
                -- "dsound",
                "winmm",
                "psapi",
                "shlwapi",
                "opengl32",
                "glu32",
                "glut32",
                "freetype",
            }
        end

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "ex/debug/objs/" )
            targetdir ( __DEST_DIR .. "ex/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "ex/release/objs/" )
            targetdir ( __DEST_DIR .. "ex/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }

    -- ======================================================== 
    -- TEST
    -- ======================================================== 

    matches = os.matchfiles("tests/*.c")
    for i=1,#matches do
        -- print ( path.getbasename(matches[i]) )
        local projectName = path.getbasename(matches[i]) 
        local destDir = __DEST_DIR .. projectName .. "/"

        project ( projectName )
            kind "ConsoleApp"
            language "C"
            targetname ( projectName )

            -- include
            includedirs {
                "ext/allegro-5.0.8/include/",
                "ext/allegro-5.0.8/addons/primitives/",
                "ext/lua-5.2.1/",
                "ext/luagl/",
                "core/"
            } 
            if __PLATFORM == "macosx" then
            elseif __PLATFORM == "win32" then
                includedirs {
                    "ext/glut/include/",
                }
            end

            -- source
            files { 
                matches[i],
            }

            -- library path ( for link to search ) 
            if __PLATFORM == "macosx" then
            elseif __PLATFORM == "win32" then
                libdirs {
                    "ext/glut/lib/win32/",
                }
            end

            -- link
            links {
                "Allegro",
                "exSDK",
            }
            if __PLATFORM == "macosx" then
                links {
                    "AppKit.framework/",
                    "AudioToolbox.framework/",
                    "IOKit.framework/",
                    "OpenAL.framework/",
                    "OpenGL.framework/",
                    "AGL.framework/",
                }
            elseif __PLATFORM == "win32" then
                links {
                    "winmm",
                    "psapi",
                    "shlwapi",
                    "opengl32",
                    "glu32",
                    "glut32",
                }
            end

            -- configurations
            configuration "Debug"
                objdir ( destDir .. "debug/objs/" )
                targetdir ( destDir .. "debug/bin/" )

                defines { "DEBUG" }
                flags { "Symbols" }

            configuration "Release"
                objdir ( destDir .. "release/objs/" )
                targetdir ( destDir .. "release/bin/" )

                defines { "NDEBUG" }
                flags { "Optimize" }
    end
    -- project "exPlayer"
