#include <catch2/catch_all.hpp>
#include "DeckofCards.h"

TEST_CASE("Constructors of deck"){
    SECTION("Default constructor"){
        Deck_of_Cards deck;
        REQUIRE(deck.get_size()==0);
    }

    SECTION("Initialization constructor with size"){
        Deck_of_Cards deck(16);
        REQUIRE(deck.get_size()==16);
        REQUIRE_NOTHROW(Deck_of_Cards(1));
        REQUIRE_NOTHROW(Deck_of_Cards(52));
    }

    SECTION("Invalid size"){
        REQUIRE_THROWS_AS(Deck_of_Cards(70), std::invalid_argument);
        REQUIRE_THROWS_AS(Deck_of_Cards(53), std::invalid_argument);
    }
}

TEST_CASE("Random values and deck"){
    Deck_of_Cards deck;
    SECTION("Random card"){
        deck.add_random_card();
        REQUIRE(deck.get_size()==1);
        REQUIRE(deck[0].get_rank()>=1);
        REQUIRE(deck[0].get_rank()<=13);
        Suit suit=deck[0].get_suit();
        REQUIRE((suit==Suit::HEARTS || suit==Suit::SPADES || suit==Suit::DIAMONDS || suit==Suit::CLUBS));
    }

    SECTION("Full deck"){
        deck=Deck_of_Cards::full_deck();
        REQUIRE(deck.get_size()==52);
        REQUIRE_FALSE(deck.have_duplicates());
    }

    SECTION("Random deck"){
        size_t size=GENERATE(take(1, random(1,52)));
        Deck_of_Cards deck(size);
        REQUIRE(deck.get_size()==size);
        REQUIRE_FALSE(deck.have_duplicates());
        for (size_t i=0; i<deck.get_size(); ++i) {
            REQUIRE(deck[i].get_rank()>=1);
            REQUIRE(deck[i].get_rank()<=13);
        }
    }
}

TEST_CASE("Operations with cards"){
    Deck_of_Cards deck;
    SECTION("Add_card"){
        Card card("spades", 3);
        deck.add_card(card);
        REQUIRE(deck.get_size()==1);
        REQUIRE(deck[0].get_rank()==3);
        REQUIRE(deck[0].get_suit()==Suit::SPADES);
    }

    SECTION("Remove card"){
        deck=Deck_of_Cards::full_deck();
        Card card=deck[13];
        deck.remove_card_by_index(13);
        REQUIRE(deck.get_size()==51);
        bool flag=false;
        for (size_t i=0; i<deck.get_size(); i++){
            if (deck[i]==card) flag=true;
        }
        REQUIRE_FALSE(flag);
    }
}

