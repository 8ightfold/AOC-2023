#include <aoc/FileReader.hpp>
#include <aoc/Fmt.hpp>
#include <aoc/SearchSet.hpp>

using IntPair = std::pair<int, int>;

namespace p1 {
  IntPair get_cursor_pair(aoc::StrRef str) {
    using namespace aoc;
    static constexpr StrRef digits = "0123456789";
    auto front = SRUtils::FindFirstOf(str, digits);
    auto back = SRUtils::FindLastOf(str, digits);
    if(front == StrRef::npos || back == StrRef::npos) UNLIKELY {
      return { -1, -1 };
    } else LIKELY {
      return { int(front), int(back) };
    }
  }

  ALWAYS_INLINE int get_pair_value(aoc::StrRef str) {
    auto [f, b] = get_cursor_pair(str);
    if(f == -1) UNLIKELY {
      return 0;
    } else LIKELY {
      int v = int(str[b] - '0');
      v += int(str[f] - '0') * 10;
      return v;
    }
  }
} // namespace p1

namespace p2 {
  aoc::SearchSet gen_searchset() {
    using SRIL = std::initializer_list<aoc::StrRef>;
    return aoc::SearchSet(SRIL { 
      "one", "two", "three", 
      "four", "five", "six", 
      "seven", "eight", "nine"
    });
  }

  /**
   * Assumes the inputs are either valid
   * or empty, don't pass random strings :P
   */
  int resolve_size(aoc::StrRef s) {
    if(s.empty()) UNLIKELY { return -1; }
    switch (s[0]) {
     case 't': {
      if(s[1] == 'w') return 2;
      else return 3;
     }
     case 'f': {
      if(s[1] == 'o') return 4;
      else return 5;
     }
     case 's': {
      if(s[1] == 'i') return 6;
      else return 7;
     }
     case 'o': return 1;
     case 'e': return 8;
     case 'n': return 9;
     default: return -1;
    }
  }

  ALWAYS_INLINE int resolve_cursor(
   aoc::StrRef str, int loc) {
    if(loc >= 0) LIKELY {
      return int(str[loc] - '0');
    } else UNLIKELY {
      return -1;
    }
  }

  IntPair get_size_pair(aoc::StrRef str) {
    using aoc::SearchSet;
    static SearchSet sset = gen_searchset();
    auto [f, b] = ::p1::get_cursor_pair(str);
    if(f == -1) UNLIKELY {
      return { -1, -1 };
    }

    auto front = sset.find_front(str);
    auto back = sset.find_back(str);
    int ifront = 0, iback = 0;

    if(auto off = SearchSet::MatchOffset(str, front);
     off != aoc::StrRef::npos && off < f)
      ifront = resolve_size(front);
    else ifront = resolve_cursor(str, f);

    if(auto off = SearchSet::MatchOffset(str, back);
     off != aoc::StrRef::npos && off > b)
      iback = resolve_size(back);
    else iback = resolve_cursor(str, b);
    
    return { ifront, iback };
  }

  ALWAYS_INLINE int get_pair_value(aoc::StrRef str) {
    auto [f, b] = get_size_pair(str);
    if(f == -1 || b == -1) UNLIKELY {
      return 0;
    } else LIKELY {
      return (f * 10) + b;
    }
  }
} // namespace p2

namespace {
  int part_one(const aoc::StrSpans& lines) {
    int total = 0;
    for(aoc::StrRef line : lines) {
      if(line.empty()) UNLIKELY { continue; }
      total += p1::get_pair_value(line);
    }
    fmt::println("part-one: {}", total);
    return 0;
  }

  int part_two(const aoc::StrSpans& lines) {
    int total = 0;
    for(aoc::StrRef line : lines) {
      if(line.empty()) UNLIKELY { continue; }
      total += p2::get_pair_value(line);
    }
    fmt::println("part-two: {}", total);
    return 0;
  }
} // namespace `anonymous`

int main() {
  aoc::BoxedStr input = 
    aoc::read_file("input.txt");
  if(!input) {
    fmt::println("[FATAL] `input.txt` could not be opened.");
    return 1;
  }
  aoc::StrSpans lines = 
    aoc::split_file(*input);
  MAocFwdReturn(part_one, lines);
  MAocFwdReturn(part_two, lines);
}