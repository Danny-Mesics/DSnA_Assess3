/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	TreeNode* newNode = new TreeNode(a_nValue);
	TreeNode* currentNode;
	// Set the root node
	if (IsEmpty()) {
		m_pRoot = newNode;	
		return;
	}
	currentNode = m_pRoot;
	do {
		// Check for less than
		if (newNode->GetData() < currentNode->GetData()) {
			// Set the node
			if (currentNode->GetLeft() == nullptr) {
				currentNode->SetLeft(newNode);
				return;
			}
			// Continue down tree
			else {
				currentNode = currentNode->GetLeft();
			}
		}
		// Check for greater than
		else if (newNode->GetData() > currentNode->GetData()) {
			// Set the node
			if (currentNode->GetRight() == nullptr) {
				currentNode->SetRight(newNode);
				return;
			}
			// Continue down tree
			else {
				currentNode = currentNode->GetRight();
			}
		}
		// Return if value is equal to an existing node
		else {
			return;
		}
	} 
	while (currentNode != nullptr);
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	if (IsEmpty()) {
		return false;
	}
	ppOutNode = m_pRoot;
	ppOutParent = m_pRoot;
	while (ppOutNode != nullptr) {
		if (a_nSearchValue == ppOutNode->GetData()) {
			return true;
		}
		else if (a_nSearchValue > ppOutNode->GetData()) {
			ppOutParent = ppOutNode;
			ppOutNode = ppOutNode->GetRight();
		}
		else {
			ppOutParent = ppOutNode;
			ppOutNode = ppOutNode->GetLeft();
		}
	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;
	TreeNode* pTemporaryNode;

	// Find the node in the tree and seed the TreeNode pointers
	if (!FindNode(a_nValue, pCurrent, pParent)) {
		return;
	}

	// Remove Leaf Node
	if (!pCurrent->HasLeft() && !pCurrent->HasRight()) {
		delete pCurrent;
		pCurrent = nullptr;
		return;
	}


	// If the left child of parent is getting deleted	
	if (pParent->GetLeft() == pCurrent) {
		// Remove node with only left child
		if (pCurrent->HasLeft() && !pCurrent->HasRight()) {
			pParent->SetLeft(pCurrent->GetLeft());
		}
		// Remove node with only right child
		else if (!pCurrent->HasLeft() && pCurrent->HasRight()) {
			pParent->SetLeft(pCurrent->GetRight());			
		}
		// Delete Current node
		delete pCurrent;
		pCurrent = nullptr;
		return;
	}


	// If the right child of parent is getting deleted
	if (pParent->GetRight() == pCurrent) {
		// Remove node with only left child
		if (pCurrent->HasLeft() && !pCurrent->HasRight()) {
			pParent->SetLeft(pCurrent->GetLeft());
		}
		// Remove node with only right child
		else if (!pCurrent->HasLeft() && pCurrent->HasRight()) {
			pParent->SetRight(pCurrent->GetRight());
		}
		// Delete Current node
		delete pCurrent;
		pCurrent = nullptr;
		return;
	}

	// Remove node with two children (check if smallest to right has right child)
	// All remaining cases will have two children
	// Check if it is possible to go right by one step
	if (pCurrent->HasRight()) {
		// Step right once, then left as far as possible
		pTemporaryNode = pCurrent->GetRight();
		while (pTemporaryNode != nullptr)
		{
			// Not checking for nullptr causes errors
			if (pTemporaryNode->GetLeft() == nullptr) {
				break;
			}
			else {
				pTemporaryNode = pTemporaryNode->GetLeft();
			}
		}
		// It is possible for temp node to have right hand nodes
		// First check to see if this is the case
		if (pTemporaryNode->HasRight()) {
			// Run FindNode passing pTemporaryNode and pParent
			// It's okay to change the address of pParent as it is
			// not required for deleting a node with 2 children 
			FindNode(pTemporaryNode->GetData(), pTemporaryNode, pParent);
			pParent->SetLeft(pTemporaryNode->GetRight());
		}
		// Set the current node to the value of the smallest
		// number larger than the node being deleted
		pCurrent->SetData(pTemporaryNode->GetData());

		delete pTemporaryNode;
		pTemporaryNode = nullptr;		
	}
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
	else {
		ClearBackground(RAYWHITE);
	}
}