TEST_CASE("Operators in deck"){
    Deck_of_Cards deck;
    SECTION("Operator >>"){
        std::istringstream is("2\n spades 3\n diamonds 5\n");
        is >> deck;
        REQUIRE(is.good());
        REQUIRE(deck[0].get_rank()==3);
        REQUIRE(deck[0].get_suit()==Suit::SPADES);
        REQUIRE(deck[1].get_rank()==5);
        REQUIRE(deck[1].get_suit()==Suit::DIAMONDS);
    }

    SECTION("Operator >> for deck"){
            Deck_of_Cards first;
            first.add_card(Card("hearts", 5));
            first.add_card(Card("spades", 3));
            Deck_of_Cards second;
            Deck_of_Cards& ret = (first >> second);
            REQUIRE(&ret == &first);
            REQUIRE(first.get_size()==1);
            REQUIRE(first[0].get_suit()==Suit::HEARTS);
            REQUIRE(first[0].get_rank()==5);
            REQUIRE(second.get_size()==1);
            REQUIRE(second[0].get_suit()==Suit::SPADES);
            REQUIRE(second[0].get_rank()==3);
    }

    SECTION("Error of operator >> for empty deck"){
        Deck_of_Cards first;          
        Deck_of_Cards second;
        REQUIRE_THROWS_AS(first >> second, std::out_of_range);
    }

    SECTION("Error of operator >> for full deck"){
        Deck_of_Cards first;
        first.add_card(Card("hearts", 5));
        Deck_of_Cards second=Deck_of_Cards::full_deck();
        REQUIRE_THROWS_AS(first >> second, std::out_of_range);
        REQUIRE(first.get_size()==1);
        REQUIRE(first[0].get_suit()==Suit::HEARTS);
        REQUIRE(second.get_size()==52);
    }

    SECTION("Errors of operator >> of size"){
        std::istringstream is("345\n");
        is >> deck;
        REQUIRE(!is.good());
    }

    SECTION("Errors of operator >> of rank"){
        std::istringstream is("1\n hearts\n 34");
        is >> deck;
        REQUIRE(!is.good());
    }

    SECTION("Operator <<"){
        std::ostringstream os;
        Card card("spades", 3);
        deck.add_card(card);
        os << deck;
        REQUIRE(os.str().find("spades")!=std::string::npos);
        REQUIRE(os.str().find("3")!=std::string::npos);
    }

    SECTION("Operator []"){
        Card card("spades", 3);
        deck.add_card(card);
        REQUIRE(deck[0].get_rank()==3);
        REQUIRE(deck[0].get_suit()==Suit::SPADES);
    }

    SECTION("Operator [] const"){
        const Card card("spades", 3);
        deck.add_card(card);
        const Deck_of_Cards& const_deck = deck; 
        REQUIRE(const_deck[0].get_rank()==3);
        REQUIRE(const_deck[0].get_suit()==Suit::SPADES);
    }

    SECTION("Operator +"){
        Card card1("spades", 3);
        Card card2("diamonds", 5);
        deck.add_card(card1);
        Deck_of_Cards deck2;
        deck2.add_card(card2);
        deck=deck+deck2;
        REQUIRE(deck.get_size()==2);
        REQUIRE(deck[0].get_rank()==3);
        REQUIRE(deck[0].get_suit()==Suit::SPADES);
        REQUIRE(deck[1].get_rank()==5);
        REQUIRE(deck[1].get_suit()==Suit::DIAMONDS);
    }

    SECTION("Operator +="){
        Card card1("spades", 3);
        Card card2("diamonds", 5);
        deck.add_card(card1);
        Deck_of_Cards deck2;
        deck2.add_card(card2);
        deck+=deck2;
        REQUIRE(deck.get_size()==2);
        REQUIRE(deck[0].get_rank()==3);
        REQUIRE(deck[0].get_suit()==Suit::SPADES);
        REQUIRE(deck[1].get_rank()==5);
        REQUIRE(deck[1].get_suit()==Suit::DIAMONDS);
    }

    SECTION("Error in operator +"){
        deck=Deck_of_Cards::full_deck();
        Card card2("diamonds", 5);
        Deck_of_Cards deck2;
        deck2.add_card(card2);
        REQUIRE_THROWS_AS(deck=deck+deck2, std::invalid_argument);
    }

    SECTION("Error in operator +"){
        deck=Deck_of_Cards::full_deck();
        Card card2("diamonds", 5);
        Deck_of_Cards deck2;
        deck2.add_card(card2);
        REQUIRE_THROWS_AS(deck+deck2, std::invalid_argument);
    }

     SECTION("Error in operator []"){
        deck=Deck_of_Cards::full_deck();
        REQUIRE_THROWS_AS(deck[54], std::out_of_range);
    }
}

TEST_CASE("Operations with deck"){

    SECTION("Shuffle"){
        Deck_of_Cards deck(13);
        Deck_of_Cards new_deck=deck;
        deck.shuffle();
        REQUIRE(deck.get_size()==new_deck.get_size());
        bool flag=false;
        for (size_t i=0; i<deck.get_size(); i++){
            if (!(deck[i]==new_deck[i])){
                flag=true; 
                break;
            }
        }
        REQUIRE(flag);
    }

    SECTION("Sort"){
        Deck_of_Cards deck(16);
        Deck_of_Cards new_deck=deck;
        deck.shuffle();
        deck.sort();
        for (size_t i=1; i<deck.get_size(); i++){
            if (deck[i-1].get_suit()==deck[i].get_suit()){
                REQUIRE(deck[i-1].get_rank()<=deck[i].get_rank());
            }else{
                REQUIRE(deck[i-1].get_suit()<deck[i].get_suit());
            }
        }
    }

    SECTION("Filtered by suit"){
        Deck_of_Cards deck(16);
        deck.shuffle();
        Deck_of_Cards new_deck=deck.filter_by_suit("spades");
        bool flag=true;
        for (size_t i=0; i<new_deck.get_size(); i++){
            if (new_deck[i].get_suit()!=Suit::SPADES){
                flag=false;
                break;
            }
        }
        REQUIRE(flag);
    }

    SECTION("Errors in filter"){
         Deck_of_Cards deck(16);
        deck.shuffle();
        REQUIRE_THROWS_AS(deck.filter_by_suit("fdjhfjd"), std::invalid_argument);
    } 
}