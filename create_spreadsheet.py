#!/usr/bin/env python

# Create a CSV file containing the creature data.  The CSV file will
# contain a header line, followed by the creature data from
# the SavageLands.xml configuration file.  This is useful for quickly
# checking whether a given symbol/colour combination has already been
# assigned to a particular creature.

from xml.dom import minidom

# Get the creature data from the XML file.  A dictionary is returned,
# keyed by a tuple of (creature_symbol, creature_colour).  The value is
# the creature_id attribute.
def get_creatures_from_xml(xml_file):
  # The creature values that will be written to the CSV file.
  ss_creatures = {}

  root = minidom.parse(xml_file)

  creatures_nodes = root.getElementsByTagName('Creatures')

  for creatures in creatures_nodes:
    creature_nodes = creatures.getElementsByTagName('Creature')

    for creature in creature_nodes:
      creature_id = creature.attributes['id'].value

      # Get the symbol and colour
      text_node = creature.getElementsByTagName('Text')[0]
      symbol_node = text_node.getElementsByTagName('Symbol')[0]
      colour_node = text_node.getElementsByTagName('Colour')[0]
      danger_level_node = creature.getElementsByTagName('DangerLevel')[0]

      creature_symbol = symbol_node.childNodes[0].nodeValue
      creature_colour = colour_node.childNodes[0].nodeValue
      creature_level  = danger_level_node.childNodes[0].nodeValue

      creature_tuple = (creature_symbol, creature_colour, creature_level)

      # If there's already a creature tuple of the given symbol/colour,
      # add the current creature ID to the existing one.
      if creature_tuple in ss_creatures:
        existing_id = ss_creatures[creature_tuple]
        print("Duplicate creature symbol/colour detected - new ID: " + creature_id + ", existing: " + existing_id)
        creature_id = creature_id + "," + existing_id
      
      ss_creatures[creature_tuple] = creature_id

  return ss_creatures

# Write the creature data to the CSV file.
def write_creatures_to_csv(creatures, csv_file):
  csv = open(csv_file, 'w')

  # Write the header
  csv.write('Symbol, Colour, Creature, Level \n')

  # Write the values
  for sc_pair in sorted(creatures):
    line = sc_pair[0] + ',' + sc_pair[1] + ',' + creatures[sc_pair] + ',' + sc_pair[2] + '\n'
    csv.write(line)

  csv.close()

# Get the creatures from the XML configuration file, and write them to
# a CSV file, pre-sorted by symbol and colour
creatures = get_creatures_from_xml('data/SavageLands.xml')
write_creatures_to_csv(creatures, 'SavageLands.csv')
