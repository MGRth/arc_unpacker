#include "fmt/nscripter/nsa_archive.h"
#include "test_support/archive_support.h"
#include "test_support/catch.hh"
#include "test_support/file_support.h"
#include "util/pack/zlib.h"

using namespace au;
using namespace au::fmt::nscripter;

TEST_CASE("Unpacking uncompressed NSA archives works")
{
    std::vector<std::shared_ptr<File>> expected_files
    {
        tests::stub_file("abc.txt", "123"_b),
        tests::stub_file("another.txt", "abcdefghij"_b),
    };

    NsaArchive archive;
    auto actual_files = tests::unpack_to_memory(
        "tests/fmt/nscripter/files/nsa/uncompressed.nsa", archive);

    tests::compare_files(expected_files, actual_files, true);
}

TEST_CASE("Unpacking NSA archives compressed with LZSS works")
{
    auto file = tests::stub_file(
        "test.bmp",
        util::pack::zlib_inflate(
            "\x78\xDA\x8D\xD3\x3D\x6E\x13\x40\x10\x86\xE1\xB5\x44\x81\x70\x9C"
            "\x38\xF1\x25\xA8\x53\x50\x20\x2A\x8A\xE9\xB8\xD4\x9C\x69\x6E\x40"
            "\x9D\x1B\xCC\x11\xF2\xE7\x38\xB4\x63\x1E\x82\xA0\xCE\x4A\x9F\x56"
            "\x7A\xB7\x79\x9A\xFD\xFE\xE3\xEB\x87\xF5\x76\xBE\xB8\x3F\xBB\x37"
            "\xFF\xF7\xF1\xAD\xFF\x79\x3E\x6C\xFF\xEE\xDF\xE3\xB7\xDB\x4F\xEB"
            "\xBD\x67\xBB\xDD\xAE\x8B\x8B\x8B\xB5\xDB\xED\xD6\xE5\xE5\xE5\xBA"
            "\xBA\xBA\x5A\xFB\xFD\x7E\x5D\x5F\x5F\xAF\x9B\x9B\x9B\x75\x38\x1C"
            "\xD6\x66\xB3\xB1\xB0\xB4\xB2\xB6\x59\x9B\xD0\x43\x0F\x3D\xF4\xD0"
            "\x43\x4F\x3D\xF5\xD4\x53\x4F\x3D\xF5\xD2\x4B\x2F\xBD\xF4\xD2\x4B"
            "\x6F\xBD\xF5\xD6\x5B\x6F\xBD\xF5\xD1\x47\x1F\x7D\xF4\xD1\x67\x56"
            "\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0"
            "\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04"
            "\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F\xF0\x04\x4F"
            "\xF0\x04\x4F\xF0\x04\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2"
            "\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24"
            "\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F"
            "\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF2\x24\x4F\xF1\x14\x4F\xF1"
            "\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14"
            "\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F"
            "\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1\x14\x4F\xF1"
            "\x14\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34"
            "\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F"
            "\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3\x34\x4F\xF3"
            "\x34\x4F\xF3\x34\x4F\xF3\x34\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C"
            "\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF"
            "\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0"
            "\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xF0\x0C\xCF\xFD\xFD"
            "\xFD\x7A\x78\x78\x58\x8F\x8F\x8F\xEB\xE9\xE9\x69\x3D\x3F\x3F\xAF"
            "\xE3\xF1\xB8\x5E\x5E\x5E\xD6\xE9\x74\x5A\xAF\xAF\xAF\xEB\x7C\x3E"
            "\xBF\xEB\x3F\xFF\xBC\xFB\xB5\xEE\xDC\xBF\x01\x89\x72\x8B\xEC"_b));
    std::vector<std::shared_ptr<File>> expected_files { file };

    NsaArchive archive;
    auto actual_files = tests::unpack_to_memory(
        "tests/fmt/nscripter/files/nsa/lzss.nsa", archive);

    tests::compare_files(expected_files, actual_files, true);
}
