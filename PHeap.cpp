#include "PHeap.h"
#include <algorithm> // pentru std::min

PHeap& PHeap::operator=(PHeap&& rhs) noexcept {
	// TODO: insert return statement here
}

PHeap& PHeap::operator=(PHeap& rhs) {
	// TODO: insert return statement here
}

PHeap& PHeap::build(std::vector<int> vals) {
	PHeap* p = new PHeap();
	for (size_t i = vals.size() / 2; i >= 0; i--)
		PHeap::min_heapify(vals, i);

	return *p;
}

void PHeap::min_heapify(std::vector<int> vals, size_t index) {
	if ((2 * index) >= vals.size()) { // just to be extra safe
		return;
	}

	int m = std::min(vals[index], std::min(vals[2 * index], vals[2 * index + 1]));

	if (m == vals[index]) {
		return;
	}

	if (m == vals[2 * index]) {
		std::swap(vals[index], vals[2 * index]);
	}

	if ((2 * index + 1) >= vals.size() && m == vals[2 * index + 1]) {
		std::swap(vals[index], vals[2 * index + 1]);
	}
}

bool PHeap::insert(int val) {
	return false;
}

int PHeap::delete_val(int val) {
	return 0;
}

bool PHeap::delete_min() {
	return false;
}

PHeap& PHeap::merge(PHeap& ph1, PHeap& ph2) {
	// TODO: insert return statement here
}

void PHeap::execute(int op_code, int arg) {}
