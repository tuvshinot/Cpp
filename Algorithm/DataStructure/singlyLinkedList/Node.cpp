#include "Node.h"

int Node::value{0};
Node Node::next{nullptr};

Node::Node(int val)
    :val{val} {
}

