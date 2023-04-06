//Dev Trivedi 21BCE2546
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

typedef struct Item {

	// Stores the weight of items
	float weight;

	// Stores the value of items
	int value;

	// Stores the index of items
	int idx;
} Item;

typedef struct Node {
	float ub;
	float lb;
	int level;
	bool flag;
	float tv;
	float tw;
} Node;

float upper_bound(float tv, float tw,
				int idx, vector<Item>& arr,int size,float capacity)
{
	float value = tv;
	float weight = tw;
	for (int i = idx; i < size; i++) {
		if (weight + arr[i].weight
			<= capacity) {
			weight += arr[i].weight;
			value -= arr[i].value;
		}
		else {
			value -= (float)(capacity
							- weight)
					/ arr[i].weight
					* arr[i].value;
			break;
		}
	}
	return value;
}

float lower_bound(float tv, float tw,
				int idx, vector<Item>& arr,int size,float capacity)
{
	float value = tv;
	float weight = tw;
	for (int i = idx; i < size; i++) {
		if (weight + arr[i].weight
			<= capacity) {
			weight += arr[i].weight;
			value -= arr[i].value;
		}
		else {
			break;
		}
	}
	return value;
}

class comp {
public:
	bool operator()(Node a, Node b)
	{
		return a.lb > b.lb;
	}
};

void assign(Node& a, float ub, float lb,
			int level, bool flag,
			float tv, float tw)
{
	a.ub = ub;
	a.lb = lb;
	a.level = level;
	a.flag = flag;
	a.tv = tv;
	a.tw = tw;
}
void bubble_sort(vector<Item>& items) {
    int n = items.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent items and swap if needed
            if (items[j].value/items[j].weight > items[j + 1].value/items[j + 1].weight) {
                swap(items[j], items[j + 1]);
            }
        }
    }
}

void knapsack(vector<Item>& arr,int size,float capacity)
{

	float min_lb = 0, final_lb = INT_MAX;

	bool curr_path[size], final_path[size];

	// Priority queue to store the nodes
	// based on lower bounds
	priority_queue<Node, vector<Node>,
				comp>
		pq;

	Node current, left, right;
	current.lb = current.ub = current.tw
		= current.tv = current.level
		= current.flag = 0;

	// Insert a dummy node
	pq.push(current);

	for (int i = 0; i < size; i++)
		curr_path[i] = final_path[i]
			= false;

	while (!pq.empty()) {
		current = pq.top();
		pq.pop();

		if (current.ub > min_lb
			|| current.ub >= final_lb) {

			
			continue;
		}

		// update the path
		if (current.level != 0)
			curr_path[current.level - 1]
				= current.flag;

		if (current.level == size) {
			// Reached last level
			if (current.lb < final_lb)
				for (int i = 0; i < size; i++)
					final_path[arr[i].idx]
						= curr_path[i];
			final_lb = min(current.lb, final_lb);
			continue;
		}

		int level = current.level;

		
		assign(right,
			upper_bound(current.tv,
						current.tw, level + 1,
						arr,size,capacity),
			lower_bound(current.tv, current.tw,
						level + 1, arr,size,capacity),
			level + 1, false,
			current.tv, current.tw);

		
		if (current.tw + arr[current.level].weight
			<= capacity) {

			
			left.ub
				= upper_bound(
					current.tv
						- arr[level].value,
					current.tw
						+ arr[level].weight,
					level + 1, arr,size,capacity);

			left.lb
				= lower_bound(
					current.tv
						- arr[level].value,
					current.tw
						+ arr[level].weight,
					level + 1, arr,size,capacity);

			assign(left, left.ub, left.lb,
				level + 1, true,
				current.tv - arr[level].value,
				current.tw
					+ arr[level].weight);
		}

		
		else {

			
			left.ub = left.lb = 1;
		}

		// Update the lower bound
		min_lb = min(min_lb, left.lb);
		min_lb = min(min_lb, right.lb);

		// Exploring nodes whose
		// upper bound is greater than
		// min_lb will never give
		// the optimal result

		if (min_lb >= left.ub)
			pq.push(left);
		if (min_lb >= right.ub)
			pq.push(right);
	}

	cout << "OPTIMAL SOLUTION"<<"\n";
	if (final_lb == INT_MAX)
		final_lb = 0;
	for (int i = 0; i < size; i++)
		cout << final_path[i] << " ";
	cout << "\n";
	cout << "MAX PROFIT : "
		<< (-final_lb) << "\n";
}

// Driver Code
int main()
{
	int size = 4;

	float capacity = 15;
	vector<Item> arr;
	arr.push_back({ 2, 10, 0 });
	arr.push_back({ 4, 10, 1 });
	arr.push_back({ 6, 12, 2 });
	arr.push_back({ 9, 18, 3 });
    
    bubble_sort(arr);
	knapsack(arr,size,capacity);
    return 0;
}
