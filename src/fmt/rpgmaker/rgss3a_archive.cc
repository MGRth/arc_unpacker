// RGSS3A archive
//
// Company:   Enterbrain
// Engine:    Ruby Game Scripting System (RPG Maker XP)
// Extension: .rgss3a
//
// Known games:
// - ElEMENTS

#include "fmt/rpgmaker/rgs/common.h"
#include "fmt/rpgmaker/rgss3a_archive.h"
#include "util/range.h"

using namespace au;
using namespace au::fmt::rpgmaker;

static const std::string magic = "RGSSAD\x00\x03"_s;

static rgs::Table read_table(io::IO &arc_io, u32 key)
{
    rgs::Table table;

    while (arc_io.tell() < arc_io.size())
    {
        std::unique_ptr<rgs::TableEntry> entry(new rgs::TableEntry);
        entry->offset = arc_io.read_u32_le() ^ key;
        entry->size = arc_io.read_u32_le() ^ key;
        entry->key = arc_io.read_u32_le() ^ key;

        size_t name_length = arc_io.read_u32_le() ^ key;
        entry->name = arc_io.read(name_length);
        for (auto i : util::range(name_length))
            entry->name[i] ^= key >> (i << 3);

        if (!entry->offset)
            break;

        table.push_back(std::move(entry));
    }
    return table;
}

bool Rgss3aArchive::is_recognized_internal(File &arc_file) const
{
    return arc_file.io.read(magic.size()) == magic;
}

void Rgss3aArchive::unpack_internal(File &arc_file, FileSaver &file_saver) const
{
    arc_file.io.skip(magic.size());
    u32 key = arc_file.io.read_u32_le() * 9 + 3;
    auto table = read_table(arc_file.io, key);
    for (auto &entry : table)
        file_saver.save(rgs::read_file(arc_file.io, *entry));
}