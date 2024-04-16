#include "common.hpp"
class LRUCache {
    struct Node {
        int key{-1};
        int value{-1};
        Node* prev { nullptr };
        Node* next { nullptr };
        Node() : key(-1),  value(-1) { }
        Node(int x, int y) : key(x),value(y) { }
    };

private:
    int capacity { -1 };
    Node* head { nullptr };
    Node* tail { nullptr };
    unordered_map<int, Node*> cache;

private:
    void removeNode(Node* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(Node* node)
    {
        // insert node between head and head->next
        node->next = head->next;
        node->prev = head;
        // unbound head and head->next
        head->next->prev = node;
        head->next = node; // ! head->next must be updated last
    }

    void moveToHead(Node* node) {
        if (node == head)
            return;
        removeNode(node);
        addToHead(node);
    }

public:
    LRUCache(int capacity) : capacity(capacity)
    {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        cache.reserve(capacity);
    }

    void put(int key, int value)
    {
        if (cache.find(key) != cache.end()) {
            auto node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            if (cache.size() == capacity)
            {
                // ! when deleing a node, its key must be known so that it can be deleted in cache
                auto last = tail->prev;
                removeNode(last);
                cache.erase(last->key);
                delete last;
                last = nullptr;
            }
            Node* newNode = new Node(key, value);
            addToHead(newNode);
            cache[key] = newNode;
        }
    }

    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;
        auto node = cache[key];
        moveToHead(node);
        return node->value;
    }
};

int main()
{
    auto lRUCache = LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    cout << lRUCache.get(1) << endl; // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << lRUCache.get(2) << endl; // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << lRUCache.get(1) << endl; // 返回 -1 (未找到)
    cout << lRUCache.get(3) << endl; // 返回 3
    cout << lRUCache.get(4) << endl; // 返回 4
}