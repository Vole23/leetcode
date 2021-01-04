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
    ListNode *head=nullptr,*tail=nullptr;
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int a=1,b=1,c=0;
        head=l1;
        while(l1!=nullptr||l2!=nullptr){
            if(l1!=nullptr&&l2!=nullptr){
                if(l1->next==nullptr&&l2->next!=nullptr){
                    l1->next=l2->next;
                    l2->next=nullptr;
                }
            }
            tail=l1;
            if(l2==nullptr){b=0;}else{b=l2->val;l2=l2->next;}
            if(l1==nullptr){a=0;}else{a=l1->val;l1->val=((a+b+c)%10);l1=l1->next;}
            c=(a+b+c)/10;
        }
        if(c) tail->next=new ListNode(1);
        if(head) return head;
        return new ListNode(0);
    }
};
