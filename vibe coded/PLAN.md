# Note-Taking App — `vibe coded`

## Plan

**Location:** `newproject/vibe coded/`

**File:** `main.cpp` (single-file C++ app)

## Features

| # | Feature | Details |
|---|---------|---------|
| 1 | **Add Note** | Prompts for text, auto-stamps with `YYYY-MM-DD HH:MM:SS` |
| 2 | **View Notes** | Lists all notes with their timestamps |
| 3 | **Search Notes** | Case-insensitive keyword search across both content and date |
| 4 | **Persist** | Saves to `notes.txt` inside the `vibe coded` folder using `---END---` delimited format |

## Structure

```
newproject/vibe coded/
├── main.cpp    # source code
├── notes.exe   # compiled binary
├── notes.txt   # persisted notes data (auto-created)
└── PLAN.md     # this plan
```

## Compile & Run

```sh
cd "newproject/vibe coded"
g++ main.cpp -o notes.exe && .\notes.exe
```

## Menu Options

1. **Add Note** — enter text, gets timestamped automatically
2. **View All Notes** — display all saved notes with timestamps
3. **Search Notes** — case-insensitive search by keyword (matches content & date)
4. **Exit** — quits the app
