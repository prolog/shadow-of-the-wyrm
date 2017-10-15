#!/usr/bin/env python

# Create a file containing the artifacts' base ids.
from xml.dom import minidom

def get_artifacts_from_xml(xml_file):
  txt_artifacts = []

  # Elements that can contain the artifact tag.
  check_nodes = [["Amulets", "Amulet"],
                 ["Armours", "Armour"], 
                 ["Rings", "Ring"], 
                 ["Weapons", "Weapon"],
                 ["Tools", "Tool"]]

  root = minidom.parse(xml_file)

  items_node = root.getElementsByTagName("Items")[0]

  for cn_pair in check_nodes:
    item_type_node = items_node.getElementsByTagName(cn_pair[0])[0]
    item_instances_nodes = item_type_node.getElementsByTagName(cn_pair[1])

    print("Checking %s %s..." % (len(item_instances_nodes), cn_pair[0]))
    
    for inst_node in item_instances_nodes:
      artifact_nodes = inst_node.getElementsByTagName("Artifact")

      if len(artifact_nodes) > 0 and artifact_nodes[0].firstChild.nodeValue == "1":
        txt_artifacts.append(inst_node.getAttribute("id"))
  return txt_artifacts

def dump_artifacts(artifacts, txt_file):
  txt = open(txt_file, "w")

  # Write the values
  for artifact_id in sorted(artifacts):
    txt.write(artifact_id + '\n')

  txt.close()

artifacts = get_artifacts_from_xml("data/ShadowOfTheWyrm.xml")

print("Dumping %s artifact IDs..." % (len(artifacts)))

dump_artifacts(artifacts, "ShadowOfTheWyrm_Artifacts.txt")

