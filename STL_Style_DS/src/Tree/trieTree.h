#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>

#include "Common/logger.h"
#include "Common/helper.h"

namespace nsCpp_DS {

struct TrieNode
{
	explicit TrieNode(const char alpha = '\0', const bool end = false)
		: m_char(alpha)
		, m_bEnd(end)
	{}

	~TrieNode() { removeAll(); }

	TrieNode(const TrieNode& other) { copyFrom(other); }
	TrieNode(TrieNode&& other) noexcept;

	TrieNode& operator=(const TrieNode&other);
	TrieNode& operator=(TrieNode&&other) noexcept;

	inline bool isLeaf() const { return m_vecNodes.empty(); }
	inline bool matchChar(const char& ch) const { return ch == m_char; }
	
	bool erase(const char &ch);

	friend std::ostream& operator<<(std::ostream& out, const TrieNode& node);
	friend std::ostream& operator<<(std::ostream& out, const TrieNode* node);

private:
	void copyFrom(const TrieNode& other);
	void removeAll();

public:
	char					m_char;
	bool					m_bEnd;		// It only represent if it's the last char of the word, even if it is, it doesn't mean its a leaf
	std::vector<TrieNode*>	m_vecNodes;
};

TrieNode::TrieNode(TrieNode&& other) noexcept
{
	m_char = std::exchange(other.m_char, '\0');
	m_bEnd = std::exchange(other.m_bEnd, false);
	m_vecNodes = std::exchange(other.m_vecNodes, std::vector<TrieNode*>());
}

TrieNode& TrieNode::operator=(const TrieNode& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

TrieNode& TrieNode::operator=(TrieNode&& other) noexcept
{
	if (this != &other)
	{
		m_char = std::exchange(other.m_char, '\0');
		m_bEnd = std::exchange(other.m_bEnd, false);
		m_vecNodes = std::exchange(other.m_vecNodes, std::vector<TrieNode*>());
	}
	return *this;
}

bool TrieNode::erase(const char& ch)
{
	std::vector<TrieNode*>::iterator it = std::find_if(m_vecNodes.begin(), m_vecNodes.end(),
		[&ch](TrieNode* node) -> bool { return node->matchChar(ch); });

	if (it != m_vecNodes.end())
	{
		m_vecNodes.erase(it);
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const TrieNode& node)	// TrieNode Friend Function
{
	out << node.m_char;
	if (node.m_bEnd)
	{
		out << '\n';
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const TrieNode* node)	// TrieNode Friend Function
{
	out << *node;
	return out;
}

void TrieNode::removeAll()
{
	std::for_each(m_vecNodes.begin(), m_vecNodes.end(), [](TrieNode*n) { delete n; });
	m_vecNodes.clear();
}

void TrieNode::copyFrom(const TrieNode& other)
{
	removeAll();
	m_vecNodes.resize(other.m_vecNodes.size());

	for (size_t i = 0, size = other.m_vecNodes.size(); i < size; ++i)
	{
		m_vecNodes[i] = new TrieNode(*other.m_vecNodes[i]);
	}
}




class Trie
{
public:
	Trie(const Trie&) = default;
	Trie& operator=(const Trie&) = default;

	Trie() = default;
	Trie(std::initializer_list<std::string> il);

	Trie(Trie &&other) noexcept;
	Trie& operator=(Trie &&other) noexcept;

	inline bool insert(std::string word);

	inline size_t size() const;
	
	inline size_t erase(std::string word, const bool delAllWithPref = false);		// Returns number of words deleted
			
	// Find methods
	inline bool find(std::string word) const;			// return if exact match found
	inline size_t count(std::string prefix) const;		// Returns count of word starting with the given prefix

	inline std::vector<std::string> getAllWordWithPrefix(std::string prefix) const;

	friend std::ostream& operator<<(std::ostream &out, const Trie &trie);

protected:
	// Helper Methods
	inline bool addWord(const std::string &word);
			
	inline std::vector<std::string> traverse(const TrieNode*node) const;

	inline void recurse(const TrieNode*inNode, std::string pref, std::vector<std::string> &vec, size_t &actualSize) const;

	inline std::vector<const TrieNode*> findWord(const std::string &prefix, size_t &pos) const;

	inline bool removeExact(std::vector<const TrieNode*> &vec);
	inline bool removeExact(std::string word);

	inline void convertToLower(std::string &word) const;
	inline void convertToUpper(std::string &word) const;

private:
	TrieNode		m_root;
	size_t			m_size{};	// Number of words
};

Trie::Trie(std::initializer_list<std::string> il)
{
	std::for_each(il.begin(), il.end(), [&](auto &word) {
		insert(word);
		});
}

bool Trie::insert(std::string word)
{
	convertToLower(word);
	return addWord(word);
}

Trie::Trie(Trie &&other) noexcept
{
	m_root = std::exchange(other.m_root, TrieNode());
	m_size = std::exchange(other.m_size, 0);
}

Trie& Trie::operator=(Trie &&other) noexcept
{
	if (this != &other)
	{
		m_root = std::exchange(other.m_root, TrieNode());
		m_size = std::exchange(other.m_size, 0);
	}
	return *this;
}

inline size_t Trie::size() const
{
	return m_size;
}

size_t Trie::erase(std::string word, bool delAllWithPref/* = false*/)
{
	convertToLower(word);
	// Count of word's deleted
	size_t retCount = 0;

	// If we have to delete the exact word
	if (!delAllWithPref)
	{
		if (removeExact(word))
		{
			retCount++;
		}
	}
	// Delete all with prefix
	else
	{
		std::vector<std::string> allWords = getAllWordWithPrefix(word);

		for (auto str : allWords)
		{
			if (removeExact(str))
			{
				retCount++;
			}
			else
			{
				assert(!"Error removing exact found word");
			}
		}
	}
	m_size -= retCount;
	m_root;
	return retCount;
}

bool Trie::find(std::string word) const
{
	convertToLower(word);
	size_t pos = 0;
	findWord(word, pos);
	if (pos == word.size())
	{
		return true;
	}
	return false;
}

size_t Trie::count(std::string prefix) const
{
	convertToLower(prefix);
	size_t pos = 0;
	const TrieNode* node = findWord(prefix, pos).back();
	return traverse(node).size();
}

std::vector<std::string> Trie::getAllWordWithPrefix(std::string prefix) const
{
	convertToLower(prefix);
	size_t pos = 0;
	const TrieNode* node = findWord(prefix, pos).back();
	if (!prefix.empty() && node == &m_root)
	{
		return {};
	}
	std::vector<std::string> res = traverse(node);
	for (auto& x : res)
	{
		x.insert(x.begin(), prefix.begin(), prefix.end());
	}
	return res;
}

bool Trie::addWord(const std::string& word)
{
	size_t pos = 0;

	TrieNode* node = const_cast<TrieNode*>(findWord(word, pos).back());

	// No need to check for (node == NULL), findWord should always return a valid node
	if (pos == word.size())
	{
		// This means word is already there
		if (!node->m_bEnd)
		{
			// if it is not the end word node, mark it as it now
			m_size++;
			node->m_bEnd = true;
			return true;
		}
		// As we have done nothing return false
		return false;
	}

	for (pos = pos; pos < word.size(); ++pos)
	{
		node->m_vecNodes.push_back(new TrieNode(word[pos]));
		node = node->m_vecNodes.back();
	}
	node->m_bEnd = true;
	m_size++;

	return true;
}

std::vector<std::string> Trie::traverse(const TrieNode* node) const
{
	std::vector<std::string> allWords;
	allWords.reserve(size());

	size_t actualSize = 0;
	recurse(node, "", allWords, actualSize);

	allWords.erase(allWords.begin() + actualSize, allWords.end());

	return allWords;
}

void Trie::recurse(const TrieNode* inNode, std::string pref, std::vector<std::string>& vec, size_t& actualSize) const
{
	for (size_t i = 0, size = inNode->m_vecNodes.size(); i < size; ++i)
	{
		TrieNode* node = inNode->m_vecNodes[i];
		pref.push_back(node->m_char);

		if (node->m_bEnd)
		{
			vec.push_back(pref);
			actualSize++;
		}
		recurse(node, pref, vec, actualSize);
		pref.pop_back();
	}
}

std::vector<const TrieNode*> Trie::findWord(const std::string& prefix, size_t& pos) const
{
	std::vector<const TrieNode*> vecNode;
	if (m_size == 0)
	{
		vecNode.push_back(&m_root);
		return vecNode;
	}

	size_t max = prefix.size();
	const TrieNode* p = &m_root;

	vecNode.push_back(p);

	std::vector<TrieNode*>::const_iterator it;
	for (size_t i = 0; i < max; ++i)
	{
		it = std::find_if(p->m_vecNodes.begin(), p->m_vecNodes.end(),
			[&i, &prefix](const TrieNode* node)
			{	return node->matchChar(prefix[i]);	}
		);

		if (it != p->m_vecNodes.end())
		{
			p = *it;
			pos++;
			vecNode.push_back(p);
		}
		else
		{
			break;
		}
	}
	return vecNode;
}

bool Trie::removeExact(std::vector<const TrieNode*>& vec)
{
	size_t i = vec.size() - 1;
	TrieNode* child = const_cast<TrieNode*>(vec[i]);
	//for (; i >= 0; --i)
	while (i--)
	{
		TrieNode* curr = const_cast<TrieNode*>(vec[i]);

		if (child->isLeaf())
		{
			curr->erase(child->m_char);
			if (curr->m_vecNodes.empty() && !curr->m_bEnd)
			{
				curr->m_bEnd = true;
			}
			else
			{
				return true;
			}
		}
		else if (child->m_bEnd)
		{
			child->m_bEnd = false;
			return true;
		}
		child = curr;
	}

	return false;
}

bool Trie::removeExact(std::string word)
{
	convertToLower(word);

	size_t pos = 0;
	std::vector<const TrieNode*> vec = findWord(word, pos);

	// vector will always have atleast one element, mRoot node.
	if (vec.size() == 1)
	{
		return false;
	}

	if (pos == word.size())
	{
		if (removeExact(vec))
		{
			return true;
		}
		else
		{
			assert(!"Error removing exact found word");
		}
	}
	return false;
}

void Trie::convertToLower(std::string& word) const
{
	std::transform(word.begin(), word.end(), word.begin(),
		[](char c) { return static_cast<char>(std::tolower(c)); });
}

void Trie::convertToUpper(std::string& word) const
{
	std::transform(word.begin(), word.end(), word.begin(),
		[](char c) { return static_cast<char>(std::toupper(c)); });
}

std::ostream& operator<<(std::ostream& out, const Trie& trie)	// Trie Friend Function
{
	const std::vector<std::string> allWords{ trie.traverse(&trie.m_root) };

	if (allWords.empty())
	{
		ns_Util::Logger::LOG_MSG("Trie is Empty\n");
	}
	else
	{
		ns_Util::Logger::LOG_MSG("*************************************\n");
		ns_Util::Logger::LOG_MSG("Total Number of words are :: ", allWords.size(), "\n\n");
		std::for_each(std::begin(allWords), std::end(allWords), [&out](const std::string &word) { ns_Util::Logger::LOG_MSG(word, '\n'); });
		ns_Util::Logger::LOG_MSG("*************************************\n");
	}
	return out;
}



// Testing code
std::pair<size_t, size_t> FillFromFile(const std::string& fileName, Trie& trie)
{
	std::ifstream inf{ fileName };
	// If we couldn't open the input file stream for reading
	if (!inf)
	{
		// Print an error and exit
		ns_Util::Logger::LOG_ERROR("File open error!\n");
		return {0, 0};
	}

	size_t totalReadWord = 0;
	size_t successFullInsertion = 0;

	// While there's still stuff left to read
	std::string strInput;
	while (inf)
	{
		// read stuff from the file into a string and print it
		std::getline(inf, strInput);
		totalReadWord++;
		successFullInsertion++;
		if (!trie.insert(strInput))
		{
			successFullInsertion--;
			ns_Util::Logger::LOG_ERROR("Already exists! :: ", strInput, '\n');
		}
	}
	return std::make_pair(totalReadWord, successFullInsertion);
}

std::pair<size_t, size_t> searchWordsInFile(const std::string& fileName, const Trie& trie)
{
	std::ifstream inf{ fileName };

	// If we couldn't open the input file stream for reading
	if (!inf)
	{
		// Print an error and exit
		ns_Util::Logger::LOG_ERROR("File open error!\n");
		return {0, 0};
	}

	size_t totalReadWord = 0;
	size_t successfullyFound = 0;

	// While there's still stuff left to read
	std::string strInput;
	while (inf)
	{
		// read stuff from the file into a string and print it
		std::getline(inf, strInput);
		totalReadWord++;
		successfullyFound++;
		if (!trie.find(strInput))
		{
			successfullyFound--;
			ns_Util::Logger::LOG_ERROR("Not Found :: ", strInput, '\n');
		}
	}

	ns_Util::Logger::LOG_MSG("Total Word Read From file are : ", totalReadWord, '\n');
	ns_Util::Logger::LOG_MSG("Successfully found words      : ", successfullyFound, '\n');
	return std::make_pair(totalReadWord, successfullyFound);
}

bool TrieTree_test_1()
{
	const char* testName = "Read word from file and construct Trie, then search all those words.";
	ns_Util::Logger::LOG_MSG("Executing Test 1 : ", testName, "\n\n");
	
	std::pair<size_t, size_t> res(0, 0);	// first = totalTestCount, second = passCount

	std::filesystem::path pwd = std::filesystem::current_path();
	std::string solutionName;
	for (std::filesystem::directory_iterator it(pwd), end; it != end; ++it)
	{
		if (it->path().extension() == ".sln")
		{
			solutionName = it->path().filename().generic_string();
			solutionName.erase(solutionName.size() - 4);
			break;
		}
	}
	solutionName.append("\\res\\Trie_Words.txt");
	pwd = pwd.parent_path();
	pwd.append(solutionName);

	const std::string fileToRead = pwd.string();
	
	res.first++;

	Trie trie;
	std::pair<size_t, size_t> p = FillFromFile(fileToRead, trie);
	ns_Util::Logger::LOG_MSG("Total Word Read From file are : ", p.first, '\n');
	ns_Util::Logger::LOG_MSG("Successfull insertion in Trie : ", p.second, '\n');
	ns_Util::Logger::LOG_MSG("Size of constructed Trie      : ", trie.size(), '\n');

	if (trie.size() == p.first && trie.size() == p.second)
	{
		res.second++;
	}
	
	res.first++;
	p = searchWordsInFile(fileToRead, trie);
	if (trie.size() == p.first && trie.size() == p.second)
	{
		res.second++;
	}

	ns_Util::Logger::LOG_RESULT(res.first, res.second, testName);
	ns_Util::Logger::LOG_MSG("\n\n");
	return res.first == res.second;
}

bool TrieTree_test_2()
{
	const char* testName = "Basic delete and getAllWordsWithPrefix() test.";
	ns_Util::Logger::LOG_MSG("Executing Test 2 : ", testName, "\n\n");

	std::pair<size_t, size_t> res(0, 0);	// first = totalTestCount, second = passCount

	Trie trie{ "to", "tea", "team", "teaming", "teamiz", "ted", "ten", "in", "inn", "india" };
	ns_Util::Logger::LOG_MSG(trie, '\n');

	res.first++;
	std::string prefix = "i";
	ns_Util::Logger::LOG_MSG("Searching for all word with prefix : ", prefix);

	auto allWords = trie.getAllWordWithPrefix("i");
	std::vector<std::string> expectedOutput{ "in", "inn", "india" };
	if (expectedOutput.size() == allWords.size())
	{
		res.second++;
	}
	
	ns_Util::Logger::LOG_MSG("\n");

	res.first++;
	if (expectedOutput == allWords)
	{
		res.second++;
	}

	res.first++;
	std::string wordToErase = "teaming";
	ns_Util::Logger::LOG_MSG("Searching  : ", wordToErase);
	if (trie.find(wordToErase))
	{
		res.second++;
	}

	res.first++;
	ns_Util::Logger::LOG_MSG("Erasing    : ", wordToErase, '\n');
	if (trie.erase(wordToErase) > 0 && !trie.find(wordToErase))
	{
		res.second++;
	}

	res.first++;
	ns_Util::Logger::LOG_MSG("Trie Size : ", trie.size(), "\n\n");
	expectedOutput = std::vector<std::string>{ "to", "tea", "team", "teamiz", "ted", "ten" };
	
	prefix = "t";
	ns_Util::Logger::LOG_MSG("Searching for all word with prefix : ( ", prefix, " )\n");
	allWords = trie.getAllWordWithPrefix(prefix);

	if (expectedOutput.size() == allWords.size())
	{
		res.second++;
	}

	res.first++;
	if (expectedOutput == allWords)
	{
		res.second++;
	}
	ns_Util::Logger::LOG_MSG("Erasing word with prefix : ( ", prefix, " )\n");
	size_t eraseCount = trie.erase("t", true);
	res.first++;
	if (eraseCount == expectedOutput.size())
	{
		res.second++;
	}

	res.first++;
	expectedOutput = { "in", "inn", "india" };
	if (trie.size() == expectedOutput.size())
	{
		res.second++;
	}

	res.first++;
	allWords.clear();
	for (char ch = 'a'; ch <= 'z'; ++ch)
	{
		auto tempVec = trie.getAllWordWithPrefix(std::string(1, ch));
		allWords.insert(allWords.end(), tempVec.begin(), tempVec.end());
	}
	if (allWords == expectedOutput)
	{
		res.second++;
	}

	ns_Util::Logger::LOG_RESULT(res.first, res.second, testName);
	ns_Util::Logger::LOG_MSG("\n\n");
	return res.first == res.second;
}

bool TrieTree_testAll(const size_t runTestCount = 1)
{
	LOG_ENTRY;
	const char* testName = "TrieTree_testAll :: ";
	for (size_t i = 1; i <= runTestCount; ++i)
	{
		ns_Util::Logger::LOG_MSG(testName, __LINE__, " : Test Counter : #", i, "\n\n");
		if (!TrieTree_test_1())
		{
			TEST_TYPE(" : TrieTree_test_1 : FAILED\n");
			return false;
		}
		if (!TrieTree_test_2())
		{
			TEST_TYPE(" : TrieTree_test_2 : FAILED\n");
			return false;
		}
	}
	TEST_TYPE(" : ALL TEST :: PASS\n\n\n");
	LOG_EXIT;
	ns_Util::Logger::LOG_MSG("#####################################\n");
	return true;
}
}	// namespace nsCpp_DS	
#endif //#define __TRIE_TREE_H__