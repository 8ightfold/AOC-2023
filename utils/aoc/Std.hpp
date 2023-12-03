//===- Std.hpp ------------------------------------------------------===//
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
//  This file provides aliases to relevant standard library objects.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_STD_HPP
#define AOC_UTILS_STD_HPP

#include <climits>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <efl/Config.hpp>

//=== Basic Definitions ===//
namespace aoc {
  namespace fs = std::filesystem;
  namespace conf = efl::config;

  template <typename T, 
    typename Deleter = std::default_delete<T>>
  using Box = std::unique_ptr<T, Deleter>;

  template <typename T>
  using Option = std::optional<T>;

  template <typename T,
    typename Allocator = std::allocator<T>>
  using Vec = std::vector<T, Allocator>;

  using Path = fs::path;
  using Str = std::string;
  using StrRef = std::string_view;

  using BoxedStr = Box<Str>;
  using StrSpans = Vec<StrRef>;
} // namespace aoc

//=== Basic Utilities ===//
namespace aoc {
  template <typename T>
  GLOBAL conf::H::inl_szt_ 
    bitsizeof = sizeof(T) * CHAR_BIT;
} // namespace aoc

namespace aoc {
  // TODO: Add unwrapping helpers
} // namespace aoc

#endif // AOC_UTILS_STD_HPP