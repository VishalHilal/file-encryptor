#include "FileUtil.hpp"
#include <cstdio>
#include <vector>
#include <fstream>

bool write_bytes_to_file(const std::string &path, const unsigned char *data, size_t len) {
    FILE *f = fopen(path.c_str(), "wb");
    if (!f) return false;
    size_t wrote = fwrite(data, 1, len, f);
    fclose(f);
    return wrote == len;
}

bool read_bytes_from_file(const std::string &path, std::vector<unsigned char> &out) {
    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    if (!ifs) return false;
    auto size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    out.resize((size_t)size);
    ifs.read(reinterpret_cast<char*>(out.data()), size);
    return true;
}
