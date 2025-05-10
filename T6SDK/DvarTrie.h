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
        dvar_s* dvar{};

        DvarTrieNode() : isEndOfWord(false), dvar(nullptr) {}
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
            
            DvarTrieNode* current = root;
            std::string word = dvar->dvarName;
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            for (char ch : word)
            {
                if (current->children.find(ch) == current->children.end())
                {
                    current->children[ch] = new DvarTrieNode();
                }
                current = current->children[ch];
            }
            current->isEndOfWord = true;
            current->dvar = dvar;
        }

        std::vector<dvar_s*> searchByPrefix(const std::string& prefix)
        {
            std::vector<dvar_s*> result;
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

        void dfs(DvarTrieNode* node, std::string currentWord, std::vector<dvar_s*>& result)
        {
            if (node->isEndOfWord) 
            {
                result.push_back(node->dvar);
            }

            for (auto& pair : node->children) 
            {
                dfs(pair.second, currentWord + pair.first, result);
            }
        }
    };
}