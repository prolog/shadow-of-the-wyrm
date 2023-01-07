#!/usr/bin/env/python

# Check the blank resource strings for any key not found in the English
# resource strings. The English strings should always be fully populated.

data = {'shadowofthewyrmtext_blank.ini': {}, 'shadowofthewyrmtext_en.ini' : {}}

for fname in data:
    with open(fname) as file:
        lines = file.readlines()

        # Split only once - the string value might have '=' in it.
        data[fname] = dict(line.strip().split('=', 1) for line in lines)

missing_keys = set(data['shadowofthewyrmtext_en.ini']) - set(data['shadowofthewyrmtext_blank.ini'])
extra_keys = set(data['shadowofthewyrmtext_blank.ini']) - set(data['shadowofthewyrmtext_en.ini'])

print("Strings in English but not Blank: ", missing_keys)
print("Extra strings in Blank that aren't in English: ", extra_keys)
