#pragma once
#include <vector>
#include "Node.h"

class PHeap
{
	Node* root = nullptr;

	PHeap(PHeap& p) = default;
	PHeap& operator=(PHeap& rhs) = default;
public:
	PHeap() = default;
	static PHeap& build(std::vector<int> vals);
	static void min_heapify(std::vector<int> vals, size_t index);
	PHeap& operator=(PHeap&& rhs);

	bool insert(int val);
	int delete_val(int val);
	bool delete_min();

	static PHeap& merge(PHeap& ph1, PHeap& ph2);

	static void execute(int op_code, int arg);

	friend class Node;
};

