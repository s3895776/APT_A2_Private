
#include "../LinkedList.h"
#include <iostream>


int LL_RunTests();

int LL_Test_Add();
int LL_Test_Count();
int LL_Test_Draw();
//void Test_Transfer();

int LL_Test_Add(){
    int numFailures = 0;

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
        std::cout << "PASSED!\n";
    else{
        numFailures++;
        std::cout << "FAILED!\n";
        std::cout << "Expected: 'A-1, B-2'" << std::endl;
        std::cout << "Got: '" << bag.ToString() << "'" << std::endl; 
    }

    return numFailures;
}

int LL_Test_Count(){
    int numFailures = 0;

    //std::cout << "Test LinkedList_Count \n";

    //create all tiles (from file?)
    Tile tile1('A', 0);

    //create tilebag
    LinkedList bag;

    //test 1
    std::cout << "Test LinkedList_Count(0) ";
    if (bag.Count() == 0)
        std::cout << "PASSED!\n";
    else{
        numFailures++;
        std::cout << "FAILED!\n ";
        std::cout << "Expected: 0" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

    //Add tiles to bag
    bag.AddTile(tile1);
    bag.AddTile(tile1);
    bag.AddTile(tile1);

    //test 2
    std::cout << "Test LinkedList_Count(3) ";
    if (bag.Count() == 3)
        std::cout << "PASSED!\n";
    else{
        numFailures++;
        std::cout << "FAILED!\n";
        std::cout << "Expected: 3" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

    //test 3: overdraw
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();
    std::cout << "Test LinkedList_Count_NoNeg ";
    if (bag.Count() == 0)
        std::cout << "PASSED!\n";
    else{
        numFailures++;
        std::cout << "FAILED!\n";
        std::cout << "Expected: 0" << std::endl;
        std::cout << "Got: " << bag.Count() << std::endl; 
    }

    return numFailures;
}

int LL_Test_Draw(){
    int numFailures = 0;

    //std::cout << "Test LinkedList_Draw \n";

    //create all tiles (from file?)
    Tile tile1('A', 1);
    Tile tile2('B', 2);

    //create tilebag
    LinkedList bag;

    //test 1: empty list returns nullptr
    
    char bagDraw = bag.DrawTile().getLetter();

    std::cout << "Test LinkedList_Draw(empty) ";
    if (bagDraw == ' ') {
        std::cout << "PASSED!\n";
    } else {
        numFailures++;
        std::cout << "FAILED!\n";
        std::cout << "  Expected: ' '" << std::endl;
        std::cout << "  Got: '" << bagDraw << "'" << std::endl; 
    }

    //Add tiles to bag
    bag.AddTile(tile1);
    bag.AddTile(tile2);

    //std::cout << bag.ToString() << std::endl;
    Tile t1 = (bag.DrawTile());
    //std::cout << bag.ToString() << std::endl;
    Tile t2 = (bag.DrawTile());
    //std::cout << bag.ToString() << std::endl;

    //test 2:
    std::cout << "Test LinkedList_DrawOrder ";
    if (t1.getLetter() == 'A' && t2.getLetter() == 'B')
        std::cout << "PASSED!\n";
    else{
        numFailures++;
        std::cout << "FAILED!\n";
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

    return numFailures;
}


int LL_RunTests(){
    int numFailures = 0;

    numFailures += LL_Test_Add();
    numFailures += LL_Test_Count();
    numFailures += LL_Test_Draw();
    //Test_Transfer();

    std::cout << "LinkedList failures: " << numFailures << std::endl << std::endl;
    return numFailures;
}

