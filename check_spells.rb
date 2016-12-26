require 'nokogiri'

doc = Nokogiri::XML(File.open("data/ShadowOfTheWyrm.xml"))
doc.remove_namespaces!

# Get all the castable spells
spells = doc.xpath("ShadowOfTheWyrm/Creatures/Creature/Spells/Spell/SpellID")
not_found = []

# Find those that don't exist
spells.each do |sp|
  sp_id = sp.text
  
  if not doc.at_xpath("ShadowOfTheWyrm/Spells/Spell[@id = '" + sp_id + "']") then
    not_found.push(sp_id)
  end
end

puts("Total spells: #{spells.length()}")
puts("Number not found, IDs: #{not_found.length()}, #{not_found}")
