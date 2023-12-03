//===- Re2.hpp ------------------------------------------------------===//
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
//  This file includes the re2 library.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_RE2_HPP
#define AOC_UTILS_RE2_HPP

#include <re2/re2.h>
#include <absl/strings/string_view.h>
#include <aoc/Std.hpp>

namespace aoc::H {
  using Pattern = re2::RE2;
  using PatternRef = absl::string_view;

  ALWAYS_INLINE auto full_match(
   const re2::StringPiece& string, const Pattern& pattern, auto&...args) {
    return re2::RE2::FullMatch(string, pattern, &args...);
  }

  ALWAYS_INLINE auto partial_match(
   const re2::StringPiece& string, const Pattern& pattern, auto&...args) {
    return re2::RE2::PartialMatch(string, pattern, &args...);
  }

  ALWAYS_INLINE auto consume(
   re2::StringPiece& string, const Pattern& pattern, auto&...args) {
    return re2::RE2::Consume(&string, pattern, &args...);
  }

  ALWAYS_INLINE auto find_and_consume(
   re2::StringPiece& string, const Pattern& pattern, auto&...args) {
    return re2::RE2::FindAndConsume(&string, pattern, &args...);
  }
} // namespace aoc::H

#endif // AOC_UTILS_RE2_HPP