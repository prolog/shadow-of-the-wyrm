#!/usr/bin/env/python
#
# Creates a CSV with level info: area ID, min, max.
import os
from xml.dom import minidom

# Create the level range info data structure
def get_level_ranges(directory):
  areas = []

  # Check all the .xml files in the given directory.
  for fname in os.listdir(directory):
    if fname.endswith(".xml"):
      root = minidom.parse(directory + "/" + fname).getElementsByTagName("CustomMap")[0]
      level_range = root.getElementsByTagName("LevelRange")[0]

      if level_range:
        area_id = root.getAttribute("id")
        min_l = level_range.getElementsByTagName("Min")
        max_l = level_range.getElementsByTagName("Max")

        if min_l and max_l:
          areas.append([area_id, min_l[0].firstChild.nodeValue, max_l[0].firstChild.nodeValue])
  
  return areas

# Write out the level range info to file.
def write_level_ranges_to_csv(level_ranges, csv_file):
  csv = open(csv_file, "w")

  # Header
  csv.write("Area ID, Min, Max\n")

  # Contents
  for area in level_ranges:
    csv.write(area[0] + "," + area[1] + "," + area[2] + "\n")

  csv.close()

# Search all the .xml files in data/maps for level info
area_info = get_level_ranges("data/maps")
write_level_ranges_to_csv(area_info, "CustomMaps.csv")
