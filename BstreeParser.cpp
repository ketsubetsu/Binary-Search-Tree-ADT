/**
 * A parser program to test the binary search tree implementation
 * @author ketsubetsu
 * @see Bstree
 * <pre>
 * File: BstreeParser.cpp
 * Parses a text file containing statement in the binary search tree 
 * "language" that has the following grammar :-
 * trim: delete all leaf nodes from the tree and decrement it size accordingly
 * delete <item> : removes the specified item from the tree, if in the tree
 * insert <item> : insert the specified item in the tree or overwrite the
 *                 the item with the specified key if it is already in the tree
 * traverse: displays three lists in preorder, inorder, and postorder traversal 
 *           of data this tree. one per line.
 * stats: displays the following information about this tree
 *        height = ?  size = ?
 *        #leaves = ?   #half-nodes = ?
 *        ?perfect = ?    ?balanced = ?
 *        minimum = ?     maximum = ?
 * </pre>
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "Bstree.cpp"


using namespace std;

/**
 * Displays a string and advances the cursor to the next line
 * @param word the string to be displayed
 */
void printWord(const string& word)
{
   cout<<word<<endl;
}

int main(int argc, char** argv)
{
   try
   {
      if (argc != 2)
      {
          cerr<<"Usage: BstreeParser <Bstree-Prog-Filename>"<<endl;
          exit(1);
      }
      string filename = argv[1];
      fstream inFile;
      inFile.open(filename.c_str(),ios::in);
      if (!inFile)
      {
         cerr<<"Unable to open "<<filename<<" for input."<<endl;
         exit(2);
      }
      string cmd, token;
      Bstree<string> words;
      while (inFile>>cmd)
      {
         if (cmd == "trim")
         {
            words.trim();
            cout<<"leaf nodes deleted"<<endl;
            cout<<endl;
         }
         else if (cmd == "delete")
         {
            inFile>>token;
            words.remove(token);
            cout<<"deleted "<<token<<endl;
         }
         else if (cmd == "insert")
         {
            inFile>>token;
            words.insert(token);
            cout<<"inserted "<<token<<endl;
         }    
         else if (cmd == "traverse")
         {
            cout<<endl<<"***Traversals***"<<endl;
            cout<<"======================================"<<endl;
            cout<<"Preorder Traversal"<<endl;
            cout<<"--------------------------------------"<<endl;
            words.preorderTraverse(printWord);
            cout<<"--------------------------------------"<<endl;
            cout<<"Inorder Traversal"<<endl;
            cout<<"--------------------------------------"<<endl;
            words.inorderTraverse(printWord);
            cout<<"--------------------------------------"<<endl;
            cout<<"Postorder Traversal"<<endl;
            cout<<"--------------------------------------"<<endl;
            words.postorderTraverse(printWord);
            cout<<"--------------------------------------"<<endl;
            cout<<endl;
         }       
         else if (cmd == "stats")
         {
            cout<<endl<<"***Statistics/Information***"<<endl;
            long treeHeight = words.height();
            long treeSize = words.size();
            long halfCount = words.countHalves();
            string label1 = "?perfect = ", label2 = "?balanced = ";
            bool isPerfect = treeSize == static_cast<long>(pow(2,treeHeight+1))-1;
            cout<<left<<setw(20)<<"height = "+to_string(treeHeight)
                <<left<<setw(20)<<"size = "+to_string(treeSize)<<endl;
            cout<<left<<setw(20)<<"#leaves = "+to_string(words.countLeaves())
                <<left<<setw(20)<<"#halves-nodes = "+to_string(halfCount)<<endl;
            if (words.empty())
            {
               cout<<left<<setw(20)<<"minimum = UNDEFINED"
               <<left<<setw(20)<<"maximum = UNDEFINED"<<endl;
            }
            else
            {
               cout<<left<<setw(20)<<"minimum = "+words.min()
                <<left<<setw(20)<<"maximum = "+words.max()<<endl;
            }
            cout<<left<<setw(20)<<label1+(isPerfect ? "true" : "false")
                <<left<<setw(20)<<label2+(words.isBalanced() ? "true" : "false")<<endl<<endl;
         }    
         else
         {
            throw BstreeException(filename+" parsing error");
         }
      }
   }
   catch(const BstreeException& e)
   {
      cerr<<e.what()<<endl;
   }
   return 0;
}

