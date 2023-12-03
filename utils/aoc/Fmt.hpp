//===- Fmt.hpp ------------------------------------------------------===//
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
//  This file includes the fmt library.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_FMT_HPP
#define AOC_UTILS_FMT_HPP

#include <fmt/format.h>

#define MAocFwdReturn(name, ...) \
 if(auto&& __v = name(__VA_ARGS__); aoc::H::check_return_code(__v)) \
 { fmt::println("[FATAL] {} returned `{}`.", #name, __v); return __v; }

namespace aoc::H {
  bool check_return_code(int i) {
    return i != 0;
  }

  bool check_return_code(auto&& v) {
    return static_cast<bool>(v);
  }
} // namespace aoc::H

#endif // AOC_UTILS_FMT_HPP