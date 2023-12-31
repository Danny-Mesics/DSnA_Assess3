#include "TreeNode.h"
#include "raylib.h"
#include <string>

TreeNode::TreeNode(int value) : m_value(value), m_left(nullptr), m_right(nullptr)
{
}


TreeNode::~TreeNode()
{
	if (m_left != nullptr) {
		delete m_left;
	}
	if (m_right != nullptr) {
		delete m_right;
	}
}

void TreeNode::Draw(int x, int y, bool selected)
{
	static char buffer[10];

	sprintf(buffer, "%d", m_value);

	DrawCircle(x, y, 30, YELLOW);

	if (selected == true)
		DrawCircle(x, y, 28, GREEN);		
	else
		DrawCircle(x, y, 28, BLACK);
			

	DrawText(buffer, x - 12, y - 10, 12, WHITE);
}