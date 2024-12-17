/**
 * Derek Hessinger
 * Prof. Ying Li
 * CS 333
 * 11/10/24
 * 
 * Counts the number of word occurences in a txt file
 * 
 * g++ -o wordcounter wordcounter.cpp
 * ./wordcounter (file)
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

// Function to clean a word (remove punctuation and convert to lowercase)
std::string clean_word(const std::string& word) {
    std::string cleaned;
    for (size_t i = 0; i < word.length(); i++) {
        if (std::isalpha(word[i])) {
            cleaned += std::tolower(word[i]);
        }
    }
    return cleaned;
}

// Structure to hold word and count for sorting
struct WordCount {
    std::string word;
    int count;
    
    WordCount(const std::string& w, int c) : word(w), count(c) {}
};

// Comparison function for sorting WordCount objects
bool compare_words(const WordCount& a, const WordCount& b) {
    if (a.count != b.count) {
        return a.count > b.count;  // Sort by count in descending order
    }
    return a.word < b.word;  // Sort alphabetically for same count
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    // Open the file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    // Use map to store word counts
    std::map<std::string, int> word_counts;
    std::string word;

    // Read and count words
    while (file >> word) {
        std::string cleaned = clean_word(word);
        if (!cleaned.empty()) {
            word_counts[cleaned]++;
        }
    }

    file.close();

    // Convert map to vector for sorting
    std::vector<WordCount> word_list;
    std::map<std::string, int>::const_iterator it;
    for (it = word_counts.begin(); it != word_counts.end(); ++it) {
        word_list.push_back(WordCount(it->first, it->second));
    }

    // Sort by frequency (and alphabetically for same frequency)
    std::sort(word_list.begin(), word_list.end(), compare_words);

    // Print top 20 words (or all if less than 20)
    size_t display_count = word_list.size() < 20 ? word_list.size() : 20;
    
    std::cout << "\nTop " << display_count << " most frequent words:\n";
    std::cout << "Rank  Count  Word\n";
    std::cout << "------------------------\n";
    
    for (size_t i = 0; i < display_count; i++) {
        std::cout << std::left << std::setw(5) << i + 1 
                  << std::setw(7) << word_list[i].count 
                  << word_list[i].word << std::endl;
    }

    std::cout << "------------------------\n";
    std::cout << "Total unique words: " << word_list.size() << std::endl;

    return 0;
}