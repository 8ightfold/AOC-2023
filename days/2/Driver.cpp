#include <aoc/FileReader.hpp>
#include <aoc/Fmt.hpp>
#include <aoc/Re2.hpp>
#include <algorithm>

namespace H = aoc::H;

static H::PatternRef consume_prefix(aoc::StrRef str) {
  static re2::RE2 prefix("Game [0-9]+: ");
  H::PatternRef pstr {str};
  if(!H::consume(pstr, prefix)) UNLIKELY {
    return H::PatternRef();
  }
  return pstr;
}

namespace p1 {
  ALWAYS_INLINE bool validate_input(
   H::PatternRef name, int count) {
    if(name == "red") {
      return count <= 12;
    } else if(name == "green") {
      return count <= 13;
    } else if(name == "blue") {
      return count <= 14;
    } else {
      return false;
    }
  }

  bool validate_game(aoc::StrRef str) {
    static re2::RE2 game("([0-9]+) (\\w+)");
    H::PatternRef pstr = consume_prefix(str);
    if(pstr.empty()) UNLIKELY {
      return false;
    }

    H::PatternRef name;
    int count;
    while(H::consume(pstr, game, count, name)) {
      if(not validate_input(name, count)) UNLIKELY {
        return false;
      }
      pstr.remove_prefix(2);
    }

    return true;
  }
} // namespace p1

namespace p2 {
  struct Colors {
    Colors() = default;

    ALWAYS_INLINE void input(
     H::PatternRef name, int count) {
      if(name == "red") {
        this->r = std::max(r, count);
      } else if(name == "green") {
        this->g = std::max(g, count);
      } else if(name == "blue") {
        this->b = std::max(b, count);
      }
    }

    ALWAYS_INLINE std::int64_t power() CONST {
      using i64 = std::int64_t;
      return i64(r) * i64(g) * i64(b);
    }

  private:
    int r = 1, g = 1, b = 1;
  };

  int game_power_set(aoc::StrRef str) {
    static re2::RE2 game("([0-9]+) (\\w+)");
    H::PatternRef pstr = consume_prefix(str);
    if(pstr.empty()) UNLIKELY {
      return 0;
    }

    Colors cols { };
    H::PatternRef name;
    int count;
    while(H::consume(pstr, game, count, name)) {
      cols.input(name, count);
      pstr.remove_prefix(2);
    }

    return cols.power();
  }
} // namespace p2

namespace {
  int part_one(const aoc::StrSpans& lines) {
    int total = 0, current_game = 1;
    for(aoc::StrRef line : lines) {
      if(line.empty()) UNLIKELY { continue; }
      else if(p1::validate_game(line)) {
        total += current_game;
      }
      ++current_game;
    }
    fmt::println("part-one: {}", total);
    return 0;
  }

  int part_two(const aoc::StrSpans& lines) {
    std::int64_t total = 0;
    for(aoc::StrRef line : lines) {
      if(line.empty()) UNLIKELY { continue; }
      total += p2::game_power_set(line);
    }
    fmt::println("part-two: {}", total);
    return 0;
  }
} // namespace `anonymous`

int main(int argc, char* argv[]) {
  fmt::println("current-program: {}", 
    aoc::fs::path(argv[0])
      .filename().string());
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