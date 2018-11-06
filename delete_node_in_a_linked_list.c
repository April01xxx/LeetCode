/**
 * Write a function to delete a node (except the tail) in a singly linked list,
 * given only access to that node.
 *
 * Given linked list -- head = [4,5,1,9], which looks like following:
 *
 * 4 -> 5 -> 1 -> 9
 *
 * Example 1:
 * Input: head = [4,5,1,9], node = 5
 * Output: [4,1,9]
 * Explanation: You are given the second node with value 5, the linked list
 *              should become 4 -> 1 -> 9 after calling your function.
 *
 * Example 2:
 * Input: head = [4,5,1,9], node = 1
 * Output: [4,5,9]
 * Explanation: You are given the third node with value 1, the linked list
 *              should become 4 -> 5 -> 9 after calling your function.
 *
 * Note:
 * The linked list will have at least two elements.
 * All of the nodes' values will be unique.
 * The given node will not be the tail and it will always be a valid node of
 * the linked list.
 * Do not return anything from your function.
 *
 * 给定单向链表中的一个节点,删除该节点.题目说明不会删除尾节点,其实这也提示了我们
 * 该如何解决这个问题.
 * 传统的删除节点要求我们知道前一个节点,而这里我们不知道,我们只知道当前节点,所以
 * 我们能删除的只是当前节点的下一个节点.具体做法如下:
 * 1. 找到当前节点curr的下一个节点next,将其内容拷贝到当前节点curr;
 * 2. 释放next节点;
 *
 * 看了下这题的赞和贬,截止2018年11月6号赞是517,贬达到了2304,是目前遇到贬最多的
 * 题.估计是因为这道题太投机了吧..
 * 顺带瞅了眼讨论区,得分最高的是一篇帖子,大意是为什么会有这种傻X题目.下面评论看到
 * 了很多国人的"mdzz"(妈的智障)...哈哈哈哈,也算是刷题的调剂了.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  void deleteNode(ListNode* node) {
    ListNode *next = node->next;

    node->val = next->val;
    node->next = next->next;
    delete next;
  }
};