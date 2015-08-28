#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <Paths.h>
#include <Path.h>
#include <System.h>

TEST_CASE("Test Paths: File")
{
	Paths paths(Path("C:\\log.txt"));

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next().value() == "C:\\log.txt");
	REQUIRE(paths.hasNext() == false);
}

TEST_CASE("Test Paths: Folder")
{
	Paths paths(Path("C:\\test"));

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next().value() == "1.txt");

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next().value() == "2.txt");

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next().value() == "3.txt");

	REQUIRE(paths.hasNext() == false);
}

#include <Process.h>

TEST_CASE("Test Process Error")
{
	Process process("y:\\etcpack\\etcpack.exe");
	int exitCode = process.execute();
	REQUIRE(exitCode == 1);
}

TEST_CASE("Test Process Success")
{
	Process process("y:\\etcpack\\etcpack.exe -version");
	int exitCode = process.execute();
	REQUIRE(exitCode == 0);
}

TEST_CASE("Test Path: fileNameWithoutExt")
{
	Path p("alp_atlas_asphalt_snow_02_df.tga");
	REQUIRE(p.fileNameWithoutExt() == "alp_atlas_asphalt_snow_02_df");
}

TEST_CASE("Test Path Is Folder")
{
	Path p("Y:\\etcpack");
	REQUIRE(p.isFolder());
}

TEST_CASE("Test Path Is File")
{
	Path p("Y:\\etcpack\\etcpack.exe");
	REQUIRE(!p.isFolder());
}


TEST_CASE("Test System")
{
	REQUIRE(System::currentFolder() != "");
}
