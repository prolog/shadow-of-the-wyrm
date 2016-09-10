#!lua
lib_dir = "/usr/lib64/"
libs_to_copy = { "libxerces-c-3.1.so",
                 "libncurses.so.6",
                 "libboost_regex.so.1.60.0",
                 "libboost_thread.so.1.60.0",
                 "libboost_date_time.so.1.60.0",
                 "libboost_filesystem.so.1.60.0",
                 "libboost_system.so.1.60.0",
                 "libz.so.1",
                 "libdl.so.2" }

for i = 1, #libs_to_copy do
  lib_filename = lib_dir .. libs_to_copy[i]
  os.execute("cp " .. lib_filename .. " dist")
end
