#include <iostream>

using namespace std;

struct ViolationNode {
    char* violation;
    ViolationNode* next;

    ViolationNode(const char* v) : next(nullptr) {
        int length = 0;
        while (v[length] != '\0') ++length;
        violation = new char[length + 1];
        for (int i = 0; i <= length; ++i) {
            violation[i] = v[i];
        }
    }

    ~ViolationNode() {
        delete[] violation;
    }
};

struct Node {
    char* carNumber;
    ViolationNode* violations;
    Node* left;
    Node* right;

    Node(const char* num, const char* violation) : violations(new ViolationNode(violation)), left(nullptr), right(nullptr) {
        int length = 0;
        while (num[length] != '\0') ++length;
        carNumber = new char[length + 1];
        for (int i = 0; i <= length; ++i) {
            carNumber[i] = num[i];
        }
    }

    ~Node() {
        delete[] carNumber;
    }
};

class TrafficDatabase {
private:
    Node* root;

    int compareStrings(const char* str1, const char* str2) {
        while (*str1 && *str2) {
            if (*str1 != *str2) return *str1 - *str2;
            ++str1;
            ++str2;
        }
        return *str1 - *str2;
    }

    Node* add(Node* node, const char* carNumber, const char* violation) {
        if (!node)
            return new Node(carNumber, violation);
        if (compareStrings(carNumber, node->carNumber) < 0)
            node->left = add(node->left, carNumber, violation);
        else
            addViolationToList(node->violations, violation);
        return node;
    }

    void addViolationToList(ViolationNode*& list, const char* violation) {
        ViolationNode* current = list;
        while (current->next) {
            current = current->next;
        }
        current->next = new ViolationNode(violation);
    }

public:
    TrafficDatabase() : root(nullptr) {}

    void addViolation(const char* carNumber, const char* violation) {
        root = add(root, carNumber, violation);
    }
};

int main() {
    TrafficDatabase database;

    database.addViolation("BB5678GH", "Overloading the vehicle");
    database.addViolation("CC9101IJ", "Driving under the influence");
    database.addViolation("DD3456KL", "Illegal parking");
    database.addViolation("BB5678GH", "Using a mobile phone while driving");
    database.addViolation("EE7890MN", "Not stopping at a pedestrian crossing");
}
