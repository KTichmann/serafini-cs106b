

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "stack.h"
#include "queue.h"
#include "lexicon.h"
#include "filelib.h"
#include "set.h"

using namespace std;
int getInput(Lexicon &dict, string &word1, string &word2);
Stack<string> findShortestLadder(Lexicon &dict, string word1, string word2);

int main() {
    // TODO: Finish the program!
    //get dictionary and input into a lexicon
    string userInput;
    while (!fileExists(userInput)){
        userInput = getLine("Dictionary filename please: ");
    };
    int response;
    Lexicon dict(userInput);
    while(true){
        string word1;
        string word2;
        response = getInput(dict, word1, word2);
        if(response == 1){
            cout << "Have a nice day." << endl;
            return 0;
        };
        Stack <string> ans = findShortestLadder(dict, word1, word2);
        cout << ans << endl;
    }
}

int getInput(Lexicon &dict, string &word1, string &word2){
    word1 = getLine("Word 1 (enter to quit): ");
    if(word1 == ""){
        return 1;
    }
    while(!dict.contains(word1)){
        word1 = getLine("Must be a word in the dictionary: ");
    };
    bool test = true;
    word2 = getLine("Word 2 (enter to quit): ");
    while(test){
        if(word2 == ""){
           return 1;
        } else if(!dict.contains(word2)){
            word2 = getLine("Must be a word in the dictionary: ");
        } else if(word1 == word2){
            word2 = getLine("Word 2 cannot be the same as word 1");
        } else if(word1.length() != word2.length()){
            word2 = getLine("Word 2 must be the same length as word 1");
        } else{
            test = false;
        }
    }
    word1 = toLowerCase(word1);
    word2 = toLowerCase(word2);
    return 0;
}

Stack<string> findShortestLadder(Lexicon &dict, string word1, string word2){
    Queue<Stack<string>> q;
    Stack<string> stk;
    stk.push(word1);
    q.enqueue(stk);
    Vector<char> alphabet = {'a', 'b', 'c', 'd','e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    Set<string> set;
    set.add(word1);
    while(!q.isEmpty()){
        Stack <string> newStack = q.dequeue();
        string word = newStack.peek();
        for(int i = 0; i < word.length(); i++){
            for(int j = 0; j < 26; j++){
               string newWord = word;
               newWord[i] = alphabet[j];
               if(dict.contains(newWord) && !set.contains(newWord)){
                   if(newWord == word2){
                       newStack.push(newWord);
                       return newStack;
                   } else{
                       Stack <string> saveStack = newStack;
                       saveStack.push(newWord);
                       q.enqueue(saveStack);
                       set.add(newWord);
                   }
               }
            }
        }
    }
    Stack<string> emptyStack;
    return emptyStack;
}
