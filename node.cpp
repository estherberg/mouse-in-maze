
#include "node.h"
using namespace mazeNode;

Node::Node()
{
   this->type = NodeType_Wall;
   this->visited = false;
   this->up = nullptr;
   this->down = nullptr;
   this->left = nullptr;
   this->right = nullptr;
}

Node::~Node()
{

}

eNodeType Node::getType()
{
   return this->type;
}

void Node::setNeighbor(eNodeNeighbor position, Node* neighbor)
{
   switch (position)
   {
   case NodeNeighbor_Up:
      this->up = neighbor;
      break;

   case NodeNeighbor_Down:
      this->down = neighbor;
      break;

   case NodeNeighbor_Left:
      this->left = neighbor;
      break;

   case NodeNeighbor_Right:
      this->right = neighbor;
      break;
   
   default:
      break;
   }
}

Node* Node::getNeighbor(eNodeNeighbor position)
{
   Node* result = nullptr;

   switch (position)
   {
   case NodeNeighbor_Up:
      result = this->up;
      break;

   case NodeNeighbor_Down:
      result = this->down;
      break;

   case NodeNeighbor_Left:
      result = this->left;
      break;

   case NodeNeighbor_Right:
      result = this->right;
      break;
   
   default:
      break;
   }

   return result;
}

bool Node::isNeighborFree(eNodeNeighbor position)
{
   bool result = false;

   switch (position)
   {
   case NodeNeighbor_Up:
      result = (this->up && this->up->isFreeToVisit());
      break;

   case NodeNeighbor_Down:
      result = (this->down && this->down->isFreeToVisit());
      break;

   case NodeNeighbor_Left:
      result = (this->left && this->left->isFreeToVisit());
      break;

   case NodeNeighbor_Right:
      result = (this->right && this->right->isFreeToVisit());
      break;
   
   default:
      break;
   }

   return result;
}

void Node::setVisited()
{
   this->visited = true;
}

bool Node::isVisited()
{
   return this->visited;
}

bool Node::isFreeToVisit()
{
   return (this->getType() != NodeType_Wall && !this->isVisited());
}

NodeWall::NodeWall() : Node()
{
   this->type = NodeType_Wall;
}

const char NodeWall::getString()
{
   return 'w';
}

NodeFree::NodeFree() : Node()
{
   this->type = NodeType_Free;
}

const char NodeFree::getString()
{
   if (this->visited)
      return '.';

   return ' ';
}

NodeCheese::NodeCheese() : Node()
{
   this->type = NodeType_Cheese;
}

const char NodeCheese::getString()
{
   if (this->visited)
      return 'X';

   return 'c';
}
