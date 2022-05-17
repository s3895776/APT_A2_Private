
#include "../tests.h"
#include "../LinkedList.h"
#include <iostream>

//int LL_RunTests();
//int LL_Test_Add();
//int LL_Test_Count();
//int LL_Test_Draw();
//void Test_Transfer();

int LL_Test_Add(){
    
    // Arrange
    Tile tile1('A', 1);
    Tile tile2('B', 2);
    LinkedList bag;

    // Act
    bag.AddTile(tile1);
    bag.AddTile(tile2);

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(bag.ToString(),"A-1, B-2","LinkedList_Add ");

    return numFailures;
}

int LL_Test_Count(){
    int numFailures = 0;

    // Arrange
    Tile tile1('A', 0);
    LinkedList bag;

    numFailures += AssertAndReport(std::to_string(bag.Count()), "0", "LinkedList_InitaliseEmpty");

    // Act 1 : Add tiles
    bag.AddTile(tile1);
    bag.AddTile(tile1);
    bag.AddTile(tile1);

    // Assert 1
    numFailures += AssertAndReport(std::to_string(bag.Count()), "3", "LinkedList_Count_3");

    // Act 2: Overdraw
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();
    bag.DrawTile();

    // Assert 2
    numFailures += AssertAndReport(std::to_string(bag.Count()), "0", "LinkedList_Count_NoNeg");

    return numFailures;
}

int LL_Test_Draw(){
    int numFailures = 0;

    // Arrange
    Tile tile1('A', 1);
    Tile tile2('B', 2);
    LinkedList bag;

    // Act
    char bagDraw = bag.DrawTile().getLetter();

    // Assert
    numFailures += AssertAndReport(bagDraw,' ', "LinkedList_Draw(empty)");

    // Act
    bag.AddTile(tile1);
    bag.AddTile(tile2);
    Tile t1 = (bag.DrawTile());
    Tile t2 = (bag.DrawTile());

    // Assert
    numFailures += AssertAndReport(t1.getLetter(), 'A', "LinkedList_DrawOrder");

    return numFailures;
}

int LL_Test_Draw_Existing_Tile(){
    int numFailures = 0;

    // Arrange
    Tile tile1('A', 1);
    Tile tile2('B', 2);
    LinkedList bag;

    // Act
    bag.AddTile(tile1);
    bag.AddTile(tile2);
    Tile endTile = bag.DrawTile(tile2);

    // Assert
    numFailures += AssertAndReport(endTile.getLetter(), 'B', "LinkedList_DrawOrder");

    return numFailures;
}


int LL_RunTests(){
    int numFailures = 0;

    numFailures += LL_Test_Add();
    numFailures += LL_Test_Count();
    numFailures += LL_Test_Draw();
    numFailures += LL_Test_Draw_Existing_Tile();

    //std::cout << "    LinkedList Failures: " << numFailures << "\n\n";
    std::cout << std::endl;
    return numFailures;
}

