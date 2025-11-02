#include <iostream>
#include <queue>
#include <memory>

enum Color { RED, BLACK };

template<typename T>
class RBTreeNode {
public:
    T data;
    Color color;
    std::shared_ptr<RBTreeNode<T>> left;
    std::shared_ptr<RBTreeNode<T>> right;
    std::shared_ptr<RBTreeNode<T>> parent;
    
    RBTreeNode(T val) : data(val), color(RED), left(nullptr), 
                       right(nullptr), parent(nullptr) {}
};

template<typename T>
class RedBlackTree {
private:
    std::shared_ptr<RBTreeNode<T>> root;
    std::shared_ptr<RBTreeNode<T>> NIL;  // Sentinel node
    
    // Initialize NIL node
    void initializeNIL() {
        NIL = std::make_shared<RBTreeNode<T>>(T());
        NIL->color = BLACK;
        NIL->left = nullptr;
        NIL->right = nullptr;
        NIL->parent = nullptr;
    }
    
    // Left rotation
    void leftRotate(std::shared_ptr<RBTreeNode<T>> x) {
        auto y = x->right;
        x->right = y->left;
        
        if (y->left != NIL) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    // Right rotation
    void rightRotate(std::shared_ptr<RBTreeNode<T>> x) {
        auto y = x->left;
        x->left = y->right;
        
        if (y->right != NIL) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        
        y->right = x;
        x->parent = y;
    }
    
    // Fix violation after insertion
    void fixInsert(std::shared_ptr<RBTreeNode<T>> k) {
        std::shared_ptr<RBTreeNode<T>> u;
        
        while (k->parent != nullptr && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;  // uncle
                
                if (u->color == RED) {
                    // Case 1: Uncle is RED
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    // Case 2: Uncle is BLACK
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    // Case 3
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;  // uncle
                
                if (u->color == RED) {
                    // Case 1: Uncle is RED
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    // Case 2: Uncle is BLACK
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    // Case 3
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            
            if (k == root) break;
        }
        
        root->color = BLACK;
    }
    
    // Transplant node during deletion
    void rbTransplant(std::shared_ptr<RBTreeNode<T>> u, std::shared_ptr<RBTreeNode<T>> v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    
    // Fix violation after deletion
    void fixDelete(std::shared_ptr<RBTreeNode<T>> x) {
        std::shared_ptr<RBTreeNode<T>> s;
        
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                
                if (s->color == RED) {
                    // Case 1: Sibling is RED
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    // Case 2: Both siblings' children are BLACK
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        // Case 3: Sibling's right child is BLACK
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    
                    // Case 4: Sibling's right child is RED
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                
                if (s->color == RED) {
                    // Case 1: Sibling is RED
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    // Case 2: Both siblings' children are BLACK
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        // Case 3: Sibling's left child is BLACK
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    
                    // Case 4: Sibling's left child is RED
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        
        x->color = BLACK;
    }
    
    // Find minimum node
    std::shared_ptr<RBTreeNode<T>> minimum(std::shared_ptr<RBTreeNode<T>> node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }
    
    // Helper for deletion
    void deleteNodeHelper(std::shared_ptr<RBTreeNode<T>> node, T key) {
        auto z = NIL;
        auto x = NIL;
        auto y = NIL;
        
        // Find the node to delete
        while (node != NIL) {
            if (node->data == key) {
                z = node;
            }
            
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        
        if (z == NIL) {
            std::cout << "Key not found in the tree" << std::endl;
            return;
        }
        
        y = z;
        Color y_original_color = y->color;
        
        if (z->left == NIL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

public:
    RedBlackTree() {
        initializeNIL();
        root = NIL;
    }
    
    // Insert a value
    void insert(T val) {
        auto node = std::make_shared<RBTreeNode<T>>(val);
        node->parent = nullptr;
        node->left = NIL;
        node->right = NIL;
        node->color = RED;
        
        auto y = nullptr;
        auto x = root;
        
        while (x != NIL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        node->parent = y;
        
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        
        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        
        if (node->parent->parent == nullptr) {
            return;
        }
        
        fixInsert(node);
    }
    
    // Delete a value
    void remove(T key) {
        deleteNodeHelper(root, key);
    }
    
    // Search for a value
    bool search(T key) {
        auto temp = root;
        
        while (temp != NIL) {
            if (key == temp->data) {
                return true;
            } else if (key < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return false;
    }
    
    // In-order traversal
    void inOrder() {
        std::cout << "In-order: ";
        inOrderHelper(root);
        std::cout << std::endl;
    }
    
    void inOrderHelper(std::shared_ptr<RBTreeNode<T>> node) {
        if (node != NIL) {
            inOrderHelper(node->left);
            std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inOrderHelper(node->right);
        }
    }
    
    // Level-order traversal (BFS) for visualization
    void levelOrder() {
        std::cout << "Level-order: ";
        if (root == NIL) return;
        
        std::queue<std::shared_ptr<RBTreeNode<T>>> q;
        q.push(root);
        
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            
            std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            
            if (node->left != NIL) q.push(node->left);
            if (node->right != NIL) q.push(node->right);
        }
        std::cout << std::endl;
    }
    
    // Get root
    std::shared_ptr<RBTreeNode<T>> getRoot() {
        return root;
    }
    
    // Visualize tree structure
    void visualize() {
        std::cout << "\nTree Structure:\n";
        visualizeHelper(root, 0, "");
    }
    
    void visualizeHelper(std::shared_ptr<RBTreeNode<T>> node, int level, std::string prefix) {
        if (node != NIL) {
            visualizeHelper(node->right, level + 1, "    ");
            
            for (int i = 0; i < level; i++) {
                std::cout << "    ";
            }
            
            std::cout << prefix << node->data << "(" << (node->color == RED ? "R" : "B") << ")\n";
            
            visualizeHelper(node->left, level + 1, "    ");
        }
    }
    
    // Check Red-Black Tree properties
    bool validateRBTree() {
        if (root == NIL) return true;
        
        // Property 2: Root must be black
        if (root->color != BLACK) {
            std::cout << "Violation: Root is not black!" << std::endl;
            return false;
        }
        
        // Check all properties
        int blackCount = -1;
        return checkRBProperties(root, 0, blackCount);
    }
    
    bool checkRBProperties(std::shared_ptr<RBTreeNode<T>> node, int blackCount, int& pathBlackCount) {
        if (node == NIL) {
            if (pathBlackCount == -1) {
                pathBlackCount = blackCount;
            } else if (blackCount != pathBlackCount) {
                std::cout << "Violation: Different black counts on paths!" << std::endl;
                return false;
            }
            return true;
        }
        
        // Property 4: No two consecutive red nodes
        if (node->color == RED) {
            if (node->left->color == RED || node->right->color == RED) {
                std::cout << "Violation: Two consecutive red nodes!" << std::endl;
                return false;
            }
        }
        
        // Count black nodes
        int newBlackCount = blackCount + (node->color == BLACK ? 1 : 0);
        
        return checkRBProperties(node->left, newBlackCount, pathBlackCount) &&
               checkRBProperties(node->right, newBlackCount, pathBlackCount);
    }
};