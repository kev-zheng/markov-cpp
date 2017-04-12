#include "csvstream.h"
#include <iostream>
#include <cstdlib> // exit
#include <map>
#include <set>
#include <ctime>

using namespace std;

class Generator {
public:
  Generator(string train_filename_in, int num_words_in)
  : num_words(num_words_in), train_filename(train_filename_in) {
    if(train_filename_in)

    try {
      csvstream csv_train(train_filename);
    } catch(csvstream_exception &e) {
      cout << "Error opening file: " << train_filename << endl;
      exit(EXIT_FAILURE);
    }
  }

  void train() {
    csvstream train_in(train_filename);
    csvstream::row_type post;

    while(train_in >> post) {
      istringstream source(post["content"]);
      string prev;
      source >> prev;
      sentence_starters.insert(prev);
      string word;
      while(source >> word) {
        ++vocabulary[prev].insert({word, 0}).first->second;
        prev = word;
      }
    }
  }

  void generate_message() {
    string word = next(vocabulary.begin(), rand() % vocabulary.size())->first;
    string message = "";
    for(int i = 0; i < num_words; ++i) {
      string next_word;
      if(vocabulary[word].size() == 0) {
        next_word = next(vocabulary.begin(), rand() % vocabulary.size())->first;
      }
      else {
        /*
        Code for maximum word in vocabulary
        int max = vocabulary[word].begin()->second;
        for(auto pair:vocabulary[word]) {
          if(pair.second > max) {
            max = pair.second;
            next_word = pair.first;
          }
        }
        */
        next_word = next(vocabulary[word].begin(), rand() % vocabulary[word].size())->first;
      }
      message = message + " " + next_word;
      word = next_word;
    }
    cout << message << endl;
  }

private:
  int num_words;
  string train_filename;
  map<string, map<string, int> > vocabulary;
  set<string> sentence_starters;

    template<typename T, typename T2>
  T random_word(const map<T, T2> &words) {
    return next(words.begin(), rand() % words.size())->first;
  }
};

int main(int argc, char *argv[]) {
  srand(time(NULL));

  if(argc != 3) {
    cout << "Error: not enough arguments" << endl;
    cout << "Usage: ./markov [filename] [num_words]" << endl;
    exit(EXIT_FAILURE);
  }

  Generator markov(argv[1], atoi(argv[2]));

  markov.train();

  markov.generate_message();

  return 0;
}
