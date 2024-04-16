#include "common.hpp"
ListNode* reverse(ListNode* prev, ListNode* curr)
{
    if (curr == nullptr) {
        return prev;
    }
    ListNode* tmp = curr->next;
    curr->next = prev;
    return reverse(curr, tmp);
}
ListNode* reverseList(ListNode* head) { return reverse(nullptr, head); }

ListNode* reverseList2(ListNode* head)
{
    ListNode *pre, *cur, *tmp;
    pre = tmp = nullptr;
    cur = head;
    while (cur) {
        tmp = cur->next; // store the third node
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}

ListNode* reverseBetween(ListNode* head, int left, int right)
{
    ListNode *dummyHead, *startPre, *tail, *start, *tmp;
    dummyHead = startPre = new ListNode(-1);
    startPre->next = head;
    tail = start = tmp = head;
    while (--left > 0)
        startPre = startPre->next;

    start = startPre->next;
    while (--right > 0)
        tail = tail->next;

    tmp = tail->next;
    tail->next = nullptr; // mark end position
    startPre->next = reverseList2(startPre->next);
    start->next = tmp;
    if (dummyHead == startPre) {
        head = dummyHead->next;
        delete startPre;
    }
    return head;
}
int main()
{
    ListNode* head = createLinkedList({ 3, 5 });
    printLinkedList(head);
    ListNode* new_head = reverseBetween(head, 1, 2);
    printLinkedList(new_head);
    return 0;
}