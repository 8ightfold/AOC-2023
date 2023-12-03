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
//  This file provides some utilities for dealing with strings.
//
//===----------------------------------------------------------------===//

#pragma once

#ifndef AOC_UTILS_STRINGUTILS_HPP
#define AOC_UTILS_STRINGUTILS_HPP

#include <bitset>
#include <aoc/Std.hpp>

//=== StrRef Utilities ===//
namespace aoc {
namespace H {
  using SRSizeType = StrRef::size_type;
  using SRBitList = std::bitset<1 << CHAR_BIT>;

  ALWAYS_INLINE SRBitList 
   create_bitlist(StrRef list) {
    SRBitList list_bits;
    for(char c : list)
      list_bits.set((unsigned char)c);
    return list_bits;
  }

  template <bool IsInclusive>
  H::SRSizeType find_first_base(StrRef str, StrRef list) {
    auto list_bits = create_bitlist(list);
    SRSizeType len = str.size();
    for(H::SRSizeType idx = 0; idx < len; ++idx) {
      if(IsInclusive == list_bits.test((unsigned char)str[idx]))
        return idx;
    }
    return StrRef::npos;
  }

  template <bool IsInclusive>
  H::SRSizeType find_last_base(StrRef str, StrRef list) {
    auto list_bits = create_bitlist(list);
    SRSizeType len = str.size();
    for(H::SRSizeType idx = len - 1, e = ~0U; idx != e; --idx) {
      if(IsInclusive == list_bits.test((unsigned char)str[idx]))
        return idx;
    }
    return StrRef::npos;
  }
} // namespace H

  struct SRUtils {
  public:
    /// Finds the first character matching a given character.
    ALWAYS_INLINE static H::SRSizeType 
     FindFirstOf(StrRef str, char c) {
      return str.find_first_of(c);
    }

    /// Finds the first character NOT matching a given character.
    ALWAYS_INLINE static H::SRSizeType 
     FindFirstNotOf(StrRef str, char c) {
      return str.find_first_not_of(c);
    }

    /// Finds the last character matching a given character.
    ALWAYS_INLINE static H::SRSizeType
     FindLastOf(StrRef str, char c) {
      return str.find_last_of(c);
    }

    /// Finds the last character NOT matching a given character.
    ALWAYS_INLINE static H::SRSizeType
     FindLastNotOf(StrRef str, char c) {
      return str.find_last_not_of(c);
    }

    /// Finds the first character in a given list.
    ALWAYS_INLINE static H::SRSizeType
     FindFirstOf(StrRef str, StrRef list) {
      return H::find_first_base<true>(str, list);
    }

    /// Finds the first character NOT in a given list.
    ALWAYS_INLINE static H::SRSizeType
     FindFirstNotOf(StrRef str, StrRef list) {
      return H::find_first_base<false>(str, list);
    }

    /// Finds the last character in a given list.
    ALWAYS_INLINE static H::SRSizeType
     FindLastOf(StrRef str, StrRef list) {
      return H::find_last_base<true>(str, list);
    }

    /// Finds the last character NOT in a given list.
    ALWAYS_INLINE static H::SRSizeType
     FindLastNotOf(StrRef str, StrRef list) {
      return H::find_last_base<false>(str, list);
    }
  
  public:

  };
} // namespace aoc

#endif // AOC_UTILS_STRINGUTILS_HPP