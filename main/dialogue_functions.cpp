#include <iostream>
#include <limits>
#include "dialogue_functions.h"

bool check_input(){
    if (std::cin.eof() || std::cin.bad()) return true;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

int dialog(const std::string messages[],int operations){
    std::string errors="";
    int number=-1;
    while (number<0 || number>=operations){
        if (!errors.empty()) std::cout << errors << std::endl;
        for (int i=0; i<operations; i++){
            std::cout << messages[i] << std::endl;
        }
        std::cout << "Enter operation:";
        if (!(std::cin >> number)) {
            if (check_input()) return 0;
            number=-1;
        }else{
            std::string residue;
            std::getline(std::cin, residue);
            if (residue.find_first_not_of("\t")!=std::string::npos){
                number=-1;
            }
        }
        errors="Wrong input. Try again.\n";
    }
    return number;
}

void dialog_create_card(Deck_of_Cards &deck){
    Card card;
    std::cout << "Enter suit and rank:\n";
    try{
    if(!(std::cin >> card)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    }catch(const std::exception &e){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << e.what() << std::endl;
        return;
    }
    try{
        deck.add_card(card);
    }catch(const std::exception &e){
        std::cout << e.what() <<std::endl;
    }
  
}

void dialog_create_random_card(Deck_of_Cards &deck){
    if (deck.get_size()>=52){
        std::cout << "Deck is already full\n";
        return;
    }
    deck.add_random_card();
}

void dialog_compare_two_cards(Deck_of_Cards &deck){
    Card first;
    Card second;
    try{
        std::cout << "Input two cards:\n";
        if(!(std::cin >> first >> second)){
            if (check_input()) throw Error_end_of_file{};
            std::cout << "Wrong input" << '\n';
            return;
        }
    }catch(const std::exception &e){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << e.what() << std::endl;
        return;
    }
    auto comparator = (first <=> second);
    if (comparator<0) std::cout << "First card < second card\n";
    else if (comparator>0) std::cout << "First card > second card\n";
    else if (comparator==0) std::cout << "First card == second card\n";
    else std::cout << "Two cards are uncomparable\n";
}

void dialog_show_card_beautifully(Deck_of_Cards &deck){
    size_t idx;
    std::cout << "Input index of card:";
    if(!(std::cin >> idx)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input\n";
        return;
    }
    if (idx>=deck.get_size()){
        std::cout << "Index out of range\n";
        return;
    }
    std::cout << deck[idx].format() << '\n';
}

void dialog_create_random_deck(Deck_of_Cards &deck){
    size_t size;
    std::cout << "Enter size of deck:";
    if(!(std::cin >> size)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    try{
        deck=Deck_of_Cards(size);
    }catch(const std::exception &e){
        std::cout << e.what() <<std::endl;
    }
}

void dialog_create_full_deck(Deck_of_Cards &deck){
    deck=Deck_of_Cards::full_deck();
}

void dialog_show_deck(Deck_of_Cards &deck){
    std::cout << deck;
}

void dialog_add_random_card(Deck_of_Cards &deck){
    try{
        deck.add_random_card();
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void dialog_remove_card(Deck_of_Cards &deck){
    size_t idx;
    std::cout << "Input index of card:";
    if(!(std::cin >> idx)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    try{
        deck.remove_card_by_index(idx);
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void dialog_get_card(Deck_of_Cards &deck){
    size_t idx;
    std::cout << "Input index of card:";
    if(!(std::cin >> idx)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    if (idx>=deck.get_size()){
        std::cout << "Index out of range\n";
        return;
    }
    std::cout << deck[idx] << '\n';
}

void dialog_sort_deck(Deck_of_Cards &deck){
    deck.sort();
}

void dialog_shuffle_deck(Deck_of_Cards &deck){
    deck.shuffle();
}

void dialog_merge_decks(Deck_of_Cards &deck){
    size_t size;
    std::cout << "Enter size of second deck:";
    if(!(std::cin >> size)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    try{
        Deck_of_Cards other(size);
        deck=deck+other;
    }catch(const std::exception &e){
        std::cout << e.what() <<std::endl;
    }
}

void dialog_check(Deck_of_Cards &deck){
    if (deck.have_duplicates()) std::cout << "Has duplicates\n";
    else std::cout << "No duplicates\n";
}

void dialog_get_group(Deck_of_Cards &deck){
    std::string suit;
    std::cout << "Enter suit to sort:";
    if(!(std::cin >> suit)){
        if (check_input()) throw Error_end_of_file{};
        std::cout << "Wrong input" << '\n';
        return;
    }
    try{
        std::cout << deck.filter_by_suit(suit);
    }catch(const std::exception &e){
        std::cout << e.what() <<std::endl;
    }
}