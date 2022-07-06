
#include "maze.h"
using namespace maze;

Maze::Maze(const char ascii[16][16], startPoint point)
{
   for (int line = 0; line < 16; line++)
   {
      for (int col = 0; col < 16; col++)
      {
         switch (ascii[line][col])
         {
         case ' ':
            this->nodes[line][col] = new mazeNode::NodeFree();
            break;

         case 'w':
            this->nodes[line][col] = new mazeNode::NodeWall();
            break;
         
         case 'c':
            this->nodes[line][col] = new mazeNode::NodeCheese();
            break;
         
         default:
            this->nodes[line][col] = nullptr;
            break;
         }
      }
   }

   // add the neighbors
   for (int line = 0; line < 16; line++)
   {
      for (int col = 0; col < 16; col++)
      {
         if (line - 1 > 0)
            this->nodes[line][col]->setNeighbor(mazeNode::NodeNeighbor_Up, this->nodes[line - 1][col]);
         if (line + 1 < 16)
            this->nodes[line][col]->setNeighbor(mazeNode::NodeNeighbor_Down, this->nodes[line + 1][col]);
         if (col - 1 > 0)
            this->nodes[line][col]->setNeighbor(mazeNode::NodeNeighbor_Left, this->nodes[line][col - 1]);
         if (col + 1 < 16)
            this->nodes[line][col]->setNeighbor(mazeNode::NodeNeighbor_Right, this->nodes[line][col + 1]);
      }
   }

   // set the start point
   this->starter = this->nodes[point.line][point.col];
}

Maze::~Maze()
{
   for (int line = 0; line < 16; line++)
   {
      for (int col = 0; col < 16; col++)
      {
         if (this->nodes[line][col])
            delete this->nodes[line][col];
      }
   }
}

bool Maze::checkConsistency()
{
   for (int line = 0; line < 16; line++)
   {
      for (int col = 0; col < 16; col++)
      {
         if (nullptr == this->nodes[line][col])
            return false;
      }
   }

   if (this->starter->getType() != mazeNode::NodeType_Free)
      return false;

   return true;
}

bool Maze::solve()
{
   return this->parse(this->starter);
}

void Maze::getAsciiFormat(char ascii[16][16])
{
   for (int line = 0; line < 16; line++)
   {
      for (int col = 0; col < 16; col++)
      {
         ascii[line][col] = this->nodes[line][col]->getString();
      }
   }
}

bool Maze::parse(mazeNode::Node *node)
{
   node->setVisited();

   if (mazeNode::NodeType_Cheese == node->getType())
      return true;

   if (node->isNeighborFree(mazeNode::NodeNeighbor_Up))
      if (this->parse(node->getNeighbor(mazeNode::NodeNeighbor_Up)))
         return true;

   if (node->isNeighborFree(mazeNode::NodeNeighbor_Left))
      if (this->parse(node->getNeighbor(mazeNode::NodeNeighbor_Left)))
         return true;

   if (node->isNeighborFree(mazeNode::NodeNeighbor_Right))
      if (this->parse(node->getNeighbor(mazeNode::NodeNeighbor_Right)))
         return true;

   if (node->isNeighborFree(mazeNode::NodeNeighbor_Down))
      if (this->parse(node->getNeighbor(mazeNode::NodeNeighbor_Down)))
         return true;

   return false;
}
