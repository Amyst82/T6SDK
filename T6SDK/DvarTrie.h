#pragma once
#include "StdInclude.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>   
namespace T6SDK::Dvars
{

    class DvarTrieNode 
    {
    public:
        std::unordered_map<char, DvarTrieNode*> children;
        bool isEndOfWord = false;
        DevConsoleItem item{};

        DvarTrieNode() : isEndOfWord(false), item() {}
    };

    class DvarTrie 
    {
    public:
        DvarTrie() 
        {
            root = new DvarTrieNode();
        }

        void insert(const std::string& word) 
        {
            DvarTrieNode* current = root;
            for (char ch : word) {
                if (current->children.find(ch) == current->children.end()) 
                {
                    current->children[ch] = new DvarTrieNode();
                }
                current = current->children[ch];
            }
            current->isEndOfWord = true;
        }
        void insert(dvar_s* dvar)
        {        
            std::string word = dvar->dvarName;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            for (int i = 0; i < word.length(); i++)
            {
                DvarTrieNode* current = root;
                std::string currentWord = word.substr(i, word.length() - i);
                for (char ch : currentWord)
                {
                    if (current->children.find(ch) == current->children.end())
                    {
                        current->children[ch] = new DvarTrieNode();
                    }
                    current = current->children[ch];
                }
                current->isEndOfWord = true;
                current->item.dvar = dvar;
                current->item.isFunction = false;
            }
        }
        void insert(cmd_function_s* func)
        {       
            std::string word = func->name;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            for (int i = 0; i < word.length(); i++)
            {
                DvarTrieNode* current = root;
                std::string currentWord = word.substr(i, word.length() - i);
                for (char ch : currentWord)
                {
                    if (current->children.find(ch) == current->children.end())
                    {
                        current->children[ch] = new DvarTrieNode();
                    }
                    current = current->children[ch];
                }
                current->isEndOfWord = true;
                current->item.function = func;
                current->item.isFunction = true;
            }
        }

        std::vector<DevConsoleItem> searchByPrefix(const std::string& prefix)
        {
            std::vector<DevConsoleItem> result;
            DvarTrieNode* current = root;

            // Traverse to the end of the prefix
            for (char ch : prefix) 
            {
                if (current->children.find(ch) == current->children.end()) 
                {
                    return result; // Prefix not found
                }
                current = current->children[ch];
            }

            // Perform DFS to find all words with the given prefix
            dfs(current, prefix, result);
            return result;
        }

    private:
        DvarTrieNode* root;

        void dfs(DvarTrieNode* node, std::string currentWord, std::vector<DevConsoleItem>& result)
        {
            if (node->isEndOfWord) 
            {
                result.push_back(node->item);
            }

            for (auto& pair : node->children) 
            {
                dfs(pair.second, currentWord + pair.first, result);
            }
        }
    };
}