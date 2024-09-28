/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode * merge (ListNode * x, ListNode * y) {
            auto head = new ListNode();
            auto cur = head;
            for ( ; y ; y = y -> next) {
                while (x != nullptr  and x -> val <= y -> val) {
                    cur -> next = x;
                    cur = cur -> next;
                    x = x -> next;
                }
                cur -> next = y;
                cur = cur -> next;
            }
            cur -> next = x;
            return head -> next;
        }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        int n = lists.size(); ListNode * cur = nullptr;
        for (int i = 0; i < n; i ++) {
            cur = merge(cur, lists[i]);
        }
        return cur;
    }
};