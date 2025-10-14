/* Jonah Shulske
 * COSC-2436 Fall 2025
 * October 14, 2025
 */

// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "GenealogyTree.h"
#include "queue.h"
#include "stack.h"
using namespace std;

void BuildTreeFromFile(const std::string& filename, GenealogyTree& tree);
vector< vector<TreeNode*> > LevelOrderTraversal(TreeNode* root);
bool IsDescendant(TreeNode* ancestor, TreeNode* descendant);

int main() {
    
    GenealogyTree tree;
    BuildTreeFromFile("genealogy.txt", tree);
    
    cout << endl;
    std::cout << "Printing tree:" << endl;
    tree.PrintTree();
    cout << endl;

    vector<vector<TreeNode*>> levels = LevelOrderTraversal(tree.GetRoot());
    for (int i = 0; i < levels.size(); i++) {
		std::cout << "Level " << i << ": ";
        std::cout << levels[i][0]->name;
        for (int j = 1; j < levels[i].size(); j++) {
			std::cout << ", " << levels[i][j]->name;
		}
        
		cout << endl;
	}
    cout << endl;

    TreeNode* ancestor = tree.FindNode(tree.GetRoot(), "Margaret Johnson");
    TreeNode* descendant1 = tree.FindNode(tree.GetRoot(), "Charlotte Lee");
    TreeNode* descendant2 = tree.FindNode(tree.GetRoot(), "Aria Carter");
    std::cout << std::boolalpha;
    std::cout << "Is " << descendant1->name << " a descendant of " << ancestor->name << "? " 
        << IsDescendant(ancestor, descendant1) << std::endl;
    std::cout << "Is " << descendant2->name << " a descendant of " << ancestor->name << "? " 
		<< IsDescendant(ancestor, descendant2) << std::endl;

    return 0;
}

void BuildTreeFromFile(const string& filename, GenealogyTree& tree) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string name, motherName;
        int birthYear;

        getline(iss, name, ',');
        iss.get(); // Skip the space after the comma
        getline(iss, motherName, ',');
        iss.get(); // Skip the space after the comma
        iss >> birthYear;

        tree.AddChild(name, motherName, birthYear);
    }
}

// Traversing each level of the tree. The runtime of this function is O(N) due to having to check each element in the vector/queue
//@param The roots of each member of the family tree
//@return The result of all the levels of the tree
vector<vector<TreeNode*>> LevelOrderTraversal(TreeNode* root) 
{
        
    vector<vector<TreeNode*>> result;
    if (!root) return result;

    DequeQueue<TreeNode*> queue;
    queue.Enqueue(root);

    while (!queue.IsEmpty())
    {
        int levelSize = queue.GetLength();
        vector<TreeNode*> level;

        for (int index = 0; index < levelSize; ++index)
        {
            TreeNode* node = queue.Peek();
            queue.Dequeue();
            level.push_back(node);
            for (TreeNode* child : node->children)
                queue.Enqueue(child);
        }
        result.push_back(level);
    }
    
    return result;
}

bool IsDescendant(TreeNode* ancestor, TreeNode* descendant) 
{
    if (!ancestor || !descendant) return false;
    if (ancestor == descendant) return true;

    DequeStack<TreeNode*> stack;
    stack.Push(ancestor);

    while (!stack.IsEmpty())
    {
        TreeNode* node = stack.Peek();
        stack.Pop();
        if (node == descendant)
            return true;

        for (TreeNode* child : node->children)
            stack.Push(child);
    }
    
    return false;
}
