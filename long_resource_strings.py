#!/usr/bin/env python
import sys

# Find all resource strings longer than 160 characters from the
# specified file, printing the resource strings to standard out.
def get_res_strings():
  if (len(sys.argv) <= 1):
    print("Resource string file: no filename specified.")
    sys.exit()
  else:
    filename = sys.argv[1]
    with open(filename, "r") as res_str:
      return dict(line.split("=", 1) for line in res_str)

res_strs = get_res_strings()
sorted_res_strs = {k : v for (k, v) in res_strs.items() if len(v) > 750}

print("Candidates for external files (> 750 characters).")
print("Leave creature descriptions as-is.")
print("Externalize books or anything with complex formatting.")

for (k, v) in sorted_res_strs.items():
  print(k)


