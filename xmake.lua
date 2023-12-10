set_project("Tiny STL")

-- project settings
set_languages("c++17")
set_version("0.2.3", {build = "%Y%m%d%H%M", soname = true})
set_allowedmodes("debug", "fastest")
set_defaultmode("debug")

-- compile_commands.json
add_rules("plugin.compile_commands.autoupdate", {outputdir = "$(buildir)"})

-- if mode is debug, enable debug symbols
add_rules("mode.debug")

-- include header files
add_includedirs("include")

-- test target
includes("test")

-- doc target
includes("doc")