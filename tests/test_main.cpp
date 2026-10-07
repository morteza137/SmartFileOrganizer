#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "CLI.h"
#include "FileInfo.h"
#include "Rule.h"

namespace fs = std::filesystem;

static int failures = 0;

#define CHECK(cond)                                                    \
    do                                                                 \
    {                                                                  \
        if (!(cond))                                                   \
        {                                                              \
            std::cerr << "FAIL " << __FILE__ << ":" << __LINE__        \
                      << ": " #cond "\n";                              \
            ++failures;                                                \
        }                                                              \
    } while (0)

static CLIOptions parseArgs(std::vector<std::string> args)
{
    std::vector<char*> argv;
    for (auto& a : args)
        argv.push_back(a.data());
    return CLI().parse(static_cast<int>(argv.size()), argv.data());
}

static void testCliParsing()
{
    auto o = parseArgs({"organizer", "some_dir", "--dry-run", "--recursive",
                        "--config", "my.json"});
    CHECK(o.directory == fs::path("some_dir"));
    CHECK(o.dryRun);
    CHECK(o.recursive);
    CHECK(o.configPath == fs::path("my.json"));

    auto d = parseArgs({"organizer", "dir"});
    CHECK(!d.dryRun && !d.recursive && !d.help);
    CHECK(d.configPath == fs::path("config.json"));

    CHECK(parseArgs({"organizer", "--help"}).help);

    bool threw = false;
    try { parseArgs({"organizer"}); } catch (const std::runtime_error&) { threw = true; }
    CHECK(threw);

    threw = false;
    try { parseArgs({"organizer", "a", "b"}); } catch (const std::runtime_error&) { threw = true; }
    CHECK(threw);

    threw = false;
    try { parseArgs({"organizer", "a", "--config"}); } catch (const std::runtime_error&) { threw = true; }
    CHECK(threw);
}

static void testRuleMatching()
{
    const fs::path dir = fs::temp_directory_path() / "sfo_test_rules";
    fs::create_directories(dir);
    const fs::path img = dir / "photo.jpg";
    const fs::path txt = dir / "notes.txt";
    std::ofstream(img) << "x";
    std::ofstream(txt) << "hello";

    FileInfo imgInfo{fs::directory_entry(img)};
    FileInfo txtInfo{fs::directory_entry(txt)};

    CHECK(imgInfo.getFilename() == "photo.jpg");
    CHECK(imgInfo.getExtension() == ".jpg");
    CHECK(txtInfo.getSize() == 5);

    Rule rule({".jpg", ".png"}, "Images");
    CHECK(rule.getDestination() == "Images");
    CHECK(rule.matches(imgInfo));
    CHECK(!rule.matches(txtInfo));

    fs::remove_all(dir);
}

int main()
{
    testCliParsing();
    testRuleMatching();

    if (failures == 0)
    {
        std::cout << "All tests passed\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed\n";
    return 1;
}
