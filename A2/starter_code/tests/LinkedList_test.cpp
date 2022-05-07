
#include "../LinkedList.h"
#include <iostream>

void LL_RunTests();

void LL_Test_Add();
void LL_Test_Count();
void LL_Test_Draw();
//void Test_Transfer();

void LL_Test_Add(){
    std::cout << "Test LinkedList_Add ";

    //create all tiles (from file?)
    Tile tile1('A', 1);
    Tile tile2('B', 2);
    //...
    
    //create tilebag
    LinkedList bag;

    //Add tiles to bag
    bag.AddTile(tile1);
    bag.AddTile(tile2);

    if (bag.ToString()== "A-1, B-2")
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "Expected: 'A-1, B-2'" << std::endl;
        std::cout << "Got: '" << bag.ToString() << "'" << std::endl; 
    }
}

void LL_Test_Count(){
    std::cout << "Test LinkedList_Count \n";

    //create all tiles (from file?)
    Tile tile1('A', 0);

    //create tilebag
    LinkedList bag;

    //test 1
    std::cout << " test empty: ";
    if (bag.Count() == 0)
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "Expected: 0" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

    //Add tiles to bag
    bag.AddTile(tile1);
    bag.AddTile(tile1);
    bag.AddTile(tile1);

    //test 2
    std::cout << " test (3): ";
    if (bag.Count() == 3)
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "Expected: 3" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

    //test 3: overdraw
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();
    std::cout << " test overdraw: ";
    if (bag.Count() == 0)
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "Expected: 0" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

}

void LL_Test_Draw(){
    std::cout << "Test LinkedList_Draw \n";

    //create all tiles (from file?)
    Tile tile1('A', 1);
    Tile tile2('B', 2);

    //create tilebag
    LinkedList bag;

    //test 1: empty list returns nullptr
    std::cout << " test emptylist: ";
    if (bag.DrawTile() == nullptr)
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "  Expected: 'nullptr'" << std::endl;
        std::cout << "  Got: '" << bag.DrawTile() << "'" << std::endl; 
    }

    //Add tiles to bag
    bag.AddTile(tile1);
    bag.AddTile(tile2);

    //std::cout << bag.ToString() << std::endl;
    Tile t1 = *(bag.DrawTile());
    //std::cout << bag.ToString() << std::endl;
    Tile t2 = *(bag.DrawTile());
    //std::cout << bag.ToString() << std::endl;

    //test 2:
    std::cout << " test draw_order ";
    if (t1.getLetter() == 'A' && t2.getLetter() == 'B')
        std::cout << "passed!\n";
    else{
        std::cout << "failed!\n";
        std::cout << "Expected: 'A-1, B-2'" << std::endl;
        std::cout << "Got: '" << t1.getLetter() << "-" << t1.getValue() << ",";
        std::cout << t2.getLetter() << "-" << t2.getValue() << "'" << std::endl; 
    }

    //test 3:
    //bag.AddTile(tile1);
    //bag.AddTile(tile2);
//
    //std::cout << " test draw_specific_head ";
    //bag.DrawTile(tile1);
    //
    //if (bag.GetHead()->tile->letter == 'B' && bag.GetTail()->tile->letter == 'B' && bag.Count() == 1)
    //    std::cout << "passed!\n";
    //else{
    //    std::cout << "failed!\n";
    //}
//
    ////test 4:
    //bag.AddTile(tile1);
    //bag.DrawTile(tile2);
    //std::cout << " test draw_specific_tail ";
//
    //if (bag.GetHead()->tile->letter == 'A' && bag.GetTail()->tile->letter == 'A' && bag.Count() == 1)
    //    std::cout << "passed!\n";
    //else{
    //    std::cout << "failed!\n";
    //}
}


void LL_RunTests(){
    LL_Test_Add();
    LL_Test_Count();
    LL_Test_Draw();
    //Test_Transfer();
}

