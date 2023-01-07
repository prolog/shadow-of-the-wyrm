#!/usr/bin/env/python

# Regenerate the blank resource strings file using the English strings.

with open('shadowofthewyrmtext_en.ini') as file:
    lines = file.readlines()
    res_strs = [k + '=' for k in dict(line.strip().split('=', 1) for line in lines)]

    with open ('shadowofthewyrmtext_blank.ini', 'w') as bl_file:
        for res_str in res_strs:
            bl_file.write("{}\n".format(res_str))


