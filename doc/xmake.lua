add_requires("doxygen")
target("doc")
  set_kind("phony")

  set_configdir("$(buildir)/doc")
  set_configvar("CONF_PROJECT_NAME", "Tiny STL")
  set_configvar("CONF_OUTPUT_DIR", "$(buildir)/doc")
  set_configvar("CONF_INPUT", "$(projectdir)/include $(projectdir)/src")
  add_configfiles("$(projectdir)/doc/Doxyfile.in", {filename = "Doxyfile"})

  on_run(function (target)
    cprint("${green}[INFO] ${clear}Generating doc ...")
    os.run("doxygen $(buildir)/doc/Doxyfile")
    cprintf("${green}[INFO] ${clear}Doc genearted ok! You can find doc in ${green}%s${clear}\n",
            "$(buildir)/doc/html/index.html")
  end)

  on_clean(function (target)
    if os.tryrm("$(buildir)/doc") then 
      cprint("${green}[INFO] ${clear}Doc cleaned ok!")
    end
  end)
target_end()