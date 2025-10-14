// GenealogyTree.cpp
#include <iostream>
#include "GenealogyTree.h"
using namespace std;

GenealogyTree::GenealogyTree() : root(nullptr) {}

GenealogyTree::GenealogyTree(const std::string& rootName, int rootBirthYear) {
    AddChild(rootName, "None", rootBirthYear);
}

void GenealogyTree::AddChild(const std::string& childName, const std::string& parentName, int birthYear) {
    TreeNode* childNode = new TreeNode(childName, birthYear);
    
    nodeMap[childName] = childNode;
    if (parentName == "None") {
        root = childNode;
    }
    else {
        TreeNode* parentNode = nodeMap[parentName];
        parentNode->children.push_back(childNode);
    }
}

TreeNode* GenealogyTree::GetRoot() const {
    return this->root;
}

TreeNode* GenealogyTree::FindNode(TreeNode* start, const std::string& name) {
    if (start == nullptr) return nullptr;
    if (start->name == name) return start;

    for (auto child : start->children) {
        TreeNode* found = FindNode(child, name);
        if (found) return found;
    }
    return nullptr;
}

std::vector<TreeNode*> GenealogyTree::GetChildren(TreeNode* parent) {
    std::vector<TreeNode*> children;
    if (parent != nullptr) {
        for (auto child : parent->children) {
            children.push_back(child);
        }
    }
    return children;
}

std::vector<TreeNode*> GenealogyTree::GetChildren(std::string motherName)
{
    std::vector<TreeNode*> children;
    TreeNode* mother = nodeMap[motherName];
    if (mother != nullptr) {
        for (auto child : mother->children) {
			children.push_back(child);
		}
	}
    return children;
}

void GenealogyTree::PrintTree() {
	PrintSubTree(root);
}


void GenealogyTree::PrintSubtree2(TreeNode* node, int level) {
    if (node == nullptr) return;

    // Indentation for the current level
    std::string indent(level * 2, ' '); // 2 spaces per level of depth
    std::cout << indent << "- " << node->name << " (" << node->birthYear << ")" << std::endl;

    // Recursively print each child
    for (TreeNode* child : node->children) {
        PrintSubtree2(child, level + 1);
    }
}

void GenealogyTree::PrintSubTree(TreeNode* node, const std::string& prefix, bool isLast) {
    if (node == nullptr) return;

    std::cout << prefix;

    // Check if it's the root node, which doesn't have a prefix
    if (!prefix.empty()) {
        //std::cout << (isLast ? "└── " : "├── ");
        std::cout << (isLast ? "|__ " : "|-- ");
    }

    // Print the current node
    std::cout << node->name << " (" << node->birthYear << ")" << std::endl;

    // Construct the next prefix
    std::string childPrefix = prefix + (isLast ? "    " : "|   ");

    // Print children
    for (size_t i = 0; i < node->children.size(); ++i) {
        PrintSubTree(node->children[i], childPrefix, i == node->children.size() - 1);
    }
}

