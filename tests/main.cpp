#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <Paths.h>

TEST_CASE("Test Paths")
{
	Paths paths("paths.txt");
	REQUIRE(paths.hasNext() == false);

	paths.begin();

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next() == "nghia");

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next() == "kata");

	REQUIRE(paths.hasNext() == true);
	REQUIRE(paths.next() == "tunix");

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
