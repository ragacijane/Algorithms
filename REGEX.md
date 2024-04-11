## Regular Expressions Cheat Sheet

### Literal Characters
- `a` Matches the character "a" exactly.
- `123` Matches the sequence of characters "123" exactly.

### Metacharacters
- `.` (dot) Matches any single character except newline `\n`.
- `^` Anchors the match to the start of the string.
- `$` Anchors the match to the end of the string.
- `|` Alternation, matches either the expression before or after the pipe.
- `[]` Character class, matches any one of the characters inside the square brackets.
- `()` Grouping, groups multiple tokens together and captures the matched text.
- `\` Escapes a metacharacter, allowing you to match it as a literal character.

### Quantifiers
- `*` Matches zero or more occurrences of the preceding character or group.
- `+` Matches one or more occurrences of the preceding character or group.
- `?` Matches zero or one occurrence of the preceding character or group.
- `{}` Specifies the exact number of occurrences or a range of occurrences.
  - `{n}` Exactly n occurrences.
  - `{n,}` At least n occurrences.
  - `{n,m}` Between n and m occurrences.

### Anchors
- `\b` Word boundary, matches a position where a word begins or ends.
- `\B` Non-word boundary, matches a position where a word does not begin or end.
- `\A` Matches only at the start of the string.
- `\Z` Matches only at the end of the string.

### Character Classes
- `\d` Matches any digit (equivalent to `[0-9]`).
- `\D` Matches any non-digit character (equivalent to `[^0-9]`).
- `\w` Matches any word character (alphanumeric character plus underscore, equivalent to `[a-zA-Z0-9_]`).
- `\W` Matches any non-word character (equivalent to `[^a-zA-Z0-9_]`).
- `\s` Matches any whitespace character (space, tab, newline).
- `\S` Matches any non-whitespace character.

### Modifiers
- `i` Case-insensitive matching.
- `m` Multi-line mode, changes behavior of `^` and `$` to match the start/end of each line.
- `g` Global 
