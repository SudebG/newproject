#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

struct Note {
    string content;
    string timestamp;
};

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* timeinfo = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return string(buf);
}

class NoteApp {
private:
    vector<Note> notes;
    const string filename = "notes.txt";

public:
    NoteApp() {
        loadNotes();
    }

    void addNote() {
        string text;
        cout << "Enter your note: ";
        cin.ignore();
        getline(cin, text);
        if (text.empty()) {
            cout << "Note cannot be empty.\n";
            return;
        }
        Note note;
        note.content = text;
        note.timestamp = getCurrentTimestamp();
        notes.push_back(note);
        saveNotes();
        cout << "Note added on " << note.timestamp << "\n";
    }

    void viewNotes() {
        if (notes.empty()) {
            cout << "No notes found.\n";
            return;
        }
        for (size_t i = 0; i < notes.size(); ++i) {
            cout << "\n--- Note " << i + 1 << " ---\n";
            cout << "Date: " << notes[i].timestamp << "\n";
            cout << notes[i].content << "\n";
        }
    }

    void searchNotes() {
        if (notes.empty()) {
            cout << "No notes to search.\n";
            return;
        }
        string keyword;
        cout << "Enter keyword to search: ";
        cin.ignore();
        getline(cin, keyword);
        if (keyword.empty()) {
            cout << "Keyword cannot be empty.\n";
            return;
        }
        string lowerKeyword = keyword;
        transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

        cout << "\nSearch results for \"" << keyword << "\":\n";
        bool found = false;
        for (size_t i = 0; i < notes.size(); ++i) {
            string lowerContent = notes[i].content;
            transform(lowerContent.begin(), lowerContent.end(), lowerContent.begin(), ::tolower);
            string lowerTimestamp = notes[i].timestamp;
            transform(lowerTimestamp.begin(), lowerTimestamp.end(), lowerTimestamp.begin(), ::tolower);

            if (lowerContent.find(lowerKeyword) != string::npos ||
                lowerTimestamp.find(lowerKeyword) != string::npos) {
                cout << "\n--- Note " << i + 1 << " ---\n";
                cout << "Date: " << notes[i].timestamp << "\n";
                cout << notes[i].content << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No matching notes found.\n";
        }
    }

    void saveNotes() {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Could not save notes.\n";
            return;
        }
        for (const auto& note : notes) {
            file << note.timestamp << "\n";
            file << note.content << "\n";
            file << "---END---\n";
        }
    }

    void loadNotes() {
        ifstream file(filename);
        if (!file) return;
        string line;
        while (getline(file, line)) {
            Note note;
            note.timestamp = line;
            if (!getline(file, note.content)) break;
            notes.push_back(note);
            getline(file, line);
        }
    }
};

int main() {
    NoteApp myApp;
    int choice;
    do {
        cout << "\n===== Note Taking App =====\n";
        cout << "1. Add Note\n";
        cout << "2. View All Notes\n";
        cout << "3. Search Notes\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1) myApp.addNote();
        else if (choice == 2) myApp.viewNotes();
        else if (choice == 3) myApp.searchNotes();
    } while (choice != 4);
    cout << "Goodbye!\n";
    return 0;
}
