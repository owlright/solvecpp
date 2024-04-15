#include "common.hpp"
#include <cassert>
#include <memory>
#include <unordered_map>

class LRUCache {
protected:
    struct Node {
        int key;
        int value;
        Node* prev { nullptr };
        Node* next { nullptr };

        Node(int k, int v) : key(k), value(v) { }
    };

    // ! moveToHead = removeNode + addToHead
    void moveToHead(Node* node)
    {
        assert(node != nullptr);
        if (node == head)
            return;
        removeNode(node);
        addToHead(node);
    }

    void removeNode(Node* node)
    {
        assert(node != nullptr);
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(Node* node)
    {
        assert(node != nullptr);
        // insert node between head and head->next
        node->next = head->next;
        node->prev = head;
        // unbound head and head->next
        head->next->prev = node;
        head->next = node; // ! head->next must be updated last
    }

private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;
        auto node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value)
    {
        if (cache.find(key) != cache.end()) {
            auto node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            if (cache.size() == capacity) {
                auto last = tail->prev;
                removeNode(last);
                cache.erase(last->key);
            }
            Node* newNode = new Node(key, value);
            addToHead(newNode);
            cache[key] = newNode;
        }
    }
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // returns 1
    cache.put(3, 3); // evicts key 2
    cout << cache.get(2) << endl; // returns -1 (not found)
    cache.put(4, 4); // evicts key 1
    cout << cache.get(1) << endl; // returns -1 (not found)
    cout << cache.get(3) << endl; // returns 3
    cout << cache.get(4) << endl; // returns 4
    return 0;
}