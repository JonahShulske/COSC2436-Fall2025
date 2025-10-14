// GenealogyTree.h
#ifndef _GENEALOGYTREE_H_
#define _GENEALOGYTREE_H_

#include <string>
#include <vector>
#include <unordered_map>

struct TreeNode {
    std::string name;
    int birthYear;
    std::vector<TreeNode*> children;

    TreeNode(const std::string& name, int birthYear) : name(name), birthYear(birthYear) {}
};

class GenealogyTree {
public:
    TreeNode* root;
    std::unordered_map<std::string, TreeNode*> nodeMap;

    GenealogyTree(const std::string& rootName, int rootBirthYear);
    GenealogyTree();

    void AddChild(const std::string& childName, const std::string& parentName, int birthYear);
    TreeNode* GetRoot() const;
    TreeNode* FindNode(TreeNode* start, const std::string& name);

    std::vector<TreeNode*> GetChildren(TreeNode* parent);
    std::vector<TreeNode*> GetChildren(std::string motherName);

    void PrintTree();

private:
    void PrintSubtree2(TreeNode* node, int level);
    void PrintSubTree(TreeNode* node, const std::string& prefix = "", bool isLast = true);
};

#endif // _GENEALOGYTREE_H_
