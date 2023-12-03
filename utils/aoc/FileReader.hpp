//===- FileReader.hpp -----------------------------------------------===//
//
// Copyright (C) 2023 Eightfold
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
//     limitations under the License.
//
//===----------------------------------------------------------------===//
//
//  This file implements a function that opens a file and reads
//  its contents into a string handle.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_FILEREADER_HPP
#define AOC_UTILS_FILEREADER_HPP

#include <fstream>
#include <iterator>
#include <aoc/Std.hpp>

namespace aoc {
  BoxedStr read_file(Path filepath) {
    if(filepath.is_relative()) {
      filepath = (fs::current_path() / filepath);
    }
    std::ifstream is ( filepath, std::ios::binary );
    is.unsetf(std::ios::skipws);
    if(not is) return BoxedStr();

    std::streampos size;
    is.seekg(0, std::ios::end);
    size = is.tellg();
    is.seekg(0, std::ios::beg);

    Str file_data;
    std::istream_iterator<char> start(is), end;
    file_data.reserve(size);
    file_data.insert(file_data.cbegin(), start, end);
    return std::make_unique<Str>(std::move(file_data));
  }

  StrSpans split_file(const Str* data) {
    std::size_t pos = 0, off;
    StrSpans spans;
    if(not data) return spans;
    const char* under = data->data();
    // Supporting windows' stupid newlines
#  if defined(PLATFORM_WINDOWS)
    constexpr char search = '\r';
    constexpr char skip_n = 2;
#  else
    constexpr char search = '\n';
    constexpr char skip_n = 1;
#  endif

    while((off = data->find(search, pos)) != Str::npos) {
      const char* begin = under + pos;
      std::size_t distance = off - pos;
      spans.emplace_back(begin, distance);
      pos = off + skip_n;
    }
    spans.emplace_back(under + pos, data->size() - pos);
    return spans;
  }

  StrSpans split_file(Str& data) {
    return split_file(&data);
  }
} // namespace aoc

#endif // AOC_UTILS_FILEREADER_HPP