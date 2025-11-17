#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <string>
#include <vector>

bool write_bytes_to_file(const std::string &path, const unsigned char *data, size_t len);
bool read_bytes_from_file(const std::string &path, std::vector<unsigned char> &out);
#endif
