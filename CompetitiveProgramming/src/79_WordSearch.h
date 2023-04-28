#ifndef __79_WORD_SEARCH_H__
#define __79_WORD_SEARCH_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <array>

#include "helper.h"

namespace nsCP
{
class Solution79
{
	struct Pos
	{
		int x{};
		int y{};

		Pos(int xx = 0, int yy = 0)
			: x(xx)
			, y(yy)
		{}
		inline bool operator==(const Pos& other) { return x == other.x && y == other.y; }
	};

	struct RecData
	{
		std::queue<Pos>		savedQueue;
		std::vector<bool>	savedVisited;
		Pos					posToPush{};
		int					wordId{};
	};

public:
	void test()
	{
		printf("Test : Solution79 -> Word Search In a Grid : START\n");
		std::vector<std::vector<std::vector<char>>> vecGrid(2);
		vecGrid[0] = std::vector<std::vector<char>>
					{
						{'A', 'B', 'C', 'E'},
						{'S', 'F', 'E', 'S'},
						{'A', 'D', 'E', 'E'}
					};
		vecGrid[1] = std::vector<std::vector<char>>{
			{'F', 'Y', 'C', 'E', 'N', 'R', 'D'},
			{'K', 'L', 'N', 'F', 'I', 'N', 'U'},
			{'A', 'A', 'A', 'R', 'A', 'H', 'R'},
			{'N', 'D', 'K', 'L', 'P', 'N', 'E'},
			{'A', 'L', 'A', 'N', 'S', 'A', 'P'},
			{'O', 'O', 'G', 'O', 'T', 'P', 'N'},
			{'H', 'P', 'O', 'L', 'A', 'N', 'O'}
		};

		std::vector<std::vector<std::string>> words;
		words.emplace_back(std::vector<std::string>{"CESEEEFS"});
		words.emplace_back(std::vector<std::string>{"FRANCE"});

		for (size_t i = 0; i < vecGrid.size(); ++i)
		{
			print(vecGrid[i], "Grid # " + std::to_string(i + 1));
			for (size_t j = 0; j < words[i].size(); ++j)
			{
				std::cout << "Searching for word : " << words[i][j];
				if (exist(vecGrid[i], words[i][j]))
				{
					std::cout << " -> FOUND\n";
				}
				else
				{
					std::cout << " -> NOT FOUND\n";
				}
			}
		}
		printf("Test : Solution79 -> Word Search In a Grid : END\n\n");
	}
private:
	bool exist(std::vector<std::vector<char>>& board, std::string word)
	{
		if (!board.size())
			return false;

		if (word.empty())
			return true;

		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[0].size(); ++j)
			{
				if (board[i][j] == word[0])
				{
					if (BFS(board, word, Pos(i, j)))
						return true;
				}
			}
		}

		return false;
	}

	bool BFS(std::vector<std::vector<char>> &board, std::string &word, const Pos &inpos)
	{
		std::stack<RecData> revisitStack;

		std::queue<Pos> que;
		que.push(inpos);

		std::vector<bool> visited(board.size() * board[0].size(), false);
		visited[getIndex(board, inpos)] = true;

		int i = 0;

		do
		{
			if (!revisitStack.empty())
			{
				RecData rec = revisitStack.top();

				que = rec.savedQueue;
				visited = rec.savedVisited;
				i = rec.wordId;
				que.pop();
				que.push(rec.posToPush);
				visited[getIndex(board, rec.posToPush)] = true;
				revisitStack.pop();
			}

			while (!que.empty())
			{
				Pos pos = que.front();
				que.pop();

				if (++i >= word.size())
					break;

				std::vector<bool> cpVisited = visited;

				Pos newPos;
				bool already = false;
				if (pos.x < board.size() - 1)
				{
					newPos.x = pos.x + 1;
					newPos.y = pos.y;
					if (board[newPos.x][newPos.y] == word[i] && !visited[getIndex(board, newPos)])
					{
						que.push(newPos);
						visited[getIndex(board, newPos)] = true;
						already = true;
					}
				}

				if (pos.x > 0)
				{
					newPos.x = pos.x - 1;
					newPos.y = pos.y;
					if (board[newPos.x][newPos.y] == word[i] && !visited[getIndex(board, newPos)])
					{
						if (already)
						{
							RecData rec;
							rec.savedQueue = que;
							rec.savedVisited = cpVisited;
							rec.wordId = i;
							rec.posToPush = newPos;

							revisitStack.push(rec);
						}
						else
						{
							que.push(newPos);
							visited[getIndex(board, newPos)] = true;
							already = true;
						}
					}
				}

				if (pos.y < board[0].size() - 1)
				{
					newPos.x = pos.x;
					newPos.y = pos.y + 1;
					if (board[newPos.x][newPos.y] == word[i] && !visited[getIndex(board, newPos)])
					{
						if (already)
						{
							RecData rec;
							rec.savedQueue = que;
							rec.savedVisited = cpVisited;
							rec.wordId = i;
							rec.posToPush = newPos;

							revisitStack.push(rec);
						}
						else
						{
							que.push(newPos);
							visited[getIndex(board, newPos)] = true;
							already = true;
						}
					}
				}

				if (pos.y > 0)
				{
					newPos.x = pos.x;
					newPos.y = pos.y - 1;
					if (board[newPos.x][newPos.y] == word[i] && !visited[getIndex(board, newPos)])
					{
						if (already)
						{
							RecData rec;
							rec.savedQueue = que;
							rec.savedVisited = cpVisited;
							rec.wordId = i;
							rec.posToPush = newPos;

							revisitStack.push(rec);
						}
						else
						{
							que.push(newPos);
							visited[getIndex(board, newPos)] = true;
						}
					}
				}
			}
			if (i >= word.size())
				return true;
		} while (!revisitStack.empty());

		return i >= word.size();
	}

	inline size_t getIndex(std::vector<std::vector<char>>& board, const Pos& pos)
	{
		return pos.x * board[0].size() + pos.y;
	}
};
}
#endif //#ifndef __79_WORD_SEARCH_H__