#include "../tests.h"
#include "../Game.h"
#include <iostream>

int Game_Save(){
    // Arrange
    Game g;
    Player p;

    p.setName("PLAYERONE");
    //Tile t = Tile('A',1);
    //p.fillHand(t);    //This causes a double free. why?
    g.AddPlayer(p);

    //p.setName("PLAYERTWO");
    //p.fillHand(Tile('B',2));
    //g.AddPlayer(p);

    // Act
    std::ifstream pre("saves/testSave.txt");
    if (pre){
        //std::cout << "Removing file: saves/testSave.txt" << std::endl;
        remove("saves/testSave.txt");
    }

    g.saveState("testSave");

    // Assert
    int numFailures = 0;
    std::ifstream post("saves/testSave.txt");
    numFailures += AssertAndReport(post.good(), 1, "Game_Save_CreatesFile");

    std::string name, hand;
    int score;

    post >> name;
    post >> score;
    post >> hand;

    numFailures += AssertAndReport(name, "PLAYERONE", "Game_Save_Name");
    numFailures += AssertAndReport(score, 0, "Game_Save_Score");
    numFailures += AssertAndReport(hand, "", "Game_Save_Hand");

    return numFailures;
}

int Game_Load(){
    // Arrange
    Game g;
    //g.AddPlayer();

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_Load");

    return numFailures;
}

int Game_InitaliseBag(){
    // Arrange
    Game g;
    LinkedList t = LinkedList();

    // Act
    g.InitaliseBag(t);

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport(t.Count(), 98, "Game_InitaliseBag_Size");

    // Count Frequencies
    int freqs[26] = {0};
    int exp[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};

    std::string got = "";
    std::string exps = "";

    // get letter freqs
    int const count = t.Count();
    for (int i=0; i < count; i++){
        char l = t.DrawTile().getLetter();
        freqs[(int)l - 65]++;
    }

    // construct strings
    for (int i=0; i < 26; i++){
        exps += (char)(i+65);
        got += (char)(i+65);

        exps += "-";
        got += "-";

        exps += std::to_string(exp[i]);
        got += std::to_string(freqs[i]);

        if (i < 25){
            exps +=", ";
            got +=", ";
        }
    }

    numFailures += AssertAndReport(got, exps, "Game_InitaliseBag_Freqs");

    return numFailures;
}

int Game_ValidNames(){
    // Arrange
    Game g;
    LinkedList t;

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_ValidNames");

    return numFailures;
}

int Game_MainMenuChoices(){
    // Arrange
    Game g;

    // Act
    //TODO

    // Assert
    int numFailures = 0;
    numFailures += AssertAndReport("TODO", "", "Game_MainMenuChoices");

    return numFailures;
}


int Game_RunTests(){
    int numFailures = 0;

    //numFailures += Game_MainMenuChoices();
    //numFailures += Game_ValidNames();
    numFailures += Game_InitaliseBag();
    numFailures += Game_Save();
    //numFailures += Game_Load();

    std::cout << std::endl;
    return numFailures;
}