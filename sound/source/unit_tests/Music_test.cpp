#include "gtest/gtest.h"

Music create_testing_music();

Music create_testing_music()
{
	Song s("id1", TileType::TILE_TYPE_UNDEFINED, MapType::MAP_TYPE_NULL, "path/file");
	Song s2("", TileType::TILE_TYPE_UNDEFINED, MapType::MAP_TYPE_WORLD, "path/file2");
	Song s3("", TileType::TILE_TYPE_UNDEFINED, MapType::MAP_TYPE_OVERWORLD, "path/file3");
	Song s4("id2", TileType::TILE_TYPE_UNDEFINED, MapType::MAP_TYPE_NULL, "path/file4");
	Song s5("", TileType::TILE_TYPE_FIELD, MapType::MAP_TYPE_NULL, "path/file5");

	vector<Song> songs = { s, s2, s3, s4, s5 };
	Music m(songs);

	return m;
}

TEST(SW_Sound_Music, songs)
{
	Music m = create_testing_music();

	EXPECT_EQ("path/file", m.get_song("id1"));
	EXPECT_EQ("path/file2", m.get_song(MapType::MAP_TYPE_WORLD));
	EXPECT_EQ("path/file3", m.get_song(MapType::MAP_TYPE_OVERWORLD));
	EXPECT_EQ("path/file4", m.get_song("id2"));
	EXPECT_EQ("path/file5", m.get_song(TileType::TILE_TYPE_FIELD));
}

TEST(SW_Sound_Music, serialization_id)
{
	Music m;
	EXPECT_EQ(ClassIdentifier::CLASS_ID_MUSIC, m.get_class_identifier());
}

TEST(SW_Sound_Music, saveload)
{
	Music m = create_testing_music();
	Music m2;

	ostringstream ss;
	m.serialize(ss);
	istringstream iss(ss.str());

	m2.deserialize(iss);

	EXPECT_TRUE(m == m2);
}