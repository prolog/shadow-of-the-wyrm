#!lua
-- Additional include dir for Lua, if necessary.
--
-- If installed in your home directory, use an absolute path.  Issues have
-- been reported using e.g. ~/
newoption {
  trigger = "lua_include",
  value = "",
  description = "Specify an additional include directory for the Lua 5.1 includes."
}

-- What Lua should be linked against?
-- Default is "lua", but SotW requires Lua 5.1, and some distros will need
-- to use Lua 5.1 instead.
--
-- If installed in your home directory, use an absolute path.  Issues have
-- been reported using e.g. ~/
newoption {
  trigger = "lua_link",
  value = "lua",
  description = "Specify the Lua library to use for linking."
}

if not _OPTIONS["lua_link"] then
  _OPTIONS["lua_link"] = "lua"
end

-- What boost-thread should be linked against?
-- Default is "boost_thread", but MacOS apparently needs "boost_thread-mt".
newoption {
  trigger="boost_thread",
  value="boost_thread",
  description="Specify the boost_thread library to use for linking."
}

if not _OPTIONS["boost_thread"] then
  _OPTIONS["boost_thread"] = "boost_thread"
end

-- For the moment, there are two sets of build files: the Visual Studio files
-- themselves, and this premake4 file, which at the moment is only intended
-- to be used to create Unix makefiles.
-- 
-- To use, run "premake4 gmake", and then "make config=release".  Assuming you 
-- have the correct versions of all the libraries/headers installed, the game
-- and all supporting files will be found in the "sotw" folder.
solution "ShadowOfTheWyrm"
  configurations { "Debug", "CursesDebug", "Release", "CursesRelease" }

project "ShadowOfTheWyrm"
  kind "ConsoleApp"
  language "C++"
  files { "**.hpp", "**.cpp" }

  -- TODO: Once premake supports per-configuration exclude lists,
  -- create MapTester/SaveConverter configurations that exclude the appropriate
  -- files.
  excludes { "source/SaveConverter.cpp", "source/MapTester.cpp" }

  includedirs { "include",
                "controller/include",
                "display/include",
                "display/animation/include",
                "engine/include",
                "engine/actions/include",
                "engine/actions/read/include",
                "engine/calculators/include",
                "engine/combat/include",
                "engine/commands/include",
                "engine/commands/equipment/include",
                "engine/commands/help/include",
		"engine/commands/order/include",
                "engine/commands/inventory/include",
                "engine/commands/magic/include",
                "engine/commands/screens/include",
                "engine/commands/select_tile/include",
                "engine/commands/skills/include",
                "engine/conversion/include",
                "engine/creatures/include",
                "engine/decision_strategies/deity/include",
                "engine/decision_strategies/include",
                "engine/decision_strategies/magic/include",
                "engine/decision_strategies/search/include",
                "engine/description/include",
                "engine/description/codex/include",
                "engine/effects/include",
                "engine/field_of_view/include",
                "engine/generators/include",
                "engine/generators/crypts/include",
                "engine/generators/fortresses/include",
                "engine/generators/rooms/include",
                "engine/generators/settlements/include",
                "engine/generators/settlements/sector/include",
                "engine/generators/tile_config/include",
                "engine/generators/worship_sites/include",
                "engine/items/include",
                "engine/magic/include",
                "engine/maps/include",
                "engine/maps/tiles/include",
                "engine/maps/tiles/features/include",
                "engine/screens/include",
                "engine/scripting/include",
                "engine/skills/include",
                "engine/serialization/include",
                "engine/strings/include",
                "engine/time/include",
                "engine/translators/include",
                "engine/XML/include",
                "engine/XML/custom_maps/include",
                "engine/XML/custom_maps/features/include",
                "engine/XML/custom_maps/world/include",
                "world/include",
                "world/magic/include",
                "world/materials/include",
                "world/religion/include",
                "world/seasons/include",
                "world/tiles/include",
                "world/tiles/features/include",
                _OPTIONS["lua_include"]
                }
  excludes { "**_test.cpp" }
  links { "pthread", "dl", "z", "boost_system", "boost_filesystem", "boost_date_time", _OPTIONS["boost_thread"], "boost_regex", _OPTIONS["lua_link"], "xerces-c", "tinfo", "ncurses" }
  flags { "ExtraWarnings" }

  -- Ignore SaveConverter, MapTester configs.
  configuration "Debug"
    defines { "_DEBUG", "DEBUG", "UNIT_TESTS", "ENABLE_SDL" }
    flags { "Symbols" }
    links { "SDL2", "SDL2_image", "gtest" }
    excludes { "source/MapTester.cpp", "source/SaveConverter.cpp" }

  configuration "CursesDebug"
    defines { "_DEBUG", "DEBUG", "UNIT_TESTS" }
    flags { "Symbols" }
    links { "gtest" }
    excludes { "source/MapTester.cpp", "source/SaveConverter.cpp" }
  
  configuration "Release"
    defines { "NDEBUG", "ENABLE_SDL" }
    flags { "Optimize" }
    links { "SDL2", "SDL2_image" }
    postbuildcommands { "mkdir sotw",
                        "cp $(TARGETDIR)/ShadowOfTheWyrm sotw/sotw",
                        "cp -R data sotw",
			"cp -R assets sotw",
                        "mkdir sotw/docs",
                        "mkdir sotw/logs",
                        "cp docs/*.pdf sotw/docs",
                        "cp -R licenses sotw",
                        "cp -R scripts sotw",
                        "cp -R texts sotw",
                        "cp howdoi.txt sotw",
                        "cp *.ini sotw",
                        "cp README.md sotw",
                        "cp LICENSE sotw",
                        "tar cvzf ShadowOfTheWyrm-Linux.tar.gz sotw"}

  configuration "CursesRelease"
    defines { "NDEBUG" }
    flags { "Optimize" }
    postbuildcommands { "mkdir sotw",
                        "cp $(TARGETDIR)/ShadowOfTheWyrm sotw/sotw",
                        "cp -R data sotw",
			-- Assets ignored in this config 
                        "mkdir sotw/docs",
                        "mkdir sotw/logs",
                        "cp docs/*.pdf sotw/docs",
                        "cp -R licenses sotw",
                        "cp -R scripts sotw",
                        "cp -R texts sotw",
                        "cp howdoi.txt sotw",
                        "cp *.ini sotw",
                        "cp README.md sotw",
                        "cp LICENSE sotw",
                        "tar cvzf ShadowOfTheWyrm-Linux.tar.gz sotw"}

