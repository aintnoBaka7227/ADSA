#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Node {
    private:
    int element;
    Node* left;
    Node* right;
    int height;
    friend class AVLTree;
    public:
    Node(int element) : element(element), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
    private:
    Node* root;

    int get_height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int get_balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return get_height(node->left) - get_height(node->right);
    }

    Node* left_rotate(Node* node) {
        Node *right_node = node->right;
        Node *right_down_left = right_node->left;
        right_node->left = node;
        node->right = right_down_left;
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        right_node->height = 1 + std::max(get_height(right_node->left), get_height(right_node->right));
        return right_node;
    }

    Node* right_rotate(Node* node) {
        Node *left_node = node->left;
        Node *left_down_right = left_node->right;
        left_node->right = node;
        node->left = left_down_right;
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        left_node->height = 1 + std::max(get_height(left_node->left), get_height(left_node->right));
        return left_node;
    }

    Node* min(Node* node) {
        Node* temp = node;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    Node* insert_val(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->element) {
            node->left = insert_val(node->left, val);
        }
        else if (val > node->element) {
            node->right = insert_val(node->right, val);
        }
        else {
            return node;
        }

        node->height = 1 + std::max(get_height(node->left), get_height(node->right));

        int balance = get_balance(node);

        if (balance > 1 && node->left->element > val) {
            return right_rotate(node);
        }
        if (balance > 1 && node->left->element < val) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (balance < -1 && node->right->element < val) {
            return left_rotate(node);
        }
        if (balance < -1 && node->right->element > val) {
            node->right = right_rotate(node);
            return left_rotate(node);
        }
        return node;
    }

    Node* delete_val(Node* root, int val) {
        if (root == nullptr) {
            return root;
        }

        if (root->element > val) {
            root->left = delete_val(root->left, val);
        }
        else if (root->element < val) {
            root->right = delete_val(root->right, val);
        }
        else {
            if (root->right == nullptr || root->left == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } 
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = min(root->right);
                root->element = temp->element;
                root->right = delete_val(root->right, temp->element);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = std::max(get_height(root->left), get_height(root->right)) + 1;
        int balance = get_balance(root);

        if (balance > 1 && get_balance(root->left) >= 0) {
            return right_rotate(root);
        }

        if (balance > 1 && get_balance(root->left) < 0) {
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }

        if (balance < -1 && get_balance(root->right) >= 0) {
            return left_rotate(root);
        }

        if (balance < -1 && get_balance(root->right) < 0) {
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
        return root;
    }

    void pre_order(Node* root) {
        if (root != nullptr) {
            std::cout << root->element << " ";
            pre_order(root->left);
            pre_order(root->right);
        }
    }

    void post_order(Node* root) {
        if (root != nullptr) {
            post_order(root->left);
            post_order(root->right);
            std::cout << root->element << " ";
        }
    }

    void in_order(Node* root) {
        if (root != nullptr) {
            in_order(root->left);
            std::cout << root->element << " ";
            in_order(root->right);
        }
    }

    public:
    AVLTree() : root(nullptr) {}

    void insert_value(int val) {
        root = insert_val(root, val);
    }

    void delete_value(int val) {
        root = delete_val(root, val);
    }
    
    void traverse_pre_order() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            pre_order(root);
        }
    }

    void traverse_post_order() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            post_order(root);
        }
    }

    void traverse_in_order() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            in_order(root);
        }
    }
};

int main() {
    std::string instruction;
    getline(std::cin, instruction);
    std::stringstream ss(instruction);
    std::string move;
    std::vector<std::string> moves;
    while(ss >> move) {
        moves.push_back(move);
    }

    AVLTree tree;

    for (size_t i = 0; i < moves.size() - 1; i++) {
        if (moves[i][0] == 'A') {
            int val = std::stoi(moves[i].substr(1));
            tree.insert_value(val);
        }
        else if (moves[i][0] == 'D') {
            int val = std::stoi(moves[i].substr(1));
            tree.delete_value(val);
        }
    }

    if (moves.back() == "PRE") {
        tree.traverse_pre_order();
        std::cout << std::endl;
    }
    else if (moves.back() == "POST") {
        tree.traverse_post_order();
        std::cout << std::endl;
    }
    else if (moves.back() == "IN") {
        tree.traverse_in_order();
        std::cout << std::endl;
    }


    return 0;
}