# Smart File Organizer

A small C++17 command-line tool that sorts the files in a directory into
sub-folders based on file extension rules defined in a JSON config.

## Features

- Rule-based sorting by file extension
- `--dry-run` mode to preview moves without touching any files
- Optional recursive scanning
- Configurable rules via JSON

## Requirements

- A C++17 compiler (e.g. `g++` 9+)
- `make`
- [nlohmann/json](https://github.com/nlohmann/json) headers (`<nlohmann/json.hpp>`)
  - Debian/Ubuntu: `sudo apt install nlohmann-json3-dev`
  - macOS: `brew install nlohmann-json`
  - MSYS2: `pacman -S mingw-w64-x86_64-nlohmann-json`

## Build

```sh
make          # builds build/organizer
make test     # builds and runs build/tests
make clean    # removes build artifacts
```

If the JSON header is not on the default include path, pass it in:

```sh
make CXXFLAGS="-std=c++17 -O2 -I/path/to/json/include"
```

## Usage

```sh
organizer <directory> [options]
```

| Option            | Description                                 |
| ----------------- | ------------------------------------------- |
| `--help`          | Show help                                   |
| `--dry-run`       | Show operations without moving files        |
| `--recursive`     | Scan subdirectories recursively             |
| `--config <file>` | Configuration file (default: `config.json`) |

Example:

```sh
./build/organizer ~/Downloads --config configs/config.json --dry-run
```

## Configuration

Rules are checked in order and the first matching rule wins. Extensions must
include the leading dot and match case-sensitively. Destinations are relative
to the directory being organized.

```json
{
  "rules": [
    { "extensions": [".jpg", ".png"], "destination": "Images" },
    { "extensions": [".pdf", ".txt"], "destination": "Documents" }
  ]
}
```

A ready-to-use example lives in `configs/config.json`.

## Project layout

```
include/   headers
src/       implementation (main.cpp is the entry point)
tests/     unit tests (tests/test_main.cpp)
configs/   sample configuration
Makefile   build and test targets
```

Pipeline: `CLI` → `Organizer` → `Config` / `Scanner` → `Planner` → `Executor`.

## Tests

`make test` runs a dependency-free test binary covering CLI argument parsing,
`FileInfo`, and `Rule` matching.
