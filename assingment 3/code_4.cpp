#include <iostream>
using namespace std;


struct node {
    int height;
    int index;
};


class max_heap {
public:
    node heap[100];// heap has been set with max elements == 100
    int size;

    max_heap() {
        size = 0;
    }

    void add(int height, int index) {
        node n = {height, index};
        int i = size++;
        while (i > 0 && heap[(i - 1) / 2].height < n.height) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = n;
    }

    void pop() {
        if (size == 0) return;
        node last = heap[--size];
        int i = 0;
        while (2 * i + 1 < size) {
            int child = 2 * i + 1;
            if (child + 1 < size && heap[child + 1].height > heap[child].height)
                child++;
            if (last.height >= heap[child].height) break;
            heap[i] = heap[child];
            i = child;
        }
        heap[i] = last;
    }

    node top() {
        return heap[0];
    }

    bool empty() {
        return size == 0;
    }
};

int main() {
    int heights[100], n, k;

    cout << "number of towers (n): ";
    cin >> n;

    cout << "enter " << n << " tower heights: ";
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    cout << "enter window size (k): ";
    cin >> k;

    max_heap mh;

    cout << "OUTPUT :\n";
    for (int i = 0; i < n; i++) {
        mh.add(heights[i], i);

        if (i >= k - 1) {
            // Remove elements out of the current window
            while (!mh.empty() && mh.top().index <= i - k) {
                mh.pop();
            }
            cout << mh.top().height << " ";
        }
    }

    cout << endl;
    return 0;
}

