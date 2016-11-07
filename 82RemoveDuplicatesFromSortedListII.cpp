/*
82. Remove Duplicates from Sorted List II
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// The above solution uses more spaces and time than other algo, but time complexity is still O(n)
// It's more readable and understandable than other algo.
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        unordered_map<int, vector<ListNode*>> mNodes;
        vector<int> vValues;
        
        ListNode* pNode = head;
        while ( pNode ) {
            int val = pNode->val;
            vValues.push_back(val);
            mNodes[val].push_back(pNode);
            pNode = pNode->next;
        }
        
        head = NULL;
        pNode = NULL;
        for (const auto& val : vValues) {
            if ( mNodes[val].size() == 1 ) {
                
                if ( pNode == NULL ) {
                    pNode = mNodes[val][0];
                    head = pNode;
                } else {
                    pNode->next = mNodes[val][0];
                    pNode = pNode->next;
                }
            }
        }
       if ( pNode ) {
           pNode->next = NULL; // Make sure the next of last node points to NULL
       }
       return head;
    }
};
