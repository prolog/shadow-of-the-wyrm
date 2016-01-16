#!/usr/bin/env python
import sys
from xml.dom import minidom

# Read the source strings from disk, exiting if no file was specified.
def get_res_strings():
  if (len(sys.argv) <= 1):
    print('No resource string file specified!')
    sys.exit()
  else:
    filename = sys.argv[1]
    print('Reading strings from ' + filename + '...')
    with open(filename, 'r') as res_str:
      return dict(line.split('=', 1) for line in res_str)

# Get a list of resource strings to check against the string table.
def get_strings_to_check(root):
  # At the moment, just check the spellbook strings.  Update this later as
  # needed.
  spellbooks_node = root.getElementsByTagName('ShadowOfTheWyrm')[0].getElementsByTagName('Items')[0].getElementsByTagName('Spellbooks')[0]
  return get_spellbook_strings(spellbooks_node)

# Get a list of all the spellbook strings that need to be checked.
def get_spellbook_strings(spellbooks_node):
  res_strs = []
  
  spellbook_nodes = spellbooks_node.getElementsByTagName('Spellbook')
  for spellbook_node in spellbook_nodes:
    # All spellbooks should have the first two
    desc_sid = spellbook_node.getElementsByTagName('DescriptionSID')[0].firstChild.nodeValue
    usage_sid = spellbook_node.getElementsByTagName('UsageDescriptionSID')[0].firstChild.nodeValue

    # Not all spellbooks will be unidentified - regular books, for example
    unid_desc = spellbook_node.getElementsByTagName('UnidentifiedDescriptionSID')

    res_strs.append(desc_sid)
    res_strs.append(usage_sid)

    if len(unid_desc) > 0:
      res_strs.append(unid_desc[0].firstChild.nodeValue)

    unid_usage = spellbook_node.getElementsByTagName('UnidentifiedUsageDescriptionSID')
    if len(unid_usage) > 0:
      res_strs.append(unid_usage[0].firstChild.nodeValue)

  return res_strs

def check_resource_strings(check_strs, res_strs):
  not_found = 0
  for check_str in check_strs:
    if not check_str in res_strs:
      print(check_str + ' was not found.')
      not_found = not_found + 1
  
  if not_found == 0:
    print('All monitored resource strings found!')


res_strs = get_res_strings()

# Read the configuration data.
root = minidom.parse('data/ShadowOfTheWyrm.xml')
check_strs = get_strings_to_check(root)

print('Checking resource strings...')
check_resource_strings(check_strs, res_strs)

