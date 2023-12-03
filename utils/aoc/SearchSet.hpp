//===- StringUtils.hpp ----------------------------------------------===//
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
//  This file provides `SearchSet`, which can be used to quickly
//  search for a substring from a list.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_SEARCHSET_HPP
#define AOC_UTILS_SEARCHSET_HPP

#include <type_traits>
#include <aoc/StringUtils.hpp>
#include <aoc/Fmt.hpp>
#include <aoc/Re2.hpp>

namespace aoc {
namespace H {
  template <typename T>
  concept is_iterable = 
   requires(std::remove_cvref_t<T>& t) {
    std::begin(t);
    std::end(t);
  };

  ALWAYS_INLINE Pattern 
   gen_fpattern(const std::string& ucpattern) {
    return Pattern(fmt::format("^\\w*?({})\\w*", ucpattern));
  }

  ALWAYS_INLINE Pattern 
   gen_bpattern(const std::string& ucpattern) {
    return Pattern(fmt::format("\\w*({})\\w*$", ucpattern));
  }

  struct SearchSetBase {
    template <typename T>
    SearchSetBase(T&& t) {
      this->data = fmt::format("{}", 
        fmt::join(std::begin(t), std::end(t), "|"));
    }
    std::string data;
  };
} // namespace H

  /**
   * Super lazy implementation...
   * Might implement a PM-k search in the future.
   * Just uses RE2 for now.
   */
  struct SearchSet {
    SearchSet() = delete;

    template <typename T>
    SearchSet(T&& t)
     requires H::is_iterable<T> : base_(t), 
     fpattern_(H::gen_fpattern(base_.data)),
     bpattern_(H::gen_bpattern(base_.data)) { }

  public:
    StrRef find_front(StrRef str) const {
      return SearchSet::Locate(
        str, this->fpattern_);
    }

    StrRef find_back(StrRef str) const {
      return SearchSet::Locate(
        str, this->bpattern_);
    }

    static H::SRSizeType MatchOffset(
     StrRef str, StrRef pat) {
      if(!pat.empty()) LIKELY {
        return H::SRSizeType(
          pat.data() - str.data());
      } else UNLIKELY {
        return StrRef::npos;
      }
    }
  
  private:
    ALWAYS_INLINE static StrRef 
     Locate(StrRef str, const H::Pattern& pat) {
      H::PatternRef pstr;
      if(H::full_match(str, pat, pstr)) LIKELY {
        return { pstr.begin(), pstr.end() };
      } else UNLIKELY {
        return StrRef();
      }
    }
  
  private:
    H::SearchSetBase base_;
    H::Pattern fpattern_;
    H::Pattern bpattern_;
  };
} // namespace aoc

#endif // AOC_UTILS_SEARCHSET_HPP